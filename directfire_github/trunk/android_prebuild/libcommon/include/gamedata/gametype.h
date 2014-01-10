#ifndef _gametype_h_
#define _gametype_h_
class GameType
{
public:
    enum RunType{
        RunType_Battle,
        RunType_Td,
        RunType_Toll,
        RunType_EndLess
    };

    enum GameRunSpeed{
        GameSpeed_Normal = 0,
        GameSpeed_Faster,
        GameSpeed_Fastest
    };

	enum AnimationType{
		DeadType,
		BornType,
		ChangeTribeType,
		ChangeColorType,
		ExplosionType
	};
	enum GameLanguage{
		English = 0,
		Chinese,
		Japanese,
		French,
		LangDefault
	};
	enum GamePlayerTribe{
		Tribe_undefined,
        Tribe_random,
		Tribe_human,
        Tribe_undead,
        Tribe_orc,
		Tribe_nightelf,
		Tribe_dragon,
		Tribe_sprite,
		Tribe_hell,
		Tribe_fort,
		Tribe_tower,
        Tribe_ghost,
		Tribe_dungeon,
        Tribe_grave,
		Tribe_element
	};
	enum GameStatus{
		GameInit = 0,
		GameLoading,
		GamePrepare,
		GameRunning,
		GameSpell,
		GameSetting,
		GamePause,
		GameSilent,
        GameMagicForbid,
		GameOver
	};
	enum GameAttackStatus{
		AttackStatus_undefined = 0,
		/* for shootball */
		AttackStatus_alignment_rollball = 1 << 0,
		AttackStatus_enemy_rollball = 1 << 1,
		AttackStatus_alignment_base = 1 << 2,
		AttackStatus_enemy_base = 1 << 3,
		AttackStatus_alignment_shootball = 1 << 4,
		AttackStatus_enemy_shootball = 1 << 5,
		AttackStatus_self = 1 << 6,
		/* for unorder ball */
		AttackStatus_unoder_self_rollball = 1 << 7,
		AttackStatus_unoder_self_base = 1 << 8,
		AttackStatus_unoder_self_shootball = 1 << 9,
		AttackStatus_unoder_alignment_rollball = 1 << 10,
		AttackStatus_unoder_alignment_base = 1 << 11,
		AttackStatus_unoder_alignment_shootball = 1 << 12,
		AttackStatus_unoder_enemy_rollball = 1 << 13,
		AttackStatus_unoder_enemy_base = 1 << 14,
		AttackStatus_unoder_enemy_shootball = 1 << 15,
		AttackStatus_alignment_unorder = 1 << 16,
		AttackStatus_enemy_unorder = 1 << 17,
        /* for alignment ball */
        AttackStatus_alignment_balls = AttackStatus_alignment_rollball | AttackStatus_alignment_shootball,
        /* for enemy ball */
        AttackStatus_enemy_balls = AttackStatus_enemy_rollball | AttackStatus_enemy_shootball,
        AttackStatus_all = 0xFFFFFFFF
	};
	enum GamePlayerType{
        LocalUser = 0,
		Computer,
		RemoteUser,
		Observer
	};
	enum GamePlayerStatus{
		Init,
		Running,
		Death
	};
	enum GamePlayerCamp{
		GamePlayerCamp_none,
		GamePlayerCamp_1,
		GamePlayerCamp_2,
		GamePlayerCamp_3,
		GamePlayerCamp_4,
		GamePlayerCamp_5
	};
	enum GameNetworkType{
		BattleNet,
		LocalNet,
		StandAlone
	};
	enum GamePlayType{
		Campaign,
		Tollgate,
        MultiOnline,
        Endless
	};
	enum RenderZValue{
        zPropsBonusSpell = 1000,
        zPropsContainer = 700,
		zUnorderBall = 695,
		zPropsEffect = 692,
		zPropsSpell = 691,
		zProps = 590,
		zBallCollisionEffect = 410,
		zSpecialBallEffect = 420,
		zMapBg = 0,
        zMapFg = 1000,
        zSkyLittleAnim = 999,
        zGroundLittleAnim = 1,
		zPropsBall = 396,
		zEffectBall = 395,
		zCurrPlayerSpecialBall = 295,
        zCurrPlayerShootBall = 294,
        zCurrPlayerShooter = 178,//288,set same to batchNode
		zCurrPlayerPathCover = 292,
		zCurrPlayerEffect = 291,
		zCurrPlayerBall = 290,
        zCurrPlayerBatchNode = 179,//289,//change same to aligh
        zCurrPlayerPath = 178,//288,//all self align Path to same
		zAlignmentSpecialBall = 185,
		zAlignmentShootBall = 184,
        zAlignmentShooter = 178,
		zAlignmentPathCover = 182,
		zAlignmentEffect = 181,
		zAlignmentBall = 180,
        zAlignmentBatchNode = 178,
        zAlignmentPath = 177,
		zEnemySpecialBall = 75,
		zEnemyShootBall = 74,
        zEnemyShooter = 68,
		zEnemyPathCover = 72,
		zEnemyEffect = 71,
		zEnemyBall = 70,
		zEnemyBatchNode = 69,
		zEnemyPath = 68
	};
	GameType();
	~GameType();
};
#endif
