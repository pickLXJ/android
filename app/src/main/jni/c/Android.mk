#设置路径
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := jni_onload_native_c
LOCAL_SRC_FILES := jni_onload_native.c

include $(BUILD_SHARED_LIBRARY)