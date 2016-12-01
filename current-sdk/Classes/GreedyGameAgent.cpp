
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

    IAgentListener* listener;

    extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onAvailable(JNIEnv* env, jobject thiz)
        {
            listener->onAvailable();
        }
        
        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onUnavailable(JNIEnv* env, jobject thiz)
        {
            listener->onUnavailable();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onFound(JNIEnv* env, jobject thiz)
        {
            listener->onFound();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onProgress(JNIEnv* env, jobject thiz, jint ret)
        {
            listener->onProgress(ret);
        }

        

#endif
        
    }


    void GreedyGameAgent::init(IAgentListener* _listener)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"init"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
            listener = _listener;
            
        }
#endif
    }



    std::string GreedyGameAgent::getCampaignPath(){
        std::string path("");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getCampaignPath"
                                                    ,"()Ljava/lang/String;"))
        {
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID);
            path = JniHelper::jstring2string(str);
        }
#endif
        return path;
    }

    
    void GreedyGameAgent::fetchFloatUnit(const char *unit_id){
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



    void GreedyGameAgent::removeAllFloatUnits(){
        CCLOG("removeAllFloatUnits");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"removeAllFloat"
                                                    ,"()V"))
        {
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }

    void GreedyGameAgent::removeFloatUnit(const char *unit_id){
        CCLOG("removeAllFloatUnits");
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


     void GreedyGameAgent::showEngagementWindow(const char *unit_id){
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


std::string GreedyGameAgent::getNativeUnitPathById(const char *unit_id){
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



    std::string GreedyGameAgent::getFloatUnitPathById(const char *unit_id){
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
