#include "absskin.h"
#include "../base/uithemedef.h"
#include "../base/fontutil.h"
#include "../base/uithemedef.h"

namespace uilib
{

BasSkin::BasSkin()
{
    m_uiTheme = 0;
    m_inited = false;
    m_skinFillHor = false;
    m_skinFillVer = false;
}
BasSkin::~BasSkin()
{

}
void BasSkin::setSkinFillHor(bool fill)
{
    m_skinFillHor = fill;
}
void BasSkin::setSkinFillVer(bool fill)
{
    m_skinFillVer = fill;
}
void BasSkin::setUiTheme(UiThemeDef *theme,const std::string &name)
{
    m_uiTheme = theme;
    m_uiName = name;
    if(m_uiTheme && m_uiName.size() != 0)
        m_inited = init();
}
void BasSkin::setFrameSize(const CCSize &size)
{
    m_frameSize = size;
    if(m_inited){
        reLayout();
    }
}
void BasSkin::getPreferedSize(CCSize &size)
{
    if(m_frameSize.width > 0 && m_frameSize.height > 0)
        size = m_frameSize;
    else
        size = this->getContentSize();
}
void BasSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
}
bool BasSkin::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    return false;
}

ButtonImageSkin::ButtonImageSkin()
{

}
ButtonImageSkin::~ButtonImageSkin()
{

}
BasSkin *ButtonImageSkin::create(const CCSize &size,UiThemeDef *theme,const std::string &themename)
{
    ButtonImageSkin *skin = new ButtonImageSkin();
    skin->setUiTheme(theme,themename);
    skin->setFrameSize(size);
    return skin;
}
void ButtonImageSkin::getPreferedSize(CCSize &size)
{
    if(m_frameSize.width > 0 && m_frameSize.height > 0)
        size = m_frameSize;
    else
        size = m_bg.getContentSize();
}
bool ButtonImageSkin::init()
{
    if(m_uiTheme == 0 || m_uiName.size() == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "ButtonImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string img;
    data->getImg(m_uiName,img);
    if(img.size() == 0){
        cout << "ButtonImageSkin::init,can not get indicated img,name=" << m_uiName << endl;
        return false;
    }
    m_bg.setSkin(img);
    this->addChild(&m_bg);
    if(m_frameSize.width != 0 && m_frameSize.height != 0){
        reLayout();
    }
    return true;
}
void ButtonImageSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
    m_bg.setEnabled(enabled);
}
void ButtonImageSkin::reLayout()
{
    CCSize csize = m_bg.getContentSize();
    m_bg.setAnchorPoint(ccp(0,0));
    m_bg.setPosition(ccp(0,0));
    m_bg.setScaleX(m_frameSize.width / csize.width);
    m_bg.setScaleY(m_frameSize.height  /csize.height);
}
bool ButtonImageSkin::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    sprites.push_back(&m_bg);
    size = m_frameSize;
    return true;
}

