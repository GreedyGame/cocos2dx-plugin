
/****************************************************************************
 Copyright (c) 2014      GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#include "GreedyGameAgent.h"
#include "cocos2d.h"
#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <string>






#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

#define  GreedyGame_CLASS_NAME "com/greedygame/android/platforms/cocos2dx/GreedyGame"

namespace greedygame
{

    CampaignStateListener* stateListener;
    CampaignProgressListener* progressListener;
    
    extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onAvailable(JNIEnv* env, jobject thiz)
        {
            if(stateListener) stateListener->onAvailable();
        }
        
        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onUnavailable(JNIEnv* env, jobject thiz)
        {
            if(stateListener) stateListener->onUnavailable();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onFound(JNIEnv* env, jobject thiz)
        {
            if(stateListener) stateListener->onFound();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onProgress(JNIEnv* env, jobject thiz, jint ret)
        {
            if(progressListener) progressListener->onProgress(ret);
        }
#endif
        
    }

    void android_main(struct android_app* state) {
        
    }


    void GreedyGameAgent::init()
    {
    
        #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"init"
                                                    ,"()V")) {

        // CCLOG("NIKHIL INSIDE INIT Cocos game init 2A classID - %d and methodID - %d ", t2.classID, t2.methodID);
        //  cocos2d::JniHelper::getMethodInfo(t, "org/cocos2dx/cpp/AppActivity"
        //                                             ,"getApplicationContext"
        //                                             ,"()V");   
        // CCLOG("NIKHIL INSIDE INIT Cocos game init 2B classID - %d and methodID - %d ", t.classID, t.methodID);
        // jclass cl = t.env->FindClass("org/cocos2dx/cpp/AppActivity");
        // CCLOG("NIKHIL INSIDE INIT Cocos game init 3");
        // jmethodID methodContext = t.env->GetMethodID(cl,"getApplicationContext","()Landroid/content/Context;");
        // CCLOG("NIKHIL INSIDE INIT Cocos game init 4 %d ", methodContext);
        // jobject context = t.env->CallObjectMethod(cl,methodContext);
        // CCLOG("NIKHIL INSIDE INIT Cocos game init 5");
        // t.env->CallStaticVoidMethod(t.classID,t.methodID,context);
        // CCLOG("NIKHIL INSIDE INIT  2 Cocos game init 6");
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }


    void GreedyGameAgent::setCampaignStateListener(CampaignStateListener* _listener)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            stateListener = _listener;
#endif
    }

    void GreedyGameAgent::setCampaignProgressListener(CampaignProgressListener* _listener)
    {
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            progressListener = _listener;
#endif
    }

    
    void GreedyGameAgent::showFloat(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"showFloat"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif
    }



    void GreedyGameAgent::removeFloat(const char *unit_id){
        CCLOG("removeFloatUnit");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"removeFloat"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID,StringArg1);
        }
#endif
    }


    void GreedyGameAgent::forcedExit(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"forcedExit"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }


     void GreedyGameAgent::showUII(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"showUII"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif        
    }


std::string GreedyGameAgent::getNativeUnitPath(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getNativeUnitPath"
                                                    ,"(Ljava/lang/String;)Ljava/lang/String;"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }



    std::string GreedyGameAgent::getFloatUnitPath(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getFloatUnitPath"
                                                    ,"(Ljava/lang/String;)Ljava/lang/String;"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }

}
