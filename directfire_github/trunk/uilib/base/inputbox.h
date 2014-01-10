#ifndef _inputbox_h_
#define _inputbox_h_
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
#include <string>
using namespace std;

#include "widget.h"
namespace uilib {

class InputBox;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

class InputNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    InputNotificationLayer(InputBox *owner);
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    // Setting
    inline void setFontName(const std::string &name) { m_fontName = name;}
    inline const std::string &getFontName() { return m_fontName;}
    inline void setFontSize(int size) { m_fontSize = size;}
    inline int getFontSize() { return m_fontSize;}
    inline void setFontColor(const ccColor3B &color) { m_fontColor = color;}
    inline const ccColor3B &getFontColor() { return m_fontColor;}
    inline void setPhFontName(const std::string &name) { m_phFontName = name;}
    inline const std::string &getPhFontName() { return m_phFontName;}
    inline void setPhFontSize(int size) { m_phFontSize = size;}
    inline int getPhFontSize() { return m_phFontSize;}
    inline void setPhFontColor(const ccColor3B &color) { m_phFontColor = color;}
    inline const ccColor3B &getPhFontColor() { return m_phFontColor;}
    inline void setPlaceAndHolder(const std::string &text) { m_placeAndHolder = text;}
    inline const std::string &getPlaceAndHolder() { return m_placeAndHolder;}
    virtual void setText(const std::string &text);
    virtual const char *getText();
protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
    int m_maxLength;
    int m_touchPriority;
protected:
    InputBox *m_owner;
protected:
    std::string m_placeAndHolder;
    std::string m_fontName;
    int m_fontSize;
    ccColor3B m_fontColor;
    std::string m_phFontName;
    int m_phFontSize;
    ccColor3B m_phFontColor;
protected:
    bool m_attach;
    CCPoint m_rootOrigPos;
};

class InputFieldTTFDefault : public InputNotificationLayer
{
public:
    InputFieldTTFDefault(InputBox *owner);
    virtual ~InputFieldTTFDefault();
    // InputNotificationLayer
    virtual void onClickTrackNode(bool bClicked);

    // CCLayer
    virtual void onEnter();
};
class InputFieldTTFAction : public InputNotificationLayer,public CCTextFieldDelegate
{
private:
    CCTextFieldTTF *    m_pTextField;
    CCAction *          m_pTextFieldAction;
    bool                m_bAction;
    int                 m_nCharLimit;

public:
    InputFieldTTFAction(InputBox *owner);
    virtual ~InputFieldTTFAction();
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);
    virtual void onClickTrackNode(bool bClicked);

    // CCLayer
    virtual void onEnter();
    virtual void onExit();

    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF *pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF *pSender, const char *delText,int nLen);
    virtual bool onDraw(CCTextFieldTTF *pSender);
    virtual void setText(const std::string &text);
    virtual const char *getText();
};
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class EditBoxDelegate : public NullFrame, public CCEditBoxDelegate
{
public:
    EditBoxDelegate(InputBox *owner,TouchNode *parent = 0);
    virtual ~EditBoxDelegate();
    void initEditBox();
    virtual void layoutCompleted();
    CCEditBox *getEditBox(){return m_editBox;}

    void setText(const std::string& strText);
    void setText(const char* pText);
    const char* getText(void);
    void setFontColor(const ccColor3B& color);
    void setPlaceholderFontColor(const ccColor3B& color);
    void setPlaceHolder(const std::string& strPlaceHolder);
    void setPlaceHolder(const char* pText);
    const char* getPlaceHolder(void);
    void setInputMode(EditBoxInputMode inputMode);
    void setMaxLength(int maxLength);
    int getMaxLength();
    void setInputFlag(EditBoxInputFlag inputFlag);
    void setReturnType(KeyboardReturnType returnType);
    void setVisible(bool isVisible);
    bool visible();
    void setEnabled(bool enabled);
    bool enabled();

public:
    virtual void editBoxEditingDidBegin(CCEditBox* editBox){}
    virtual void editBoxEditingDidEnd(CCEditBox* editBox){}
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text){}
    virtual void editBoxReturn(CCEditBox* editBox);

    virtual void moveInStart();
    virtual void moveOutStart();

protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CCEditBox *m_editBox;
    InputBox *m_owner;

protected:
    EditBoxInputMode    m_eEditBoxInputMode;
    EditBoxInputFlag    m_eEditBoxInputFlag;
    KeyboardReturnType  m_eKeyboardReturnType;

    std::string m_strText;
    std::string m_strPlaceHolder;

    ccColor3B m_colText;
    int  m_nMaxLength;
    bool m_isVisible;
    bool m_enabled;
};
#endif
class InputBox : public BasWidget
{
public:
    InputBox();
    virtual ~InputBox();
    virtual void layoutCompleted();
    virtual void childLayoutCompleted();
    virtual void moveInStart();
    virtual void moveOutStart();

    void initEditBox();
    void parentMoveInCB();
    float getParentMoveInTime();
    float getParentMoveOutTime();
    void setTheme(const std::string &theme,const std::string &bg);
    void setDelegate(CCEditBoxDelegate *pDelegate);
    void setText(const std::string &text);
    void appendText(const std::string &text);
    const char *getText();
    void setPlaceHolder(const std::string &text);
    void setFontColor(const ccColor3B &color);
    void setPlaceholderFontColor(const ccColor3B &color);
    void setInputMode(EditBoxInputMode inputMode);
    void setMaxLength(int maxLength);
    int getMaxLength();
    void setInputFlag(EditBoxInputFlag inputFlag);
    void setReturnType(KeyboardReturnType returnType);
    void setVisible(bool isVisible);
    void setEnabled(bool enabled);
    bool enabled();

    void editBoxReturn(CCEditBox* editBox);
    void setOnReturned(CCNode *listener, SEL_CallFuncN func);

protected:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    EditBoxDelegate *m_editBoxDelegate;
    CCEditBox *m_editBoxReal;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EditBoxDelegate *m_editBoxDelegate;
    CCEditBox *m_editBoxReal;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    InputNotificationLayer *m_editBox;
#else
    InputNotificationLayer *m_editBox;
#endif

protected:
    CCNode *m_returnListener;
    SEL_CallFuncN m_returnFunc;
};

}
#endif