ButtonTextImageSkin::ButtonTextImageSkin()
{
    m_fontFamily = getSystemFont();
    m_fontSize = 16;
    m_fontColor = ccBLACK;
    m_label = 0;
}
ButtonTextImageSkin::~ButtonTextImageSkin()
{

}
void ButtonTextImageSkin::setFrameSize(const CCSize &size)
{
    m_frameSize = size;
    if(m_inited){
        reLayout();
    }else{
        if(m_label){
            m_label->setAnchorPoint(ccp(0.5,0.5));
            m_label->setPosition(ccp(m_frameSize.width / 2,m_frameSize.height / 2));
            CCSize size = m_label->getTexture()->getContentSize();
            m_label->setScaleX(m_frameSize.width / size.width);
            m_label->setScaleY(m_frameSize.height / size.height);
        }
    }
}
BasSkin *ButtonTextImageSkin::create(const std::string &text,const CCSize &framesize,UiThemeDef *theme,const std::string &themename,
                            const std::string &family,
                            int size,ccColor3B color)
{
    ButtonTextImageSkin *skin = new ButtonTextImageSkin();
    skin->setFrameSize(framesize);
    skin->setText(text,family,size,color);
    skin->setUiTheme(theme,themename);
    return skin;
}
void ButtonTextImageSkin::getPreferedSize(CCSize &size)
{
    if(m_frameSize.width > 0 && m_frameSize.height > 0){
        size = m_frameSize;
    }else{
        if(m_bg.getParent()){
            size = m_bg.getContentSize();
        }
        if(m_label && m_label->getParent()){
            CCSize lsize = m_label->getTexture()->getContentSize();
            /* 1.1 for text edge ?*/
            if(lsize.width > size.width)
                size.width = lsize.width * 1.1;
            if(lsize.height > size.height)
                size.height = lsize.height * 1.1;
        }
    }
}
void ButtonTextImageSkin::setText(const std::string &text,
             const std::string &family,
             int size,
             ccColor3B color)
{
    if(m_label != 0){
        m_label->removeFromParentAndCleanup(true);
        m_label = 0;
    }
    m_text = text;
    if(m_text.empty()){
        return;
    }
    m_fontFamily = family;
    m_fontSize = size;
    m_fontColor = color;
    m_label = CCLabelTTF::create(m_text.data(),m_fontFamily.data(),
                                 m_fontSize,m_frameSize,
                                 kCCTextAlignmentCenter,
                                 kCCVerticalTextAlignmentCenter);
    m_label->setColor(m_fontColor);
    this->addChild(m_label,1);
    m_label->setAnchorPoint(ccp(0.5,0.5));
    if(m_frameSize.width != 0 && m_frameSize.height != 0){
        m_label->setPosition(ccp(m_frameSize.width / 2,m_frameSize.height / 2));
    }else{
        CCSize tsize = m_label->getTexture()->getContentSize();
        m_label->setPosition(ccp(tsize.width / 2,tsize.height / 2));
    }
}
bool ButtonTextImageSkin::init()
{
    if(m_uiTheme == 0 || m_uiName.size() == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "ButtonTextImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string img;
    data->getImg(m_uiName,img);
    if(img.size() == 0){
        cout << "ButtonTextImageSkin::init,can not get indicated img,name=" << m_uiName << endl;
        return false;
    }
    m_bg.setSkin(img);
    this->addChild(&m_bg,0);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void ButtonTextImageSkin::updateText(const std::string &text)
{
    if(m_label)
        m_label->setString(text.data());
}
void ButtonTextImageSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
    m_bg.setEnabled(enabled);
    if(m_enabled && m_label){
        m_label->setColor(m_fontColor);
    }else if(m_label){
        m_label->setColor(ccGRAY);
    }
}
void ButtonTextImageSkin::reLayout()
{
    CCSize csize = m_bg.getContentSize();
    m_bg.setAnchorPoint(ccp(0,0));
    m_bg.setPosition(ccp(0,0));
    m_bg.setScaleX(m_frameSize.width / csize.width);
    m_bg.setScaleY(m_frameSize.height  /csize.height);
    if(m_label){
        m_label->setAnchorPoint(ccp(0.5,0.5));
        m_label->setPosition(ccp(m_frameSize.width / 2,m_frameSize.height / 2));
        CCSize size = m_label->getTexture()->getContentSize();
        if(size.width > m_frameSize.width && size.height > m_frameSize.height){
            m_label->setScaleX(m_frameSize.width / size.width);
            m_label->setScaleY(m_frameSize.height / size.height);
        }
    }
}
bool ButtonTextImageSkin::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    sprites.push_back(&m_bg);
    size = m_frameSize;
    return true;
}

