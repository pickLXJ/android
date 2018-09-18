#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>


int value_from_cpp();

JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
    int iValue = value_from_cpp();
    printf("hello in c native code./n");
    char a[100];

    sprintf(a,"hello world from_c_i_cpp[%d].",iValue);
	return (*env)->NewStringUTF(env,a);
}

#define JNIREG_CLASS "com/example/ndk_onload/jni_onload"//指定要注册的类

/**
* Table of methods associated with a single class.
*/
static JNINativeMethod gMethods[] = {
	{ "test_jni_onload_c_i_cpp", "()Ljava/lang/String;", (void*)native_hello },//绑定
};

/*
* Register several native methods for one class.
*/
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;
	clazz = (*env)->FindClass( env,className);
	if (clazz == NULL) {
		return JNI_FALSE;
	}
	if ((*env)->RegisterNatives(env,clazz, gMethods, numMethods) < 0) {
		return JNI_FALSE;
	}

	return JNI_TRUE;
}


/*
* Register native methods for all classes we know about.
*/
static int registerNatives(JNIEnv* env)
{
	if (!registerNativeMethods( env,JNIREG_CLASS, gMethods,
                                 sizeof(gMethods) / sizeof(gMethods[0])))
		return JNI_FALSE;

	return JNI_TRUE;
}

/*
* Set some test stuff up.
*
* Returns the JNI version on success, -1 on failure.
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	if ((*vm)->GetEnv(vm,(void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return -1;
	}
	assert(env != NULL);

	if (!registerNatives(env)) {//注册
		return -1;
	}
	/* success -- return valid version number */
	result = JNI_VERSION_1_4;

	return result;
}
