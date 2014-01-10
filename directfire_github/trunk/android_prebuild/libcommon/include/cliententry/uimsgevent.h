#ifndef _uimsgevent_h_
#define _uimsgevent_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

class UiMsgEv
{
public:
    enum PlayerInfoType{
        Self,
        Friend,
        Other
    };
    enum MsgSendObjType{
        MsgToUser = 0,
        MsgToUserPublic,
        MsgToUserPrivate,
        MsgToRoomAll,
        MsgToHallAll
    };
    enum HerosType{
        HeroLevel = 0,
        HeroGold,
        HeroPlayed,
        HeroWon,
        HeroLose
    };
    enum GameChangeType{
        BallColorChange
    };

    typedef struct PlayerTypeEv
    {
        void setType(PlayerInfoType type){
            m_type = type;
        }
        bool isSelf(){
            return m_type == Self;
        }
        bool isFriend(){
           return m_type == Friend;
        }
        bool isOther(){
            return m_type == Other;
        }
        PlayerInfoType m_type;
    }PlayerTypeEv;

    typedef struct AccountInfoEv
    {
        std::string m_id;
        std::string m_mail;
        std::string m_name;
        std::string m_password;
        short m_sex;
    }AccountInfoEv;
    typedef struct PlayerInfoEv : public PlayerTypeEv
    {
        PlayerInfoEv(){
            m_playedNum = 0;
            m_wonNum = 0;
            m_losedNum = 0;
            m_offlineNum = 0;
            m_escapeNum = 0;
            m_level = 0;
            m_exp = 0;
            m_cap = 0;
            m_intell = 0;
            m_energy = 0;
            m_lucky = 0;
            m_leader = 0;
            m_thumb = 0;
            m_foot = 0;
            m_isValid = false;

            m_seatIndex = 0;
            m_origSeatIndex = 0;
            m_mapPos = 0;
            m_userIndex = 0;
        }
        bool m_isValid;

        std::string m_userId;
        std::string m_userMail;
        std::string m_nickName;
        std::string m_creditName;
        std::string m_gameName;
        std::string m_portraitUpTime;
        std::string m_headName;
        std::string m_propertyUpTime;
        std::string m_friendUpTime;
        std::string m_propsUpTime;
        std::string m_playing;
        std::string m_hostId;
        short m_playedNum;
        short m_wonNum;
        short m_losedNum;
        short m_offlineNum;
        short m_escapeNum;
        short m_level;
        int m_exp;
        int m_cap;
        int m_intell;
        int m_energy;
        int m_lucky;
        int m_leader;
        int m_thumb;
        int m_foot;

        //game related
        int m_seatIndex;
        int m_origSeatIndex;
        int m_mapPos;
        int m_userIndex;
        int m_tribe;
        int m_camp;
        int m_playerType;
    }PlayerInfoEv;
    typedef struct SocialPropEv : public PlayerTypeEv
    {
        std::string m_uid;
    }SocialPropEv;
    typedef struct GiftPropEv
    {
        GiftPropEv(int id,int count){
            m_id = id;
            m_count = count;
        }
        GiftPropEv(){
            m_id = 0;
            m_count = 0;
        }

        int m_id;
        int m_count;
    }GiftPropEv;
    typedef struct RoomMapInfoEv{
        RoomMapInfoEv(){
            m_mapId = 0;
            m_roomsCount = 0;
            m_inMapUserCount = 0;
            m_coinCost = 0;
            m_alignNum = 0;
            m_suppNum = 0;
            m_mapWidth = 0;
            m_mapHeight = 0;
            m_mapType = 0;
        }
        RoomMapInfoEv(int id,int count,int userCount,int type = 0){
            m_mapId = id;
            m_roomsCount = count;
            m_inMapUserCount = userCount;
            m_mapType = type;
            m_coinCost = 0;
            m_alignNum = 0;
            m_suppNum = 0;
            m_mapWidth = 0;
            m_mapHeight = 0;
        }
        int m_mapId;
        int m_roomsCount;
        int m_inMapUserCount;
        int m_coinCost;
        int m_alignNum;
        int m_suppNum;
        int m_mapWidth;
        int m_mapHeight;
        int m_mapType;
        std::string m_mapFile;
        std::string m_mapName;
        std::string m_mapAbbrevName;
    }RoomMapInfoEv;
    typedef struct RoomInfoEv {
        void clear(){
            m_mapName.clear();
            m_mapAbbrevName.clear();
            m_mapId = -1;
            m_coinGolds = 0;
            m_bonusGolds = 0;
            m_hostIndex = -1;
            m_userIndex = -1;
            m_playerNum = 0;
            m_alignNum = 0;
            m_suppNum = 0;
            m_playerInfo.clear();
            m_mapWidth = 0;
            m_mapHeight = 0;
        }
        void reservePlayerNum(int num){
            if(m_playerInfo.size() != 0)
                m_playerInfo.clear();
            for(int i = 0;i < num;i++){
                m_playerInfo.push_back(new PlayerInfoEv);
            }
        }

        void setNewHostId(const std::string &id){
            for(unsigned int i = 0;i < m_playerInfo.size();i++){
                if(!m_playerInfo[i]->m_isValid)
                    continue;
                if(m_playerInfo[i]->m_userId == id){
                    m_hostId = id;
                    m_hostIndex = i;
                    return;
                }
            }
        }
        void userQuit(){
            m_playerNum--;
        }
        void userJoin(){
            m_playerNum++;
        }
        std::string m_mapFile;
        std::string m_mapName;
        std::string m_mapAbbrevName;
        std::string m_hostId;
        int m_mapId;
        int m_coinGolds;
        int m_bonusGolds;
        int m_hostIndex;
        int m_userIndex;
        short m_playerNum;
        int m_alignNum;
        int m_suppNum;
        int m_mapWidth;
        int m_mapHeight;
        std::vector<PlayerInfoEv *> m_playerInfo;
        float m_startAfter;
    }RoomInfoEv;
    typedef struct ChatInfo{
        int m_chatType;
        std::string m_senderId;
        std::string m_senderMail;
        std::string m_senderNickName;
        std::string m_revId;
        std::string m_revMail;
        std::string m_revNickName;
        std::string m_chatContent;
    }ChatInfo;
    typedef struct GameInitInfo{
        float m_startDelay;
        float m_startServerTimeSec;
        float m_startServerTimeUSec;
        float m_gameServerStep;
        int m_gameSyncStep;
        int m_syncCount;
        int m_gameModel;
        std::vector<int> m_playerSeed;
        std::vector<int> m_playerTheme;
        std::vector<int> m_playerType;
        std::vector<int> m_playerCamp;
    }GameInitInfo;
    typedef struct GameSyncInfo{
        int m_syncSource;//==-1,from game-server(in battle model),other from user(in other model)
        int m_serverFrame;
        int m_syncCount;
        long m_serverSec;
        long m_serverUSec;
    }GameSyncInfo;
    typedef struct AskFriendInfo{
        AskFriendInfo(){
            m_isOnline = false;
        }
        std::string m_friendId;
        std::string m_friendMail;
        std::string m_friendNick;
        std::string m_askWord;
        bool m_isOnline;
    }AskFriendInfo;
    typedef struct PropDef{
        PropDef(){
            m_type = -1;
            m_count = 0;
        }
        PropDef(int type,int count){
            m_type = type;
            m_count = count;
        }
        int m_type;
        int m_count;
    }PropDef;
    typedef struct RoomUsePropDef{
        std::string m_sender;
        std::string m_receiver;
        int m_type;
        int m_count;
    }RoomUsePropDef;
    typedef struct ForceQuitGameInfo{
        std::vector<PropDef> m_punish;
    }ForceQuitGameInfo;

