#ifndef __PHOTOLISTENER_H__
#define __PHOTOLISTENER_H__

class PhotoListener
{
public:    
    PhotoListener(){};
    virtual ~PhotoListener(){};
    
    virtual void takePhotoFinished(const char* imageData, int len, const char* imageDataHq, int lenHq) = 0;
    virtual void takePhotoFinished(const char* imageFile){}
    virtual void takePhotoFailed() = 0;
    virtual void takePhotoCanceled() = 0;
};

#endif /* __PHOTOLISTENER_H__ */

