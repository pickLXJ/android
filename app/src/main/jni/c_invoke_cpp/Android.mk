#设置路径
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := jni_onload_native_c_i_cpp
LOCAL_SRC_FILES := jni_onload_native_c_i_cpp.c return_cpp.cpp

include $(BUILD_SHARED_LIBRARY)