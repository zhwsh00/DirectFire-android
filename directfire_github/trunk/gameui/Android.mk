LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gameui_static

LOCAL_MODULE_FILENAME := libgameui

LOCAL_SRC_FILES := 	../Classes/AppDelegate.cpp \
					battle.net/abssocialitem.cpp \
					battle.net/addfrienddialog.cpp \
					battle.net/askasfrienddialog.cpp \
					battle.net/askfriendwidget.cpp \
					battle.net/baspage.cpp \
					battle.net/basscalewidget.cpp \
					battle.net/ccimagecliper.cpp \
					battle.net/chatwidget.cpp \
					battle.net/coin2golddialog.cpp \
					battle.net/delfrienddialog.cpp \
					battle.net/frienditem.cpp \
					battle.net/friendspage.cpp \
					battle.net/friendtitle.cpp \
					battle.net/gamepage.cpp \
					battle.net/gamepageitem.cpp \
					battle.net/gamepagetitle.cpp \
					battle.net/giftwidget.cpp \
					battle.net/guessspellitem.cpp \
					battle.net/halllayer.cpp \
					battle.net/hallmainwidget.cpp \
					battle.net/hallpage.cpp \
					battle.net/hallscene.cpp \
					battle.net/headportraitwidget.cpp \
					battle.net/headsettingdialog.cpp \
					battle.net/herositem.cpp \
					battle.net/herospage.cpp \
					battle.net/herostitle.cpp \
					battle.net/iapgiftshow.cpp \
					battle.net/invitetoroomdialog.cpp \
					battle.net/kickoutdialog.cpp \
					battle.net/levelexpshow.cpp \
					battle.net/mailwidget.cpp \
					battle.net/noticeshow.cpp \
					battle.net/okdialog.cpp \
					battle.net/prop2golddialog.cpp \
					battle.net/propexdialog.cpp \
					battle.net/propshow.cpp \
					battle.net/propsyndialog.cpp \
					battle.net/recgiftshow.cpp \
					battle.net/roomgameshow.cpp \
					battle.net/roomlayer.cpp \
					battle.net/roommainwidget.cpp \
					battle.net/roomroleshow.cpp \
					battle.net/roomscene.cpp \
					battle.net/sendgiftdialog.cpp \
					battle.net/sendmsganim.cpp \
					battle.net/sendmsgdialog.cpp \
					battle.net/shoppage.cpp \
					battle.net/socialpage.cpp \
					battle.net/socialshow.cpp \
					battle.net/sys/abssyspage.cpp \
					battle.net/sys/creditintropage.cpp \
					battle.net/sys/facebookpage.cpp \
					battle.net/sys/feedbackpage.cpp \
					battle.net/sys/gamerulepage.cpp \
					battle.net/sys/screenshotpage.cpp \
					battle.net/sys/sinapage.cpp \
					battle.net/sys/spellintropage.cpp \
					battle.net/sys/syssettingpage.cpp \
					battle.net/sys/systitle.cpp \
					battle.net/sys/tribeintropage.cpp \
					battle.net/sys/twitterpage.cpp \
					battle.net/sysawarddialog.cpp \
					battle.net/syspage.cpp \
					battle.net/taskshowdialog.cpp \
					battle.net/taskwidget.cpp \
					battle.net/thumbfootitem.cpp \
					battle.net/turnplateitem.cpp \
					battle.net/usershow.cpp \
					battle.net/waitingmoreitem.cpp \
					battle.net/wonshow.cpp \
					mainmenulayer.cpp \
					menuscene.cpp \
					standalone/endlessscene.cpp \
					uistatus.cpp



LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/ \
					$(LOCAL_PATH)/../

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/../ \
					$(LOCAL_PATH)/../gamecore/ \
					$(LOCAL_PATH)/../../../cocos2dx/platform/third_party/android/prebuilt/libxml2/include \
					$(LOCAL_PATH)/../../../cocos2dx/ \
					$(LOCAL_PATH)/../../../cocos2dx/include \
					$(LOCAL_PATH)/../../../cocos2dx/kazmath/include \
					$(LOCAL_PATH)/../../../cocos2dx/platform \
					$(LOCAL_PATH)/../../../cocos2dx/platform/android \
					$(LOCAL_PATH)/../../../CocosDenshion/include \
					$(LOCAL_PATH)/../../../extensions \
					$(LOCAL_PATH)/../android_prebuild/libcommon/include \
		$(LOCAL_PATH)/../android_prebuild/libgamecore/include \
		$(LOCAL_PATH)/../android_prebuild/libgamecore/include/gamecore

LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libcommon_static cocos_libgamecore_static

LOCAL_STATIC_LIBRARIES += -L$(LOCAL_PATH)/../../../cocos2dx/platform/third_party/android/prebuilt/libxml2/libs/armeabi -lxml2
LOCAL_STATIC_LIBRARIES += -L$(LOCAL_PATH)/../android_prebuild/libcommon/libs/armeabi -lcommon
LOCAL_STATIC_LIBRARIES += -L$(LOCAL_PATH)/../android_prebuild/libgamecore/libs/armeabi -lgamecore
include $(BUILD_STATIC_LIBRARY)
$(call import-module,libcommon)
$(call import-module,libgamecore)