#设置路径
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := jni_onload_native_cpp
LOCAL_SRC_FILES := jni_onload_native.cpp
#LOCAL_SRC_FILES := ../../jniLibs/$(TARGET_ARCH_ABI)/ljni_onload_native_c_i_cpp.so

include $(BUILD_SHARED_LIBRARY)