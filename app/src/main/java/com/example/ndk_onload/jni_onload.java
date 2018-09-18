package com.example.ndk_onload;

/**
 * Created by LXUJIE on 2018/9/18.
 */

public class jni_onload {
    static{
        System.loadLibrary("jni_onload_native_c");
        System.loadLibrary("jni_onload_native_cpp");
        System.loadLibrary("jni_onload_native_cpp_i_c");
        System.loadLibrary("jni_onload_native_c_i_cpp");
    }

    public static native String test_jni_onload_c();
    public static native String test_jni_onload_cpp();
    public static native String test_jni_onload_cpp_i_c();
    public static native String test_jni_onload_c_i_cpp();

}
