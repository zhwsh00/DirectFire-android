#include "absareaskin.h"

namespace uilib
{
GraySuppSprite::GraySuppSprite()
{

}
GraySuppSprite::~GraySuppSprite()
{

}
GraySuppSprite* GraySuppSprite::create(const char* pszFileName)
{
    GraySuppSprite* graySprite = new GraySuppSprite;
    if (graySprite && graySprite->initWithFile(pszFileName)){
        graySprite->autorelease();
        return graySprite;
    }else{
        CC_SAFE_RELEASE(graySprite);
        return 0;
    }
}
bool GraySuppSprite::initWithTexture(CCTexture2D* pTexture, const CCRect& tRect)
{
    do{
        CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));

        GLchar* pszFragSource =
                "#ifdef GL_ES \n \
                precision mediump float; \n \
        #endif \n \
            uniform sampler2D u_texture; \n \
            varying vec2 v_texCoord; \n \
            varying vec4 v_fragmentColor; \n \
            void main(void) \n \
        { \n \
            // Convert to greyscale using NTSC weightings \n \
                vec4 col = texture2D(u_texture, v_texCoord); \n \
                float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
                gl_FragColor = vec4(grey, grey, grey, col.a); \n \
        }";

        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
        this->setShaderProgram(pProgram);
        pProgram->release();
        CHECK_GL_ERROR_DEBUG();

        this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();

        this->getShaderProgram()->link();
        this->getShaderProgram()->updateUniforms();

        return true;
    } while (0);
    return false;
}
void GraySuppSprite::draw()
{
    return CCSprite::draw();
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

    this->getShaderProgram()->use();
    //this->getShaderProgram()->setUniformForModelViewProjectionMatrix();
    this->getShaderProgram()->setUniformsForBuiltins();

    ccGLBindTexture2D( this->getTexture()->getName() );

#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;


    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));


    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));


    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CC_INCREMENT_GL_DRAWS(1);
}
BasAreaSkin::BasAreaSkin()
{
    m_enabled = true;
    m_graySkin = 0;
}
BasAreaSkin::~BasAreaSkin()
{

}
void BasAreaSkin::setSkin(const std::string &skin,bool anti)
{
    m_skin = skin;
    if(m_skin.size() == 0)
        return;
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_skin.data());
    if(anti){
        frame->getTexture()->setAntiAliasTexParameters();
    } else {
        frame->getTexture()->setAliasTexParameters();
    }
    this->initWithSpriteFrame(frame);
    autorelease();
}
void BasAreaSkin::setSize(const CCSize &size)
{
    CCSize csize = getContentSize();
    this->setScaleX(size.width / csize.width);
    this->setScaleY(size.height / csize.height);
}
void BasAreaSkin::setEnabled(bool enabled)
{
    if(m_graySkin == 0){
        m_graySkin = new GraySuppSprite;
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_skin.data());
        m_graySkin->initWithSpriteFrame(frame);
        m_graySkin->autorelease();
        m_graySkin->setAnchorPoint(ccp(0,0));
        m_graySkin->setPosition(ccp(0,0));
        this->addChild(m_graySkin);
    }
    m_enabled = enabled;
    if(!m_enabled){
        m_graySkin->setVisible(true);
    }else{
        m_graySkin->setVisible(false);
    }
}
CCSprite *BasAreaSkin::clone()
{
    CCSprite *sprite = CCSprite::create();
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_skin.data());
    sprite->initWithSpriteFrame(frame);
    return sprite;
}

}
