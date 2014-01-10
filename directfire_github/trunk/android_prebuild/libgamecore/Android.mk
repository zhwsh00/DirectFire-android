LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libgamecore_static
LOCAL_MODULE_FILENAME := gamecore
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libgamecore.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
