#ifndef __PHOTOHELPERIMPL_H__
#define __PHOTOHELPERIMPL_H__

#include "photohelper.h"

class PhotoHelper;
class PhotoListener;
class PhotoHelperImpl
{
public:
    PhotoHelperImpl(PhotoHelper *photoHelper) : m_photoHelper(photoHelper){m_listener = 0;};
    virtual ~PhotoHelperImpl(){};
    
    virtual void takePhoto(){};
    virtual void savePhotosAlbum(const char *imageData, int len, int w, int h){};
    void setListener(PhotoListener *listener) { m_listener = listener;}
    PhotoListener *getListener() { return m_listener;}
protected:
    PhotoHelper* m_photoHelper;
protected:
    PhotoListener *m_listener;
};
extern PhotoHelperImpl* __createPhotoHelper(PhotoHelper* photoHelper);

#endif /* __PHOTOHELPERIMPL_H__ */

