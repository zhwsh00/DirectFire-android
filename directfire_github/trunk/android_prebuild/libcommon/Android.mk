LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libcommon_static
LOCAL_MODULE_FILENAME := common
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libcommon.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
