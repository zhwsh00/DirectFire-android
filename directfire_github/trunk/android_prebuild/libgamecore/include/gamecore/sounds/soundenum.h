#ifndef _soundenum_h_
#define _soundenum_h_
class SoundEnum
{
public:
    enum SoundTypeEnum{
            // game bg sound
            CURRENT_BG_SOUND = 100, //当前背景音乐
            MAINMENU_BG_SOUND,      //登陆界面背景音乐
            GAME_BG,                //游戏背景音效
            turnplateWon = 150,
            // social effect
            BTN_EFFECT_NORMAL = 200,  //普通按钮点击声音
            BTN_GOT_MSG,		//得到留言，好用申请
            BTN_SEND_MSG,		//发送留言，赠送礼物，道具
            GOT_CHAT,			//得到聊天信息
            USER_JOIN,			//用户加入房间
            USER_QUIT,			//用户退出房间
            KICK_USER,			//kick用户
            SNEER_USER,			//嘲讽用户
            PRAISE_USER,		//赞美用户
            ADD_PROP,			//增加选择
            SUB_PROP,			//减少选择
            GOT_PROP,			//得到物品
            PLATE_ROTATE,		//转盘转动
            // spell effect
            SPELL_ICEARROW = 300, //冰箭释放
            SPELL_BLACKHOLE	,	//黑洞释放
            SPELL_THUNDERBALL,	//雷弹释放
            SPELL_STORM,		//雷暴释放
            SPELL_OATH,			//光冲释放
            SPELL_SILENT,		//静默释放
            SPELL_MAGICFORBID,		//沙漏释放
            SPELL_WORMBALL,		//球洞释放
            SPELL_CYCLONE,		//龙卷风释放
            SPELL_DISPEL,		//驱散释放
            SPELL_WARCALL,		//召唤释放
            SPELL_WARTRAMPLE,	//践踏释放
            SPELL_DRAGON ,		//龙珠释放
            SPELL_FOG,			//笼罩释放
            // game effect
            LEVEL_UP = 400,		//用户升级
            GAME_COUNT_DOWN,	//倒计时声音
            SHOOT_OUT,			//发射出去
            INSERT_IN,			//球插入
            BALLBALL_HIT,       //玩家小球互相碰撞
            BALLBASE_HIT,       //小球和基地碰撞
            BALLEXPLODE_NORMAL, //小球普通爆炸
            DOUBHIT_1,			//1连击
            DOUBHIT_2,			//2连击
            DOUBHIT_3,			//3连击
            BALL_HIT_CATCH,		//球碰到一起赶上
            BALL_HIT_HEADON,    //球碰到一起迎头
            GAME_WON,			//胜利
            GAME_LOSE,			//失利
            SS_SHOT,			//快照
            BALL_CHANGECOLOR
    };

};


#endif
