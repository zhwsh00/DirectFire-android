#ifndef _loginregdialog_h_
#define _loginregdialog_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "../base/widget.h"
#include "../base/inputbox.h"

namespace uilib
{

class LoginRegDialog : public BasWidget
{
    enum LoginButtonIndex{
        LoginButton,
        LoginCancelButton,
        LoginRegButton,
        RegButton,
        RegRsetButton,
        RegBackButton
    };

public:
    LoginRegDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~LoginRegDialog();
    void setTheme(const std::string &theme,const std::string &bg);
    void setTitleBg(const std::string &bg);
    void setLoginClickListener(CCNode *node,SEL_CallFuncND func);
    void setCancelClickListener(CCNode *node,SEL_CallFuncND func);
    void setRegClickListener(CCNode *node,SEL_CallFuncND func);
    void setLoginInfo(const std::string &account,const std::string &passwd);
    void getLoginInfo(std::string &account,std::string &passwd);
    void getRegInfo(std::string &account,std::string &passwd);
    void clearLoginInfo();
    void setLoginImg(const std::string &normal,const std::string &pressed);
    void setCancelImg(const std::string &normal,const std::string &pressed);
    void setLoginRegImg(const std::string &normal,const std::string &pressed);
    void setRegImg(const std::string &normal,const std::string &pressed);
    void setRegBackImg(const std::string &normal,const std::string &pressed);
    void setAccountLimitLen(int len);
    inline int accountLimitedLen() { return m_accountLimitLen;}
    void setPasswdLimitLen(int len);
    inline int passwdLimitedLen() { return m_passwdLimitLen;}
    inline void setEdgeSize(float size) { m_edgeSize = size;}
    inline float getEdgeSize() { return m_edgeSize;}
    void setDialogEnabled(bool enable);
    void exec();
    void destroy();
protected:
    void onButtonClicked(CCNode *pSender,void *index);
    void onFailedSplashFinished(CCNode* sender);
    void finished();
    void clear();
protected:
    void onMoveOutFinished(CCNode *node);
protected:
    float m_edgeSize;
    int m_accountLimitLen;
    int m_passwdLimitLen;
protected:
    std::string m_theme;
    std::string m_bg;
    std::string m_titleBg;
protected:
    CCNode *m_loginListener;
    SEL_CallFuncND m_loginFunc;
    CCNode *m_cancelListener;
    SEL_CallFuncND m_cancelFunc;
    CCNode *m_regListener;
    SEL_CallFuncND m_regFunc;
protected:
    InputBox *m_accountBox;
    InputBox *m_passwdBox;
protected:
    std::string m_account;
    std::string m_passwd;
protected:
    BasButton *m_loginTitleWidget;
    BasButton *m_regTitleWidget;
    BasWidget *m_contentWidget;

    BasWidget *m_loginWidget;
    BasWidget *m_regWidget;
protected:
    BasButton *m_loginButton;
    BasButton *m_loginCancelButton;
    BasButton *m_loginRegButton;

    BasButton *m_regButton;
    BasButton *m_regBackButton;
protected:
    std::string m_loginImg,m_loginPressedImg;
    std::string m_cancelImg,m_cancelPressedImg;
    std::string m_loginRegImg,m_loginRegPressedImg;
    std::string m_regImg,m_regPressedImg;
    std::string m_regBackImg,m_regBackPressedImg;
};

}
#endif
