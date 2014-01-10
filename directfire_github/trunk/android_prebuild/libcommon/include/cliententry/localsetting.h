#ifndef LOCALSETTING_H
#define LOCALSETTING_H
#include <string>
#include <iostream>
using namespace std;

#include "sqlite/sqlite3.h"
#include "network/common/netcommon.h"

/**
 * local read only db
 */
class LocalSetting
{
public:
    LocalSetting();
    ~LocalSetting();
    void setDBPath(const string& dbPath);
    void loadDB();
    bool isOpened();
    bool getMapsInfo(DBMapInfosMessage& mapInfoMsg);
    bool getPropExchangeRules(PropExchangeRulesMessage& rulesMsg);
    bool getLevelInfo(CharLevelMessage& levelInfo);
    bool getPropSynthRules(PropSynthRulesMessage& rulesMsg);
    bool getTaskRules(TaskRulesMessage& allRules);

private:
    bool getLevelCap(CharLevelMessage::CharLevelData& levelData);
    bool getLevelGift(CharLevelMessage::CharLevelData& levelData);
    bool getTaskAwards(TaskRuleMessage& rule);

private:
    string m_dbPath;
    sqlite3 *m_db;
    string m_sqlCmd;
    char *m_errMsg;
    int m_dbResult;
};

#endif // LOCALSETTING_H
