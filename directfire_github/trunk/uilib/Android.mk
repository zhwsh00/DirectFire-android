LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := uilib_static
LOCAL_MODULE_FILENAME := libuilib
LOCAL_CFLAGS :=   -B V=1
LOCAL_CPPFLAGS :=   -B V=1

LOCAL_SRC_FILES := \
				actions/absnodeaction.cpp \
				actions/animeffectaction.cpp \
				actions/moveinaction.cpp \
				actions/moveoutaction.cpp \
				actions/scaleeffectaction.cpp \
				actions/shineeffectaction.cpp \
				actions/swayeffectaction.cpp \
				base/absanchor.cpp \
				base/dialog.cpp \
				base/frame.cpp \
				base/inputbox.cpp \
				base/namegenerator.cpp \
				base/scrollarea.cpp \
				base/scrollbar.cpp \
				base/sizepolicy.cpp \
				base/textarea.cpp \
				base/touchnode.cpp \
				base/uithemedef.cpp \
				base/uithemesetting.cpp \
				base/widget.cpp \
				base/absanimsprite.cpp \
				effectsprite/cardsprite.cpp \
				skin/absareaskin.cpp \
				skin/absskin.cpp \
				widgets/absfixedsizewidget.cpp \
				widgets/absscrollwidget.cpp \
				widgets/absshowdialog.cpp \
				widgets/autofitwidget.cpp \
				widgets/autoscrollwidget.cpp \
				widgets/busydialog.cpp \
				widgets/chatfacingdialog.cpp \
				widgets/chatphrasedialog.cpp \
				widgets/chatwidgetlayer.cpp \
				widgets/circleprogressbar.cpp \
				widgets/fillborderwidget.cpp \
				widgets/filltestwidget.cpp \
				widgets/floatingdelegatewidget.cpp \
				widgets/fsizeccnodedelegate.cpp \
				widgets/fsizecontainerlayer.cpp \
				widgets/fsizelabeldelegate.cpp \
				widgets/fsizenulldelegate.cpp \
				widgets/fsizespritedelegate.cpp \
				widgets/fsizewidgetcontainer.cpp \
				widgets/fsizewidgetdelegate.cpp \
				widgets/horprogressbar.cpp \
				widgets/hortriprogressbar.cpp \
				widgets/labelmessagedialog.cpp \
				widgets/loginregdialog.cpp \
				widgets/popbuttonsdialog.cpp \
				widgets/querydialog.cpp \
				widgets/turnplatedialog.cpp \
				lang/langsetting.cpp \
				lang/langdef.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/../
					
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/. \
		$(LOCAL_PATH)/../ \
		$(LOCAL_PATH)/../../../cocos2dx/platform/third_party/android/prebuilt/libxml2/include \
		$(LOCAL_PATH)/../../../cocos2dx/ \
		$(LOCAL_PATH)/../../../cocos2dx/include \
		$(LOCAL_PATH)/../../../cocos2dx/kazmath/include \
		$(LOCAL_PATH)/../../../cocos2dx/platform \
		$(LOCAL_PATH)/../../../cocos2dx/platform/android \
		$(LOCAL_PATH)/../../../CocosDenshion/include \
		$(LOCAL_PATH)/../../../extensions \
		$(LOCAL_PATH)/../../../cocos2dx/platform/third_party/android/prebuilt/libxml2/include \
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