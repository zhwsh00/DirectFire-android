#ifndef __PHOTOHELPER_H__
#define __PHOTOHELPER_H__

#include <iostream>
#include <vector>
using namespace std;

#define KM_ENABLE_TAKEPHOTO_USECAMERA 0

class PhotoListener;
class PhotoHelperImpl;
class PhotoHelper
{
private:
    PhotoHelper();
    virtual ~PhotoHelper();
    static PhotoHelper *m_instance;
public:
    static PhotoHelper *getInstance();
    
    void registerListener(PhotoListener* photoListener);
    void unRegisterListener(PhotoListener* photoListener);
    
    void takePhoto();
    void takePhotoFinished(const char* imageData, int len, const char* imageDataHq, int lenHq);
    void takePhotoFailed();
    void takePhotoCanceled();
    
    void savePhotosAlbum(const char *imageData, int len, int w, int h);

public:
    void setLangCancel(string cancel) {m_langCancel = cancel;}
    const string& langCancel() {return m_langCancel;}
    void setLangChooseImage(string langChooseImage) {m_langChooseImage = langChooseImage;}
    const string& langChooseImage() {return m_langChooseImage;}
    void setLangTakePhoto(string langTakePhoto) {m_langTakePhoto = langTakePhoto;}
    const string& langTakePhoto() {return m_langTakePhoto;}
    
protected:
    PhotoHelperImpl* m_photoHelperImpl;
    vector<PhotoListener*> m_photoListeners;
    
protected:
    string m_langCancel;
    string m_langChooseImage;
    string m_langTakePhoto;
};

#endif /* __PHOTOHELPER_H__ */

