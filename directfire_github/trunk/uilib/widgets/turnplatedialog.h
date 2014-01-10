#ifndef _turnplatedialog_h_
#define _turnplatedialog_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

namespace uilib {
class TurnPlateDialog;

class TurnPlateNodeDelegate : public FSizeCCNodeDelegate
{
public:
    TurnPlateNodeDelegate(TurnPlateDialog *owner,CCNode *node,const CCSize &size = CCSizeMake(0,0));
    virtual ~TurnPlateNodeDelegate();
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    TurnPlateDialog *m_owner;
    CCPoint m_pressEvent;
    CCPoint m_releaseEvent;
};
class TurnPlateDialog : public BasShowDialog
{
public:
    typedef struct TurnPlateBetInfo{
        TurnPlateBetInfo(){
            m_goldUsed = 0;
            m_propNum = 0;
        }
        TurnPlateBetInfo(int use,const std::string &prop,int num){
            m_goldUsed = use;
            m_propName = prop;
            m_propNum = num;
        }

        int m_goldUsed;
        std::string m_propName;
        int m_propNum;
    }TurnPlateBetInfo;

    TurnPlateDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~TurnPlateDialog();
    void exec();
    void setPlateGridNum(int num) { m_plateGridNum = num;}
    void setPlateInfo(const std::string &hand,const std::string &plate,const std::string &frame,const std::string &ind);
    void setPropPayInfo(const std::vector<std::string> &props,const std::vector<int> &payrate);
    void setForce(float force);
    void setGlodInfo(const std::string &img,int num);
    void setBetMinMax(int min,int max);
    const std::vector<TurnPlateBetInfo> &getBetResults() { return m_betResults;}
    void usePropReplyGot();
protected:
    void finish();
    void initPlateProps();
    void initGoldInfo();
    void initBetInfo();
protected:
    void startIndicator();
    void onFrameClicked();
    void onPlateActionFinished(CCNode *node,void *data);
    void onFrameActionFinished(CCNode *node,void *data);
    void onFrameIndicatorFinished(CCNode *node,void *data);
    void calculateResult();
    void sendBetResult();
    void showBetResult(const std::string &img,int num,int rate);
protected:
    void onShowResultFinished(CCNode *node,void *data);
protected:
    void onIncClicked(CCNode *node,void *data);
    void onDecClicked(CCNode *node,void *data);
protected:
    std::string m_handString,m_plateString,m_frameString,m_inString;
    CCSprite *m_handSprite;
    CCSprite *m_plateSprite;
    CCSprite *m_frameSprite;
    CCSprite *m_inSprite;
    FSizeCCNodeDelegate *m_handDele;
    FSizeCCNodeDelegate *m_plateDele;
    FSizeCCNodeDelegate *m_frameDele;
    FSizeCCNodeDelegate *m_inDele;
    CCNode *m_wonShowSprite;
    int m_plateGridNum;
protected:
    std::vector<std::string> m_props;
    std::vector<int> m_payRate;
protected:
    CCActionEase* m_plateSpeed;
    CCActionEase* m_frameSpeed;
    bool m_plateFinished;
    bool m_frameFinished;
    bool m_usePropGot;
protected:
    float m_force;
protected:
    std::string m_goldImg;
    int m_goldNum;
    CCLabelBMFont *m_goldSprite;
protected:
    CCLabelBMFont *m_betNumSprite;
    BasButton *m_incButton;
    BasButton *m_decButton;
    int m_betMinNum;
    int m_betMaxNum;
    int m_betOnNum;
protected:
    std::vector<TurnPlateBetInfo> m_betResults;
};
}
#endif
