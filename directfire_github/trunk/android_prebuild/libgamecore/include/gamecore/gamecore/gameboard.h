#ifndef _gameboard_h_
#define _gameboard_h_
/* this class include all the necessary info to game
 *
 */
#include <vector>
#include <list>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "gamedata/gametype.h"
#include "resource/resourcemgr.h"
#include "asyncrunmgr.h"
#include "absruncontroll.h"

#include "serverinterface.h"
#include "cliententry/uimsghandler.h"
#include "cliententry/uimsgevent.h"

class BasGamePlayer;
class Ball2DRenderHelper;
class SysSetting;
class PropsSpellMgr;
class PropsWidget;
class GamePanel;
class StartEffect;
class ReplayFile;
class	Map2DRenderHelper;
class	BattleMapRenderHelper;
class	Ball2DShootRenderHelper;
class	Ball2DUnorderRenderHelper;
class	SpecialBall2DRenderHelper;
class	Props2DRenderHelper;
class   LevelManager;
class GameRunMgr;
class GameOperProxy;
class GameSettingProxy;
class BallEffectMgr;
using namespace cocos2d;
class BasMap;
class SyncRunController;
class WonDialog;
class LostDialog;
class CallEvenDialog;
class PlayerAsyncRunMgr;
class BasShooter;
class BasBall;
class BallFactory;
class GameBoard : public cocos2d::CCLayer,public AsyncRunMgr,public BasRunControll
{
    friend class GamePanel;
    friend class PropsWidget;
	friend class BattleMapRenderHelper;
	friend class GameRunMgr;
	friend class GameSettingProxy;
	friend class GameOperProxy;
	friend class BallEffectMgr;
	friend class SpecialBallEffectMgr;
    friend class CircleSpecialAction;
	friend class PropsSpellMgr;
    friend class PlayerAsyncRunMgr;
    friend class StartEffect;
public:
	typedef struct BallInfo{
        BallInfo();
        ~BallInfo();
		GameType::GamePlayerType m_playerType;
		BasShooter *m_mapShooter;
		BasBall *m_ballStart;
		BasBall *m_ballEnd;
		std::list<BasBall *> m_shootBallList;
		std::vector<BasBall *> m_prepareBallList;
		std::list<BasBall *> m_unorderBallList;
		CCSpriteBatchNode *m_batchNode;
        CCSpriteBatchNode *m_shootBatchNode;
        CCSpriteBatchNode *m_unorderBatchNode;
		std::vector<int> m_doubleHits;
        int m_tdBallLeft;
        int m_tdBallSum;
	}BallInfo;
	GameBoard();
	GameBoard(const std::string &map);
	~GameBoard();
    CREATE_FUNC(GameBoard)
    void startGame();
    void stopGame();
    void pauseGame();
    bool initEndLessGame();
    bool initBattleGame(UiMsgEv::GameInitInfo *init);
    void setColorRangeByUserIndex(int index);
    void setColorRangeByMapIndex(int index);
	void setGameMap(const std::string &map);
	void setGamePlayType(GameType::GamePlayType type);
	void setGameNetworkType(GameType::GameNetworkType net);
	void setPlayers(const std::vector<BasGamePlayer*> &players);
    void setMapOffset(const CCPoint &pos,float scale);
    void shootBall(int userIndex,const CCPoint &pos,int attach,bool isReal);
    void useProp(int userIndex,const std::string &type,const CCPoint &pos,float rotation,int attach,bool isReal);
    void gameChange(UiMsgEv::GameChangeInfo *info);
    void showChangeBallEffect(BasBall *ball);
    void convertScenePosToMapPos(CCPoint &pos);
    void getGameBoardSize(CCSize &size);
    void quitGame();
    void leaveRoom();
public:
    void onBallHalfEffectChange(CCNode *sender,void *data);
    void onBallFullEffectChange(CCNode *sender,void *data);
public:
    void serverListener(CCNode *sender,void *type);
protected:
    //players
	std::vector<BasGamePlayer*> m_boardPlayers;
    //player async run mgr
    std::vector<PlayerAsyncRunMgr*> m_asyncRunMgrs;
    //game model
    GameModel m_gameModel;
	int m_currPlayerIndex;
    std::string m_boardMap;
	GameType::GamePlayType m_gamePlayType;
	GameType::GameNetworkType m_gameNetworkType;
protected:
    virtual void update(float fDelta);
    virtual void update(float fDelta,int userindex);
    virtual void draw();
protected:
    //draw
    void drawMap();
    void drawBall();
protected:
	bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	void pausedClicked();
	void settingClicked();
    bool spellClicked(const std::string &spell);
	void cancelSpellClicked();
    bool execSpellClicked(const std::string &prop);
	void finishSpell();
	bool isOnSpell();
protected:
	void initVariable();
    bool init();
    void initGame();
    void clearGame();
    void initBall();
    void findCurrPlayerIndex();
    bool isRunning() { return m_isRunning;}
    inline int currPlayerIndex() { return m_currPlayerIndex;}
    void initPrepareBall();
    void clearPrepareBall();
    void initShootBall();
    void clearShootBall();
    void insertBalltoHead(int index,BasBall *ball);
    void insertBallToTail(int index,BasBall *ball);
    void removeBall(int index,BasBall *ball);
    BasBall *createBall(const std::string &name,int theme,int index,int radius,int color,int type = 0,int randtype = 0);
	void initRenderHelper();
    void updateRendeerHelperMap();
	void initGameSetting();
	void initGameOper();
	void initSysSetting();
	void initBallEffect();
	void initProps();
    void initResourceMgr();
	GameType::GameStatus gameStatus();
	void pushGameStatus(GameType::GameStatus status);
    void resumeGameStatus(GameType::GameStatus status);
    void checkWrongGameStatus();
	int gameAttackStatus();
	void pushGameAttackStatus(int);
	void resumeGameAttackStatus();
protected:
    void addAnimNode(CCNode *anim,int zorder);
    void removeAnimNode(CCNode *anim,bool cleanup = false);
    void clearAnimNode();
protected:
    void onAddLittleAnim(float dt);
protected:
    virtual void runFastCatchToSync(int userIndex = -1);
    virtual void runFinishedWaitForSync(int userIndex = -1);
    virtual void waitFinishedRunForSync(int userIndex = -1);
public:
    void printRealBallInfo(int frame);
protected:
    void startCountDown();
    void startCountDownShow(float dt);
    void countDownFinished(CCNode *node,void *data);
protected:
    virtual void clientFrameStep();
    void syncNumCount();
    void addNormalBalls();
    void addNormalBalls(int userIndex,int num,float speedRate);
    void addBonusBalls(int mapIndex,int ballnum);
    void addBonusSpell(int mapIndex,int ballnum,const CCPoint &pos);
    void addBonusSpellByDoubleHit(int mapIndex,int hitnum,const CCPoint &pos);
    void gotBonusSpell(int mapIndex,int spellType,const std::string &spellName,CCSprite *sprite);
    void playerDeath(int pindex);
    void haveWon();
    void timeUsedOut();
    void genGameResult();
    void takeScreenShot();
    void shakeGameBoard(const std::string &name,int force = 1);
    void playSpellSound(const std::string &name);
    void stopSpellSound(const std::string &name);
    void playSound(int type);
protected:
    void successResultGot(std::vector<UiMsgEv::GameResultInfo> *results);
    void failedResultGot();
    void onWonDialogCloseClicked(CCNode *node,void *data);
    void onWonDialogOkClicked(CCNode *node,void *data);
    void onLostDialogCloseClicked(CCNode *node,void *data);
    void onLostDialogOkClicked(CCNode *node,void *data);
    void onCallEvenDialogCloseClicked(CCNode *node,void *data);
    void onCallEvenDialogOkClicked(CCNode *node,void *data);
protected:
    void oneBallReachEnd(int playerIndex);
protected:
    //ball data
    std::vector<BallInfo*> m_ballsVector;
    CCTexture2D *m_ballBatchNodeTex;
    //map data
    BasMap *m_map;
    //render helper
	Ball2DRenderHelper *m_2dBallRender;
	Map2DRenderHelper *m_2dMapRender;
	BattleMapRenderHelper *m_battleMapRender;
	Ball2DShootRenderHelper *m_2dShootBallRender;
	Ball2DUnorderRenderHelper *m_2dUnorderBallRender;
	SpecialBall2DRenderHelper *m_2dSpecialBallRender;
	Props2DRenderHelper *m_2dPropsRender;
    LevelManager *m_levelMgr;
	BallFactory *m_ballFactory;
	//game run manager
	GameRunMgr *m_gameRunMgr;
	//game setting proxy
	GameSettingProxy *m_gameSettingProxy;
	//game oper proxy
	GameOperProxy *m_gameOperProxy;
	//sys setting
	SysSetting *m_sysSetting;
	//effect mgr
    BallEffectMgr *m_ballEffectMgr;
    //props status bar
	PropsSpellMgr *m_propsSpellMgr;
    PropsWidget *m_propsWidget;
    GamePanel *m_gamePanel;
	//Resource mgr
	ResourceMgr *m_resourceMgr;
	//game status
	std::vector<GameType::GameStatus> m_statusVector;
	std::vector<int> m_attackVector;
    //sync run mgr
    bool m_isRunning;
    SyncRunController *m_syncRunController;
    //map scale
    CCPoint m_mapOffset;
    float m_mapScale;
    //server interface
    ServerInterface *m_serverIFace;
    //room
    UiMsgEv::RoomInfoEv *m_roomEv;
    //game result
    std::vector<UiMsgEv::GameResultInfo> m_gameResults;
    //counter down timer
    CCLabelBMFont *m_downTimer;
    //cocos2d-x add schedule
    bool m_touchAdded;
protected:
    //added ball in fixed time
    int m_addBallSyncNum;
    int m_currSyncGot;
protected:
    //spell,magic batchNode
    CCSpriteBatchNode *m_animBatchNode;
protected:
    ReplayFile *m_replayFile;
    bool m_replayRecord;
    bool m_offerRecord;
protected:
    WonDialog *m_wonDialog;
    LostDialog *m_lostDialog;
    CallEvenDialog *m_callevenDialog;
protected:
    int m_ssIndex;
protected:
    //playing sound mgr
    std::map<int,int> m_soundMgr;
protected:
    //start effect
    StartEffect *m_startEffect;
};
#endif
