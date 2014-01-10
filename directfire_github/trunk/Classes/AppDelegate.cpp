#include "AppDelegate.h"
#include "gamecore/gamecore/gamescene.h"
#include "gamecore/splash/splashscene.h"
#include "gamecore/serverinterface.h"
#include "iap/IAPHelper.h"
#include "netdetect/netdetect.h"
#include "photo/photohelper.h"
#include "gamecore/utils/fileutils.h"
#include "crypto/md5check.h"
#include "utils/kmconfigcomlib.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    IAPHelper::getInstance()->unRegisterListener(ServerInterface::getInstance());
}

bool AppDelegate::applicationDidFinishLaunching() {
    if(1){
        // permission check
        MD5Check checker;
        string binraryPath = "DirectFire";
        getAbsoluteResourceFilePath(binraryPath);
        string resPath = "resfile.dat";
        getAbsoluteResourceFilePath(resPath);
        string dbPath = "db/localsettingdb.sqlit";
        getAbsoluteResourceFilePath(dbPath);

        string binraryMD5 = checker.getFileMD5(binraryPath);
        string resMD5 = checker.getFileMD5(resPath);
        string dbMD5 = checker.getFileMD5(dbPath);
        string localMD5 = checker.genLocalMD5(binraryMD5.append(resMD5).append(dbMD5));
        cout << "gen local=" << localMD5 << " get local=" << checker.getLocalMD5() << " gen remote=" << checker.genLocalMD5(binraryMD5.append(resMD5).append(dbMD5)) << endl;
    // open here when release
    //    if (localMD5.compare(checker.getLocalMD5()) != 0) {
    //        return false;
    //    }
        ServerInterface::getInstance()->setRemoteMD5(checker.genLocalMD5(binraryMD5.append(resMD5).append(dbMD5)));
    }
    // init iap transaction observer
    IAPHelper::getInstance()->registerListener(ServerInterface::getInstance());
    // init net detecter observer
    NetDetect::getInstance()->registerListener(ServerInterface::getInstance());
    // init photo picker
    PhotoHelper::getInstance()->registerListener(ServerInterface::getInstance());
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // use this selection when release
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(size.width, size.height, kResolutionShowAll);

    // turn on display FPS
    //pDirector->setDisplayStats(true);
    pDirector->setProjection(kCCDirectorProjection2D);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30);
    // run
    pDirector->runWithScene(SplashScene::create());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    ServerInterface::getInstance()->applicationDidEnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    ServerInterface::getInstance()->applicationWillEnterForeground();
}