    typedef struct KickOutInfo{
        std::string m_kickerId;
        std::string m_kickerMail;
        std::string m_kickerNick;

        std::string m_outerId;
        std::string m_outerMail;
        std::string m_outerNick;
        int m_seatIndex;
    }KickOutInfo;
    typedef struct AwardTaskInfo{
        AwardTaskInfo(){
            m_limitTime = 0;
        }
        std::string m_taskKey;
        std::string m_taskDesc;
        std::string m_startTime;
        std::string m_endTime;
        int m_limitTime;
        std::vector<UiMsgEv::PropDef> m_awards;
    }AwardTaskInfo;
    typedef struct ThumbPortrait{
        void clear(){
            m_ids.clear();
            m_heads.clear();
        }

        std::vector<std::string> m_ids;
        std::vector<std::string> m_heads;
    }ThumbPortrait;
    typedef struct PropExchangeRule{
        int m_propType;
        int m_priceType;
        std::string m_propName;
        std::string m_priceName;
        int m_buyPriceCount;
        int m_salePriceCount;
        bool m_reverse;
    }PropExchangeRule;
    typedef struct HeroInfo{
        std::string m_userId;
        std::string m_userMail;
        std::string m_nickName;
        std::string m_headName;
        int m_propCount;
        int m_playedNum;
        int m_wonNum;
        int m_losedNum;
        int m_level;
        int m_exp;
    }HeroInfo;
    typedef struct HerosInfo{
        HerosType m_sortType;
        void clear(){
            m_heros.clear();
        }
        std::vector<HeroInfo> m_heros;
    }HerosInfo;
    typedef struct UserRank{
        HerosType m_sortType;
        int m_sortNum;
    }UserRank;
    typedef struct UserClickInfo{
        int m_userIndex;
        float m_x;
        float m_y;
        int m_attach;
    }UserClickInfo;
    typedef struct UserUsePropInfo{
        int m_userIndex;
        float m_x;
        float m_y;
        float m_rotation;
        int m_attach;
        std::string m_type;
    }UserUsePropInfo;
    typedef struct GameChangeInfo{
        GameChangeType m_type;
        int m_userIndex;
        int m_attach;
        int m_origValue;
        int m_changeValue;
    }GameChangeInfo;

