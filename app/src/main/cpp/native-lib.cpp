//Java
#include <jni.h>
//C++
#include <iostream>
#include <fstream>
#include <memory>
//Android
#include <android/log.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getMac(JNIEnv *env, jobject) {
	std::fstream my_file;
	std::string mac;
	std::string path = "/sys/class/net/wlan0/address";
	jint sdk;
	jclass cls;
	jfieldID getSdk;

	cls = env->FindClass("android/os/Build$VERSION");
	if(env->ExceptionCheck()){
		env->ExceptionDescribe();
	}
	getSdk = env->GetStaticFieldID(cls,"SDK_INT", "I");
	if(env->ExceptionCheck()){
		env->ExceptionDescribe();
	}
	sdk = env->GetStaticIntField(cls,getSdk);
	if(env->ExceptionCheck()){
		env->ExceptionDescribe();
	}
	env->DeleteLocalRef(cls);


	if( sdk >= 28){
		path = "/sys/class/net/p2p0/address";
	}

	my_file.open(path, std::ios::in);
	if (!my_file) {
		return env->NewStringUTF("File not found");
	}

	my_file >> mac;
	my_file.close();


	return env->NewStringUTF(mac.c_str());

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getAndroidVersion(JNIEnv *env, jobject) {
	jclass androidOsCls = (env)->FindClass("android/os/Build$VERSION");
	jfieldID getOsVersion = env->GetStaticFieldID(androidOsCls, "RELEASE", "Ljava/lang/String;");
	auto androidVs = (jstring) env->GetStaticObjectField(androidOsCls, getOsVersion);
	return androidVs;
}
