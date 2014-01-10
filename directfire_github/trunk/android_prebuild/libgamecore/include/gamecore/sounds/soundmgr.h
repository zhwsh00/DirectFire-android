#ifndef _soundmgr_
#define _soundmgr_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/userdata/userdata.h"
#include "soundenum.h"
#include "soundloader.h"

class SoundMgr
{
private:
    static SoundMgr *m_instance;
    SoundMgr();
    ~SoundMgr();
    
public:
    static SoundMgr *getInstance();
    
    // bg sound
    void playSoundBg(const char* pszFilePath, bool bLoop);
    void playSoundBg(int bgType, bool bLoop=true);
    void stopSoundBg();
    void pauseSoundBg();
    void resumeSoundBg();
    void pauseAllSound();
    void resumeAllSound();
    
    // effect
    void playEffect(int effectType);
    int playEffectReturnId(int effectType);
    void stopEffect(int id);
    
    // all sound control
    void switchBgSoundOn(bool on);
    void switchGameSoundOn(bool on);
    
    bool isBgSoundOn();
    bool isGameSoundOn();
    
private:
    void initSound();
    void initSoundBgVolume();
    void initSoundGameVolume();
    void setBgSoundOn(bool on);
    void setGameSoundOn(bool on);
    
private:
    SoundLoader m_soundLoader;
    
private:
    bool m_bgSoundOn;
    bool m_gameSoundOn;
    string m_currentBgSoundPath;
    
    CCUserDefault *m_userSettings;
};

#endif
