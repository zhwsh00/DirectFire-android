#ifndef _sysutils_h_
#define _sysutils_h_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void getCurrSystemTime(long &sec,long &usec);
void logCurrSystemTime(int index);
void saveFileToFs(const std::string &file,const std::string &data);
time_t getCurrGMTSec();
time_t getCurrLocalSec();
void getCurrGMTDateTime(string& outDateTime);
time_t dateTimeToSec(const string& dateTime);
void secToDateTime(string& outDateTime, time_t localSec);
int timeDiffToDay(const std::string &time);
void mailToNickName(const std::string &mail,std::string &name);
void readFilesFromDir(const std::string &dir,std::vector<std::string> &files,const std::string &postfix);
double difftimeval(const struct timeval *tv1, const struct timeval *tv2);
bool isSpecialChar(char c);
bool hasSpecialChar(std::string& text);
#endif
