#设置路径
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := jni_onload_native_cpp_i_c
LOCAL_SRC_FILES := jni_onload_native_cpp_i_c.cpp return_c.c

include $(BUILD_SHARED_LIBRARY)