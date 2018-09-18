
/*
Java调用C和C++函数时的JNI使用区别:
注意：jni.h头文件中对于***.c  &  ***.cpp采用不同的定义

在C的定义中,env是一个两级指针,而在C++的定义中,env是个一级指针
C形式需要对env指针进行双重deferencing，而且须将env作为第一个参数传给jni函数

jclass (JNICALL *GetObjectClass)   (JNIEnv *env, jobject obj);
jclass GetObjectClass(jobject obj)
{
    return functions->GetObjectClass(this,obj);
}


对于***.c
1.jclass test_class = (*env)->GetObjectClass(env, obj);
2.jfieldID id_num = (*env)->GetFieldID(env, test_class, "num", "I");

对于 ***.cpp
1.jclass test_class = env->GetObjectClass(obj);
2.jfieldID id_num = env->GetFieldID(test_class, "num", "I");

在 C 中，
JNI 函数调用由“(*env)->”作前缀，目的是为了取出函数指针所引用的值。
在 C++ 中，
JNIEnv 类拥有处理函数指针查找的内联成员函数。

下面将说明这个细微的差异，其中，这两行代码访问同一函数，但每种语言都有各自的语法。
C 语法：jsize len = (*env)->GetArrayLength(env,array);
C++ 语法：jsize len =env->GetArrayLength(array);


*/


#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>


extern "C" {

extern int value_from_c();

}

JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
    int iValue = value_from_c();
	printf("hello in c native code./n");
	char a[100] = {"hello world from_cpp_i_c."};

	sprintf(a,"hello world from_cpp_i_c[%d].",iValue);

	return (env)->NewStringUTF(a);
}

#define JNIREG_CLASS "com/example/ndk_onload/jni_onload"//指定要注册的类

/**
* Table of methods associated with a single class.
*/
static JNINativeMethod gMethods[] = {
	{ "test_jni_onload_cpp_i_c", "()Ljava/lang/String;", (void*)native_hello },//绑定
};

/*
* Register several native methods for one class.
*/
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;
	clazz = (env)->FindClass( className);
	if (clazz == NULL) {
		return JNI_FALSE;
	}
	if ((env)->RegisterNatives(clazz, gMethods, numMethods) < 0) {
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

	if ((vm)->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
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
