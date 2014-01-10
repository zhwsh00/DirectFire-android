#ifndef _fileutils_h_
#define _fileutils_h_
#include <string>
#include <fstream>
using namespace std;
extern bool isFileExist(const std::string &file);
extern bool isResourceFileExist(const std::string &relativePath);
extern void getAbsoluteResourceFilePath(std::string &file);
extern void getAbsoluteResourceRootPath(std::string &file);
extern long getFileSize(const std::string &file);
extern bool isMailAddress(const std::string &mail);
#endif