BorderImageSkin::BorderImageSkin()
{

}
BorderImageSkin::~BorderImageSkin()
{

}
BasSkin *BorderImageSkin::create(const CCSize &size,UiThemeDef *theme,const std::string &themename)
{
    if(theme == 0 || themename.size() == 0)
        return 0;
    BorderImageSkin *skin = new BorderImageSkin;
    skin->setUiTheme(theme,themename);
    skin->setFrameSize(size);
    return skin;
}
BasSkin *BorderImageSkin::create(const CCSize &size,const std::string &themename,const std::string &bg)
{
    UiThemeDef *theme = UiThemeMgrProxy::getInstance()->getThemeByName(themename);
    if(theme == 0 || bg.size() == 0)
        return 0;
    BorderImageSkin *skin = new BorderImageSkin;
    skin->setUiTheme(theme,bg);
    skin->setFrameSize(size);
    return skin;
}
void BorderImageSkin::getPreferedSize(CCSize &psize)
{
    if(m_frameSize.width > 0 && m_frameSize.height > 0){
        psize = m_frameSize;
        return;
    }
    CCSize lbsize = m_lb.getContentSize();
    CCSize bottom = m_bottom.getContentSize();
    CCSize rbsize = m_rb.getContentSize();
    CCSize left = m_left.getContentSize();
    CCSize ltsize = m_lt.getContentSize();
    psize.width = lbsize.width + bottom.width + rbsize.width;
    psize.height = lbsize.height + left.height + ltsize.height;
}
bool BorderImageSkin::init()
{
    if(m_uiTheme == 0 || m_uiName.size() == 0)
        return false;
    SelfAdaptBgData *data = m_uiTheme->getSelfAdaptDataByName(m_uiName);
    if(data == 0){
        cout << "BorderImageSkin::init,can not get SelfAdaptBgData,name=" << m_uiName << endl;
        return false;
    }
    std::vector<std::string> &selfData = data->getAreaData();
    m_lt.setSkin(selfData[Area_lt],false);
    m_top.setSkin(selfData[Area_top],false);
    m_rt.setSkin(selfData[Area_rt],false);
    m_left.setSkin(selfData[Area_left],false);
    m_center.setSkin(selfData[Area_center],false);
    m_right.setSkin(selfData[Area_right],false);
    m_lb.setSkin(selfData[Area_lb],false);
    m_bottom.setSkin(selfData[Area_bottom],false);
    m_rb.setSkin(selfData[Area_rb],false);
    this->addChild(&m_lt);
    this->addChild(&m_top);
    this->addChild(&m_rt);
    this->addChild(&m_left);
    this->addChild(&m_right);
    this->addChild(&m_lb);
    this->addChild(&m_bottom);
    this->addChild(&m_rb);
    this->addChild(&m_center);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void BorderImageSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
    m_lt.setEnabled(enabled);
    m_top.setEnabled(enabled);
    m_rt.setEnabled(enabled);
    m_left.setEnabled(enabled);
    m_right.setEnabled(enabled);
    m_lb.setEnabled(enabled);
    m_bottom.setEnabled(enabled);
    m_rb.setEnabled(enabled);
    m_center.setEnabled(enabled);
}
void BorderImageSkin::reLayout()
{
    CCSize ltsize = m_lt.getContentSize();
    CCSize topsize = m_top.getContentSize();
    CCSize rtsize = m_rt.getContentSize();
    CCSize leftsize = m_left.getContentSize();
    CCSize centersize = m_center.getContentSize();
    CCSize rightsize = m_right.getContentSize();
    CCSize lbsize = m_lb.getContentSize();
    CCSize bottomsize = m_bottom.getContentSize();
    CCSize rbsize = m_rb.getContentSize();
    if(0){
        m_lt.setAnchorPoint(ccp(0,1.0));
        m_lt.setPosition(ccp(0,m_frameSize.height));

        m_rt.setAnchorPoint(ccp(1.0,1.0));
        m_rt.setPosition(ccp(m_frameSize.width,m_frameSize.height));

        m_lb.setAnchorPoint(ccp(0,0));
        m_lb.setPosition(ccp(0,0));

        m_rb.setAnchorPoint(ccp(1.0,0));
        m_rb.setPosition(ccp(m_frameSize.width,0));

        m_left.setAnchorPoint(ccp(0,0));
        m_left.setPosition(ccp(0,lbsize.height));
        m_left.setScaleY((m_frameSize.height - ltsize.height - lbsize.height) / leftsize.height );

        m_top.setAnchorPoint(ccp(0,1.0));
        m_top.setPosition(ccp(ltsize.width,m_frameSize.height));
        m_top.setScaleX(((m_frameSize.width - ltsize.width - rtsize.width) / topsize.width));

        m_right.setAnchorPoint(ccp(1.0,0.0));
        m_right.setPosition(ccp(m_frameSize.width,rbsize.height));
        m_right.setScaleY((m_frameSize.height - rtsize.height - rbsize.height) / rightsize.height );

        m_bottom.setAnchorPoint(ccp(0.0,0.0));
        m_bottom.setPosition(ccp(lbsize.width,0.0));
        m_bottom.setScaleX((m_frameSize.width - rbsize.width - lbsize.width) / bottomsize.width);

        m_center.setAnchorPoint(ccp(0,0));
        m_center.setPosition(ccp(lbsize.width,lbsize.height));
        m_center.setScaleX((m_frameSize.width - leftsize.width - rightsize.width) / centersize.width);
        m_center.setScaleY((m_frameSize.height - topsize.height - bottomsize.height) / centersize.height);
    }else{
        m_lt.setAnchorPoint(ccp(0,1.0));
        m_lt.setPosition(ccp(0,m_frameSize.height));

        m_rt.setAnchorPoint(ccp(1.0,1.0));
        m_rt.setPosition(ccp(m_frameSize.width,m_frameSize.height));

        m_lb.setAnchorPoint(ccp(0,0));
        m_lb.setPosition(ccp(0,0));

        m_rb.setAnchorPoint(ccp(1.0,0));
        m_rb.setPosition(ccp(m_frameSize.width,0));

        m_left.setAnchorPoint(ccp(0.5,0.5));
        m_left.setPosition(ccp(leftsize.width / 2.0,lbsize.height + (m_frameSize.height - ltsize.height - lbsize.height ) / 2.0));
        m_left.setScaleY((m_frameSize.height - ltsize.height - lbsize.height) / leftsize.height );

        m_top.setAnchorPoint(ccp(0.5,0.5));
        m_top.setPosition(ccp(m_frameSize.width / 2.0,m_frameSize.height - topsize.height / 2.0));
        m_top.setScaleX(((m_frameSize.width - ltsize.width - rtsize.width) / topsize.width));

        m_right.setAnchorPoint(ccp(0.5,0.5));
        m_right.setPosition(ccp(m_frameSize.width - rightsize.width / 2.0,rbsize.height + (m_frameSize.height - rtsize.height - rbsize.height ) / 2.0));
        m_right.setScaleY((m_frameSize.height - rtsize.height - rbsize.height) / rightsize.height );

        m_bottom.setAnchorPoint(ccp(0.5,0.5));
        m_bottom.setPosition(ccp(m_frameSize.width/2,bottomsize.height / 2.0));
        m_bottom.setScaleX((m_frameSize.width - rbsize.width - lbsize.width) / bottomsize.width);

        m_center.setAnchorPoint(ccp(0.5,0.5));
        m_center.setPosition(ccp(m_frameSize.width / 2.0,bottomsize.height + (m_frameSize.height - topsize.height - bottomsize.height ) / 2.0));
        m_center.setScaleX((m_frameSize.width - leftsize.width - rightsize.width) / centersize.width);
        m_center.setScaleY((m_frameSize.height - topsize.height - bottomsize.height) / centersize.height);
    }
}
TrisectionImageSkin::TrisectionImageSkin()
{

}
TrisectionImageSkin::~TrisectionImageSkin()
{

}
void TrisectionImageSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
    m_headSkin.setEnabled(enabled);
    m_tailSkin.setEnabled(enabled);
    m_bgSkin.setEnabled(enabled);
}
HTrisectionImageSkin::HTrisectionImageSkin()
{

}
HTrisectionImageSkin::~HTrisectionImageSkin()
{

}
BasSkin *HTrisectionImageSkin::create(const CCSize &size,UiThemeDef *theme,const std::string &img)
{
    HTrisectionImageSkin *skin = new HTrisectionImageSkin;
    skin->m_headImg = img + "head";
    skin->m_tailImg = img + "tail";
    skin->m_img = img;
    skin->setUiTheme(theme,img);
    skin->setFrameSize(size);
    return skin;
}
BasSkin *HTrisectionImageSkin::create(const CCSize &size,const std::string &themename,const std::string &img)
{
    UiThemeDef *theme = UiThemeMgrProxy::getInstance()->getThemeByName(themename);
    HTrisectionImageSkin *skin = new HTrisectionImageSkin;
    skin->m_headImg = img + "head";
    skin->m_tailImg = img + "tail";
    skin->m_img = img;
    skin->setUiTheme(theme,img);
    skin->setFrameSize(size);
    return skin;
}
void HTrisectionImageSkin::getPreferedSize(CCSize &size)
{
    CCSize headsize = m_headSkin.getContentSize();
    CCSize tailsize = m_tailSkin.getContentSize();
    CCSize bgsize = m_bgSkin.getContentSize();
    size.width = headsize.width + tailsize.width + bgsize.width;
    size.height = bgsize.height;
}
bool HTrisectionImageSkin::init()
{
    if(m_uiTheme == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "HTrisectionImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string bgimg,bghead,bgtail;
    data->getImg(m_img,bgimg);
    data->getImg(m_headImg,bghead);
    data->getImg(m_tailImg,bgtail);
    if(bgimg.size() == 0 || bghead.size() == 0 || bgtail.size() == 0){
        cout << "HTrisectionImageSkin::init,can not get correct img=" << m_img << endl;
        return false;
    }
    m_headSkin.setSkin(bghead,false);
    m_tailSkin.setSkin(bgtail,false);
    m_bgSkin.setSkin(bgimg,false);
    this->addChild(&m_headSkin);
    this->addChild(&m_tailSkin);
    this->addChild(&m_bgSkin);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void HTrisectionImageSkin::reLayout()
{
    CCSize headsize = m_headSkin.getContentSize();
    CCSize tailsize = m_tailSkin.getContentSize();
    CCSize csize = m_bgSkin.getContentSize();

    m_headSkin.setAnchorPoint(ccp(0,0));
    m_headSkin.setPosition(ccp(0,0));
    if(m_skinFillVer)
        m_headSkin.setScaleY(m_frameSize.height / headsize.height);
    else
        m_headSkin.setScaleY(1.0);

    m_tailSkin.setAnchorPoint(ccp(1.0,0.0));
    m_tailSkin.setPosition(ccp(m_frameSize.width,0));
    if(m_skinFillVer)
        m_tailSkin.setScaleY(m_frameSize.height / tailsize.height);
    else
        m_tailSkin.setScaleY(1.0);

    m_bgSkin.setAnchorPoint(ccp(0.5,0.5));
    m_bgSkin.setPosition(ccp(headsize.width + (m_frameSize.width - headsize.width - tailsize.width)/2.0,m_frameSize.height / 2.0));
    m_bgSkin.setScaleX((m_frameSize.width - headsize.width -
                        tailsize.width) / csize.width);
    if(m_skinFillVer)
        m_bgSkin.setScaleY(m_frameSize.height / csize.height);
    else
        m_bgSkin.setScaleY(1);
}
VTrisectionImageSkin::VTrisectionImageSkin()
{

}
VTrisectionImageSkin::~VTrisectionImageSkin()
{

}
BasSkin *VTrisectionImageSkin::create(const CCSize &size,UiThemeDef *theme,const std::string &img)
{
    VTrisectionImageSkin *skin = new VTrisectionImageSkin;
    skin->m_headImg = img + "head";
    skin->m_tailImg = img + "tail";
    skin->m_img = img;
    skin->setUiTheme(theme,img);
    skin->setFrameSize(size);
    return skin;
}
BasSkin *VTrisectionImageSkin::create(const CCSize &size,const std::string &themename,const std::string &img)
{
    UiThemeDef *theme = UiThemeMgrProxy::getInstance()->getThemeByName(themename);
    VTrisectionImageSkin *skin = new VTrisectionImageSkin;
    skin->m_headImg = img + "head";
    skin->m_tailImg = img + "tail";
    skin->m_img = img;
    skin->setUiTheme(theme,img);
    skin->setFrameSize(size);
    return skin;
}
void VTrisectionImageSkin::getPreferedSize(CCSize &size)
{
    CCSize headsize = m_headSkin.getContentSize();
    CCSize tailsize = m_tailSkin.getContentSize();
    CCSize bgsize = m_bgSkin.getContentSize();
    size.height = headsize.height + tailsize.height + bgsize.height;
    size.width = bgsize.width;
}
bool VTrisectionImageSkin::init()
{
    if(m_uiTheme == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "VTrisectionImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string bgimg,bghead,bgtail;
    data->getImg(m_img,bgimg);
    data->getImg(m_headImg,bghead);
    data->getImg(m_tailImg,bgtail);
    if(bgimg.size() == 0 || bghead.size() == 0 || bgtail.size() == 0){
        cout << "VTrisectionImageSkin::init,can not get correct img=" << m_img << endl;
        return false;
    }
    m_headSkin.setSkin(bghead,false);
    m_tailSkin.setSkin(bgtail,false);
    m_bgSkin.setSkin(bgimg,false);
    this->addChild(&m_headSkin);
    this->addChild(&m_tailSkin);
    this->addChild(&m_bgSkin);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void VTrisectionImageSkin::reLayout()
{
    CCSize headsize = m_headSkin.getContentSize();
    CCSize tailsize = m_tailSkin.getContentSize();
    CCSize csize = m_bgSkin.getContentSize();
    m_headSkin.setAnchorPoint(ccp(1.0,1.0));
    m_headSkin.setPosition(ccp(m_frameSize.width,m_frameSize.height));
    if(m_skinFillHor)
        m_headSkin.setScaleX(m_frameSize.width / headsize.width);
    else
        m_headSkin.setScaleX(1.0);

    m_tailSkin.setAnchorPoint(ccp(0,0));
    m_tailSkin.setPosition(ccp(0,0));
    if(m_skinFillHor)
        m_tailSkin.setScaleX(m_frameSize.width / tailsize.width);
    else
        m_tailSkin.setScaleX(1.0);

    m_bgSkin.setAnchorPoint(ccp(0.5,0.5));
    m_bgSkin.setPosition(ccp(m_frameSize.width / 2.0,tailsize.height + (m_frameSize.height - headsize.height - tailsize.height) / 2.0));
    if(m_skinFillHor)
        m_bgSkin.setScaleX(m_frameSize.width / csize.width);
    else
        m_bgSkin.setScaleX(1.0);
}
ScrollImageSkin::ScrollImageSkin()
{
    m_indicatorPercent = 0.0;
}
ScrollImageSkin::~ScrollImageSkin()
{

}
void ScrollImageSkin::setIndicatorPercent(float percent)
{
    m_indicatorPercent = percent;
}
float ScrollImageSkin::getIndicatorPercent()
{
    return m_indicatorPercent;
}
void ScrollImageSkin::setEnabled(bool enabled)
{
    m_enabled = enabled;
    m_scrollHead.setEnabled(enabled);
    m_scrollTail.setEnabled(enabled);
    m_scrollBg.setEnabled(enabled);
    m_scrollIndicator.setEnabled(enabled);
}
VScrollImageSkin::VScrollImageSkin()
{

}
VScrollImageSkin::~VScrollImageSkin()
{

}
BasSkin *VScrollImageSkin::create(const CCSize &size,UiThemeDef *theme)
{
    std::string name = "vscroll";
    VScrollImageSkin *skin = new VScrollImageSkin;
    skin->setUiTheme(theme,name);
    skin->setFrameSize(size);
    return skin;
}
void VScrollImageSkin::setIndicatorPercent(float percent)
{
    ScrollImageSkin::setIndicatorPercent(percent);
    if(m_inited){
        CCSize isize = m_scrollIndicator.getContentSize();
        m_scrollIndicator.setPosition(ccp(m_frameSize.width / 2,
                                          m_frameSize.height -
                                          (m_frameSize.height - isize.height) *
                                          m_indicatorPercent));
    }
}
void VScrollImageSkin::getPreferedSize(CCSize &size)
{
    size = m_scrollBg.getContentSize();
}
bool VScrollImageSkin::init()
{
    if(m_uiTheme == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "VScrollImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string bgimg,bghead,bgtail,indicatorimg;
    data->getImg("vscrollbg",bgimg);
    data->getImg("vscrollbghead",bghead);
    data->getImg("vscrollbgtail",bgtail);
    if(bgimg.size() == 0 || bghead.size() == 0 || bgtail.size() == 0){
        cout << "VScrollImageSkin::init,can not get indicated img,name=vscrollbg" << endl;
        return false;
    }
    data->getImg("vscrollindicator",indicatorimg);
    if(indicatorimg.size() == 0){
        cout << "VScrollImageSkin::init,can not get indicated img,name=vscrollindicator" << endl;
        return false;
    }
    m_scrollBg.setSkin(bgimg);
    m_scrollHead.setSkin(bghead);
    m_scrollTail.setSkin(bgtail);
    m_scrollIndicator.setSkin(indicatorimg);
    this->addChild(&m_scrollBg);
    this->addChild(&m_scrollHead);
    this->addChild(&m_scrollTail);
    this->addChild(&m_scrollIndicator);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void VScrollImageSkin::reLayout()
{
    CCSize headsize = m_scrollHead.getContentSize();
    CCSize tailsize = m_scrollTail.getContentSize();
    CCSize csize = m_scrollBg.getContentSize();
    CCSize isize = m_scrollIndicator.getContentSize();
    m_scrollHead.setAnchorPoint(ccp(1.0,1.0));
    m_scrollHead.setPosition(ccp(m_frameSize.width,m_frameSize.height));
    if(m_skinFillHor) m_scrollHead.setScaleX(m_frameSize.width / headsize.width);
    m_scrollTail.setAnchorPoint(ccp(0,0));
    m_scrollTail.setPosition(ccp(0,0));
    if(m_skinFillHor) m_scrollTail.setScaleX(m_frameSize.width / tailsize.width);

    m_scrollBg.setAnchorPoint(ccp(0.5,0.5));
    m_scrollBg.setPosition(ccp(m_frameSize.width / 2,m_frameSize.height / 2));
    if(m_skinFillHor) m_scrollBg.setScaleX(m_frameSize.width / csize.width);
    m_scrollBg.setScaleY((m_frameSize.height - headsize.height - tailsize.height) / csize.height);

    m_scrollIndicator.setAnchorPoint(ccp(0.5,1.0));
    m_scrollIndicator.setPosition(ccp(m_frameSize.width / 2,
                                      m_frameSize.height -
                                      (m_frameSize.height - isize.height) *
                                      m_indicatorPercent));
}
HScrollImageSkin::HScrollImageSkin()
{

}
HScrollImageSkin::~HScrollImageSkin()
{

}
BasSkin *HScrollImageSkin::create(const CCSize &size,UiThemeDef *theme)
{
    std::string name = "hscroll";
    HScrollImageSkin *skin = new HScrollImageSkin;
    skin->setUiTheme(theme,name);
    skin->setFrameSize(size);
    return skin;
}
void HScrollImageSkin::setIndicatorPercent(float percent)
{
    ScrollImageSkin::setIndicatorPercent(percent);
    if(m_inited){
        CCSize isize = m_scrollIndicator.getContentSize();
        m_scrollIndicator.setPosition(ccp((m_frameSize.width - isize.width) * m_indicatorPercent,
                                      m_frameSize.height / 2));
    }
}
void HScrollImageSkin::getPreferedSize(CCSize &size)
{
    size = m_scrollBg.getContentSize();
}
bool HScrollImageSkin::init()
{
    if(m_uiTheme == 0)
        return false;
    NormalDataDef *data = m_uiTheme->getNormalData();
    if(data == 0){
        cout << "HScrollImageSkin::init,can not get NormalData,please check!" << endl;
        return false;
    }
    std::string bgimg,bghead,bgtail,indicatorimg;
    data->getImg("hscrollbg",bgimg);
    data->getImg("hscrollbghead",bghead);
    data->getImg("hscrollbgtail",bgtail);
    if(bgimg.size() == 0 || bghead.size() == 0 || bgtail.size() == 0){
        cout << "HScrollImageSkin::init,can not get indicated img,name=hscrollbg" << endl;
        return false;
    }
    data->getImg("hscrollindicator",indicatorimg);
    if(indicatorimg.size() == 0){
        cout << "HScrollImageSkin::init,can not get indicated img,name=hscrollindicator" << endl;
        return false;
    }
    m_scrollBg.setSkin(bgimg);
    m_scrollHead.setSkin(bghead);
    m_scrollTail.setSkin(bgtail);
    m_scrollIndicator.setSkin(indicatorimg);
    this->addChild(&m_scrollBg);
    this->addChild(&m_scrollHead);
    this->addChild(&m_scrollTail);
    this->addChild(&m_scrollIndicator);
    if(m_frameSize.width != 0 && m_frameSize.height != 0)
        reLayout();
    return true;
}
void HScrollImageSkin::reLayout()
{
    CCSize headsize = m_scrollHead.getContentSize();
    CCSize tailsize = m_scrollTail.getContentSize();
    CCSize csize = m_scrollBg.getContentSize();
    CCSize isize = m_scrollIndicator.getContentSize();

    m_scrollHead.setAnchorPoint(ccp(0,0));
    m_scrollHead.setPosition(ccp(0,0));
    if(m_skinFillVer) m_scrollHead.setScaleY(m_frameSize.height / headsize.height);

    m_scrollTail.setAnchorPoint(ccp(1.0,0.0));
    m_scrollTail.setPosition(ccp(m_frameSize.width,0));
    if(m_skinFillVer) m_scrollTail.setScaleY(m_frameSize.height / tailsize.height);

    m_scrollBg.setAnchorPoint(ccp(0.5,0.5));
    m_scrollBg.setPosition(ccp(m_frameSize.width / 2,m_frameSize.height / 2));
    m_scrollBg.setScaleX((m_frameSize.width - headsize.width - tailsize.width) / csize.width);
    if(m_skinFillVer) m_scrollBg.setScaleY(m_frameSize.height / csize.height);

    m_scrollIndicator.setAnchorPoint(ccp(0,0.5));
    m_scrollIndicator.setPosition(ccp((m_frameSize.width - isize.width) * m_indicatorPercent,
                                      m_frameSize.height / 2));
}

}
