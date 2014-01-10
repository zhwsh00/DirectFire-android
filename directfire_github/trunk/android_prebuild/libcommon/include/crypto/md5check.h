#ifndef __MD5CHECK_H__
#define __MD5CHECK_H__

#include <iostream>
#include <vector>
using namespace std;

class MD5CheckImpl;
class MD5Check
{
public:
    MD5Check();
    virtual ~MD5Check();
    
    const string& getStringMD5(const string& str);
    const string& getFileMD5(const string& path);
    const string& getLocalMD5();
    const string& genLocalMD5(const string& str);
    const string& genRemoteMD5(const string& str);
    
protected:
    MD5CheckImpl* m_md5CheckImpl;
    string m_md5;
};

#endif /* __MD5CHECK_H__ */

