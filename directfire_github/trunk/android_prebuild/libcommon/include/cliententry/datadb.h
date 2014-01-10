#ifndef _datadb_h_
#define _datadb_h_
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

#include "sqlite/sqlite3.h"

#include "uimsgevent.h"

class PropsInfoMessage;
class DataDb
{
public:
    DataDb();
    ~DataDb();
    void setDbInfo(const std::string &dir,const std::string &name);
    bool isOpened();
    void init();
    void save();
    bool hasRecord(const std::string& sqlCmd);
    bool needRestoreTransaction();
    bool getRestoreTransactions(vector<UiMsgEv::IAPInfo>& iapMsgs);
    bool recordTransaction(UiMsgEv::IAPInfo& iapMsg);
    bool getHeadPortrait(const std::string &uid,std::string &head,std::string &time);
    void insertHeadPortrait(const std::string &uid,const std::string &head,const std::string &time);
    bool getLatestLoginedInfo(UiMsgEv::AccountInfoEv& accountInfo);
    bool updateLatestLoginedInfo(UiMsgEv::AccountInfoEv& accountInfo);
    bool getPlayerInfo(const std::string &uid,UiMsgEv::PlayerInfoEv *ev);
    bool getPlayerPortraitUpTime(const std::string &uid,std::string &time);
    bool getPlayerPropsUpTime(const std::string &uid,std::string &time);
    bool getPlayerFriendUpTime(const std::string &uid,std::string &time);
    void insertPlayerInfo(const std::string &uid,UiMsgEv::PlayerInfoEv *ev);
    bool getFriendInfo(const std::string &uid,std::vector<std::string> &uids);
    void insertFriendInfo(const std::string &uid,const std::vector<std::string> &fid);
    void deleteFriendInfo(const std::string &uid,const std::string &fid);
    bool getPlayerProps(const std::string &uid,std::string &time,std::vector<UiMsgEv::GiftPropEv> &props);
    bool getPlayerProps(const string &uid,std::string &time,PropsInfoMessage *props);
    void insertPlayerProps(const string &uid, const string &time,PropsInfoMessage *props);
    void insertPlayerProps(const std::string &uid,const std::string &time,const std::vector<UiMsgEv::GiftPropEv> &props);
protected:
    bool isHeadPortraitTablExist();
    void createHeadPortraitTable();
protected:
    bool isPlayerInfoTableExist();
    void createPlayerInfoTable();
protected:
    bool isFriendInfoTableExist();
    void createFriendInfoTable();
protected:
    bool isPropsTableExist();
    void createPropsTable();
protected:
    bool isIAPReceiptTableExist();
    void createIAPReceiptTable();
protected:
    void createAccountInfoTable();
protected:
    std::string m_dbDir;
    std::string m_dbName;
protected:
    sqlite3 *m_db;
    char *m_errMsg;
    std::string m_sqlCmd;
    int m_dbResult;
};

#endif
