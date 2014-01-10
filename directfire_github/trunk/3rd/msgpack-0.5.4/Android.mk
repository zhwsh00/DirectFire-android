LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := msgpack_shared

LOCAL_MODULE_FILENAME := libmsgpack

LOCAL_SRC_FILES := \
		src/objectc.c \
		src/unpack.c \
		src/version.c \
		src/vrefbuffer.c \
		src/zone.c \
		src/object.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src

LOCAL_CPPFLAGS    += -fexceptions
                                                   
include $(BUILD_SHARED_LIBRARY)
