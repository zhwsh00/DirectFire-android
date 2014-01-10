#ifndef __MD5CHECKIMPL_H__
#define __MD5CHECKIMPL_H__

#include "md5check.h"

class MD5Check;
class MD5CheckImpl
{
public:
    MD5CheckImpl(MD5Check *md5Check) : m_md5Check(md5Check){};
    virtual ~MD5CheckImpl(){};
    
    virtual const string& getStringMD5(const string& str){return m_md5;}
    virtual const string& getFileMD5(const string& path){return m_md5;}
    virtual const string& getLocalMD5(){return m_md5;}
    
protected:
    MD5Check* m_md5Check;
    string m_md5;
};
extern MD5CheckImpl* __createMD5Check(MD5Check* md5Check);

#endif /* __MD5CHECKIMPL_H__ */

