#ifndef _gamemodel_h_
#define _gamemodel_h_
#include "gametype.h"

class GameModel
{
public:
    GameModel();
    virtual ~GameModel();
    void setGameMode(GameType::RunType model){ m_gameModel = model;}
    GameType::RunType getGameModel(){ return m_gameModel;}
    bool isBattleModel(){return m_gameModel == GameType::RunType_Battle;}
    bool isTdModel(){ return m_gameModel == GameType::RunType_Td;}
    bool isTollModel() { return m_gameModel == GameType::RunType_EndLess;}
    bool isEndLessModel() { return m_gameModel == GameType::RunType_EndLess;}
    bool isSuchModel(GameType::RunType model) { m_gameModel == model;}
protected:
    GameType::RunType m_gameModel;
};

#endif