    typedef struct PropsSelected{
        void clear(){
            m_num = 0;
            m_props.clear();
        }

        int m_num;
        std::vector<std::string> m_props;
    }PropsSelected;
    typedef struct MapInfo{
        MapInfo(){

        }

        int m_mapId;
        int m_maxPlayer;
        int m_maxAlign;
        int m_costGolds;
        int m_width;
        int m_height;
        std::string m_gateId;
        std::string m_mapName;
        std::string m_mapAbbvName;
        int m_mapType;
    }MapInfo;
    typedef struct GameResultInfo{
        GameResultInfo(){
            m_goldBulking = 0;
            m_expBulking = 0;
            m_levelFinal = 0;
            m_expFinal = 0;
            m_won = 0;
            m_camp = 0;
            m_seat = 0;
            m_cap = 0;
            m_levelUp = 0;
            m_head = 0;
        }

        std::string m_id;
        std::string m_nick;
        std::string *m_head;
        int m_goldBulking;
        int m_expBulking;
        int m_levelFinal;
        int m_expFinal;
        int m_camp;
        int m_seat;
        int m_cap;
        bool m_won;
        bool m_levelUp;
    }GameResultInfo;

    typedef struct LoginInfo{
        LoginInfo(const std::string &ip,int port){
            m_ip = ip;
            m_port = port;
        }

        std::string m_ip;
        int m_port;
    }LoginInfo;
    typedef struct BnServerInfo{
        BnServerInfo(const std::string &ip,int port,int route,int maxUser,int olUser){
            m_ip = ip;
            m_port = port;
            m_route = route;
            m_maxUser = maxUser;
            m_onlineUser = olUser;
        }
        ~BnServerInfo(){

        }
        string m_ip;
        int m_port;
        int m_route;
        int m_maxUser;
        int m_onlineUser;
    }BnServerInfo;
    typedef std::map<int, BnServerInfo> RouteServerMap;
    typedef struct RoutesInfo{
        RouteServerMap& servers(){ return m_servers;}
        RouteServerMap m_servers;
    }RoutesInfo;
    typedef struct IAPInfo{
        int m_verifyStatus;
        int m_quantity;
        int m_coinNum;
        string m_uid;
        string m_receipt;
        string m_productId;
        string m_transactionId;
        string m_purchaseDate;
        string m_appItemId;
        string m_bid;
        string m_bvrs;
        string m_detail;
    }IAPInfo;
    UiMsgEv();
    ~UiMsgEv();
};

extern bool prop_sortbyId(UiMsgEv::GiftPropEv t1,UiMsgEv::GiftPropEv t2);
extern bool prop_sortByCount(const UiMsgEv::GiftPropEv t1,const UiMsgEv::GiftPropEv t2);
extern bool game_sortByCost(UiMsgEv::RoomMapInfoEv t1,UiMsgEv::RoomMapInfoEv t2);
extern bool game_sortByOnlineNum(UiMsgEv::RoomMapInfoEv t1,UiMsgEv::RoomMapInfoEv t2);
extern bool game_sortByMapName(UiMsgEv::RoomMapInfoEv t1,UiMsgEv::RoomMapInfoEv t2);
extern bool game_sortByRoomNum(UiMsgEv::RoomMapInfoEv t1,UiMsgEv::RoomMapInfoEv t2);
extern bool gameResult_sortBySeatIndex(UiMsgEv::GameResultInfo t1,UiMsgEv::GameResultInfo t2);
#endif
