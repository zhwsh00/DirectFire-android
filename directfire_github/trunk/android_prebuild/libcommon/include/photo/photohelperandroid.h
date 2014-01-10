#ifndef _photohelperandroid_h_
#define _photohelperandroid_h_
#define android 1
#if (android == 1)
#include "photohelperimpl.h"
#include "common/thread/absthread.h"
#include "common/listener/threadevent.h"
#include "common/listener/absevent.h"
#include "common/listener/abslistener.h"
enum TakePhotoEvent{
    FindTakePhotoAPI,
    NoFindTakePhotoAPI,
    TakeFailed,
    TakeSuccess
};
class PhotoEvent : public BasEvent
{
public:
    PhotoEvent();
    PhotoEvent(int childtype);
    ~PhotoEvent();
    int childType() { return (int)m_childType;}
    void setChildType(int type) {m_childType = type;}
protected:
    int m_childType;
};

class TakePhotoAndroidWorker
{
public:
    TakePhotoAndroidWorker(BasThread *thread);
    virtual ~TakePhotoAndroidWorker();
    void start();
    void stop();
protected:
    BasThread *m_thread;
};

class TakePhotoAndroidThread : public BasThread
{
public:
    TakePhotoAndroidThread();
    virtual ~TakePhotoAndroidThread();
    virtual void finish();
protected:
    void run();
protected:
    TakePhotoAndroidWorker *m_worker;
};

class PhotoHelper;
class PhotoHelperImplAndroid : public PhotoHelperImpl,public BasListener
{
public:
    PhotoHelperImplAndroid(PhotoHelper* photoHelper);
    virtual ~PhotoHelperImplAndroid();
    const std::string &getPngName() { return m_pngName;}
    virtual void takePhoto();
    virtual void savePhotosAlbum(const char *imageData, int len, int w, int h);
    virtual void notify(int id, BasEvent::EventType event_type, BasEvent *event, void *sender);
protected:
    TakePhotoAndroidThread *m_thread;
    std::string m_pngName;
};

#endif
#endif
