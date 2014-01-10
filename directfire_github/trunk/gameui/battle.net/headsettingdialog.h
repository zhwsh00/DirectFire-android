#ifndef _headsettingdialog_h_
#define _headsettingdialog_h_

#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

#include "gamecore/serverinterface.h"
#include "uilib/uilib.h"
using namespace uilib;
#include "cliententry/uimsgevent.h"
#include "photo/photohelper.h"
#include "photo/photolistener.h"
using namespace uilib;

class HeadSettingDialog : public BasShowDialog, public PhotoListener
{
public:
    HeadSettingDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~HeadSettingDialog();
    virtual void exec();
    
    // PhotoListener
    virtual void takePhotoFinished(const char* imageData, int len, const char* imageDataHq, int lenHq);
    virtual void takePhotoFinished(const char* imageFile);
    virtual void takePhotoFailed();
    virtual void takePhotoCanceled();

    void setHeadSprite(CCSprite *headSprite);
    void setEditAble(bool editAble);
    void setSubmitPortraitCB(CCNode *listener,SEL_CallFuncND func);
    
protected:
    void portraitUpdated(const std::string& imgData);
protected:
    void finish();
    void setResetImg(const std::string &normal,const std::string &pressed);
protected:
    void onUploadClicked(CCNode *sender,void *data);
    void onLogOutClicked(CCNode *sender,void *data);
    void onExitGameClicked(CCNode *sender,void *data);
    void onResetClicked(CCNode *sender,void *data);
    void onSubmitClicked(CCNode *sender,void *data);
    void editEnabled(bool enable);
    bool sendFormData();
    void onSubmitStart();
protected:
    void onSubmitSuc(CCNode *sender,void *data);
    void onSubmitFailed(CCNode *sender,void *data);
    void onFailedSplashFinished(CCNode *sender);
protected:
    void onFemaleClicked(CCNode *sender,void *data);
    void onMaleClicked(CCNode *sender,void *data);
protected:
    void hiddenInputBox();
    void showEditAbleInputBox();
    void showDisableInputBox();
protected:
    CCNode *m_submitPortraitListener;
    SEL_CallFuncND m_submitPortraitFunc;
protected:
    ServerInterface *m_serverInf;
    UiMsgEv::AccountInfoEv *m_accountInf;
protected:
    std::string m_resetImg;
    std::string m_resetPressedImg;
protected:
    InputBox *m_accountInput;
    InputBox *m_pwdInput;
    InputBox *m_pwdConfirmInput;
    InputBox *m_nickNameInput;
    CheckBox *m_femaleButton;
    CheckBox *m_maleButton;
protected:
    BasWidget *m_baseArea;
    BasButton *m_resetButton;
    BasButton *m_submitButton;
    BusyDialog *m_loadingDialog;
protected:
    std::string m_headPortrait;
    BasNodeDelegateWidget *m_headDelegate;
    CCSprite *m_headSprite;
protected:
    bool m_editAble;
};
#endif
