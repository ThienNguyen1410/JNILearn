#include <jni.h>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>

jstring charTojstring(JNIEnv* env, const char* pat) {
    jclass strClass = (env)->FindClass("java/lang/String");
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
    jstring encoding = (env)->NewStringUTF("GB2312");
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getMacAddress(JNIEnv *env, jobject thiz) {
    jclass networkInterface_cls = env->FindClass("java/net/NetworkInterface");
    if (networkInterface_cls == 0) {
        return env->NewStringUTF("");
    }
    jmethodID jgetByName = env->GetStaticMethodID(networkInterface_cls,"getByName", "(Ljava/lang/String;)Ljava/net/NetworkInterface;");
    if (jgetByName == 0){
        return env->NewStringUTF("");
    }
    std::string wlan0_jni = "wlan0";
    jstring  wlan0 = env->NewStringUTF(wlan0_jni.c_str());
    jobject getByName = env->CallStaticObjectMethod(networkInterface_cls,jgetByName,wlan0);
    jmethodID getHardwareAddr = env->GetMethodID(networkInterface_cls,"getHardwareAddress", "()[B");
    if(getHardwareAddr == 0){
        return env->NewStringUTF("");
    }
    jbyteArray callGetHardwareAddr = (jbyteArray) env->CallObjectMethod(getByName,getHardwareAddr);

    jbyte *byteData = env->GetByteArrayElements(callGetHardwareAddr,0);
    jsize byteArrLen = env->GetArrayLength(callGetHardwareAddr);

#define BYTE unsigned char
    int len = byteArrLen;
    char *data = (char*) env->GetByteArrayElements(callGetHardwareAddr,0);
    char *temp = new char[len*2 + 1];
    memset(temp,0,len*2 + 1);
    for (int i = 0; i < len ; i++){
        char* buffer = new char[2];
        memset(buffer,0,2);
        sprintf(buffer,"%02X",data[i]);
        memcpy(temp+i*2,buffer,2);
        delete[] buffer;
    }
    jstring macAddress = charTojstring(env,temp);
    delete [] temp;
    return macAddress;

}




