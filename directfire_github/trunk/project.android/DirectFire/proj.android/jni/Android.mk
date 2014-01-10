LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := \
					hellocpp/main.cpp

                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../ \
					$(LOCAL_PATH)/../../../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static ev_shared msgpack_shared uilib_static gameui_static      
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

$(call import-module,directfire_github/trunk/3rd/libev-android) \
$(call import-module,directfire_github/trunk/3rd/msgpack-0.5.4)  \
$(call import-module,directfire_github/trunk/uilib) \
$(call import-module,directfire_github/trunk/gameui) \
$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)