#ifndef _roomgameshow_h_
#define _roomgameshow_h_
#include "uilib/uilib.h"

using namespace uilib;

#include <string>
#include <vector>
#include <map>

class RoomMainWidget;
class RoomGameShow : public BorderWidget
{
public:
    RoomGameShow(RoomMainWidget *owner);
    virtual ~RoomGameShow();
    void reset();
    void setMapInfo(int id,const std::string &name,const std::string &abbrev);
    void setIsHost(bool host);
    void setQuitImg(const std::string &normal,const std::string &pressed);
    void setStartImg(const std::string &normal,const std::string &pressed);
    void setBonusImg(const std::string &normal,const std::string &pressed);
    void setSpellImg(const std::string &normal,const std::string &pressed);
    void setQuitCB(CCNode *listener,SEL_CallFuncND func);
    void setStartCB(CCNode *listener,SEL_CallFuncND func);
    void setBonusCB(CCNode *listener,SEL_CallFuncND func);
    void setSpellCB(CCNode *listener,SEL_CallFuncND func);
    void setSpellMaxNum(int num);
    void updateSpellNum(int num);
    int getSpellNum();
    void getSpellSelected(int &num,std::vector<std::string> &spells);
    void enableStartAfterSec(int sec);
protected:
    void layoutCompleted();
protected:
    void enableStartStep(float dt);
    void setStartQuitButtons();
    void onSpellNumButtonClicked(CCNode *node,void *data);
protected:
    void onSpellClicked(CCNode *node,void *data);
protected:
    RoomMainWidget *m_owner;
protected:
    int m_mapId;
    std::string m_mapName;
    std::string m_mapAbbrev;
protected:
    CCNode *m_quitListener;
    SEL_CallFuncND m_quitFunc;
    CCNode *m_startListener;
    SEL_CallFuncND m_startFunc;
    CCNode *m_bonusListener;
    SEL_CallFuncND m_bonusFunc;
    CCNode *m_spellListener;
    SEL_CallFuncND m_spellFunc;
protected:
    std::string m_quitImg,m_quitPressedImg;
    std::string m_startImg,m_startPressedImg;
    std::string m_bonusImg,m_bonusPressedImg;
    std::string m_spellImg,m_spellPressedImg;
protected:
    int m_spellMaxNum;
    int m_spellNum;
    HorScrollWidget *m_spellWidget;
    BasButton *m_quitButton;
    BasButton *m_startButton;
    BasButton *m_spellNumButton;
protected:
    CCLabelBMFont *m_spellNumSprite;
protected:
    bool m_roomHost;
protected:
    std::vector<FSizeSpriteDelegate*> m_selected;
    int m_selNum;
    BasWidget *m_containerWidget;
};

#endif
