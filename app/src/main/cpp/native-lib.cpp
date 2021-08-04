//Java
#include <jni.h>
//C++
#include <iostream>
#include <fstream>
#include <memory>
//Android
#include <android/log.h>


jstring getMac(JNIEnv *env) {
	std::fstream my_file;
	std::string mac;
	std::string path = "/sys/class/net/wlan0/address";
	jint sdk;
	jclass cls;
	jfieldID getSdk;

	cls = env->FindClass("android/os/Build$VERSION");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
		return env->NewStringUTF("");
	}
	getSdk = env->GetStaticFieldID(cls, "SDK_INT", "I");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
		return env->NewStringUTF("");

	}
	sdk = env->GetStaticIntField(cls, getSdk);
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
		return env->NewStringUTF("");
	}
	env->DeleteLocalRef(cls);


	if (sdk >= 28) {
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

jstring getAndroidVersion(JNIEnv *env) {
	jclass cls;
	cls = (env)->FindClass("android/os/Build$VERSION");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
		return env->NewStringUTF("");
	}
	jfieldID getOsVersion = env->GetStaticFieldID(cls, "RELEASE", "Ljava/lang/String;");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}
	auto androidVs = (jstring) env->GetStaticObjectField(cls, getOsVersion);
	env->DeleteLocalRef(cls);
	return androidVs;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_myapplication_MainActivity_getResult(JNIEnv *env, jobject thiz) {
	jclass cls = env->FindClass("android/os/Build");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	jfieldID getDevice = env->GetStaticFieldID(cls, "DEVICE", "Ljava/lang/String;");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	jfieldID getModel = env->GetStaticFieldID(cls, "MODEL", "Ljava/lang/String;");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	jfieldID getHardware = env->GetStaticFieldID(cls, "HARDWARE", "Ljava/lang/String;");
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	auto device = (jstring) env->GetStaticObjectField(cls, getDevice);
	auto model = (jstring) env->GetStaticObjectField(cls, getModel);
	auto hardware = (jstring) env->GetStaticObjectField(cls, getHardware);

	jobjectArray result = env->NewObjectArray(5, env->FindClass("java/lang/String"), nullptr);

	env->SetObjectArrayElement(result, 0, device);
	env->SetObjectArrayElement(result, 1, model);
	env->SetObjectArrayElement(result, 2, hardware);
	env->SetObjectArrayElement(result, 3, getAndroidVersion(env));
	env->SetObjectArrayElement(result, 4, getMac(env));

	env->DeleteLocalRef(device);
	env->DeleteLocalRef(model);
	env->DeleteLocalRef(hardware);
	env->DeleteLocalRef(cls);

	return result;
}
