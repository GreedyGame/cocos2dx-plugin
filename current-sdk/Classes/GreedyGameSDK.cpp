
/****************************************************************************
 Copyright (c) 2014      GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#include "GreedyGameSDK.h"
#include "cocos2d.h"
#include <iostream>
#include <vector>



#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

#define  GreedyGame_CLASS_NAME "com/greedygame/android/cocos2dx/AdsGreedyGame"

namespace greedygame
{
    void (*onInitCallback)(int);
    void (*onDownloadCallback)(float);

    extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onEvent(JNIEnv* env, jobject thiz, jint ret)
        {
            if(ret == GG_CAMPAIGN_CACHED || ret == GG_CAMPAIGN_DOWNLOADED){

                std::string path = GreedyGameSDK::getActivePath();
                CCLOG("activepath %s", path.c_str());
                
                std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
                searchPaths.insert (searchPaths.begin(), path);
                CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
            }

            onInitCallback(ret);
        }
        
        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onDownload(JNIEnv* env, jobject thiz, jfloat ret)
        {
            onDownloadCallback(ret);
        }
#endif
        
    }


    void GreedyGameSDK::initialize(const char *appId, void (*init_callback)(int), void (*progress_callback)(float))
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"initializeGreedyGameJNI"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(appId);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
            onInitCallback = init_callback;
            onDownloadCallback = progress_callback;

            /**Setting pref**/
            std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();;
            searchPaths.push_back("greedygame");
            CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        }
#endif
    }



    std::string GreedyGameSDK::_getActivePath(){
        std::string path("");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActivePathGreedyGameJNI"
                                                    ,"()Ljava/lang/String;"))
        {
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID);
            path = JniHelper::jstring2string(str);
        }
#endif
        return path;
    }

    void GreedyGameSDK::cancelDownload() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"cancelDownloadGreedyGameJNI"
                                                    ,"()V"))
        {
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }

    void GreedyGameSDK::setDebug(bool d) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"setDebugGreedyGameJNI"
                                                    ,"(Z)V"))
        {
            jboolean jb = JNI_FALSE;
            if(d){
                jb = JNI_TRUE;
            }
            t.env->CallStaticVoidMethod(t.classID,t.methodID, jb);
        }
#endif
    }

    void GreedyGameSDK::fetchAdHead(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"fetchAdHeadGreedyGameJNI"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif
    }

    void GreedyGameSDK::removeAdHead(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"removeAdHeadGreedyGameJNI"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif
    }

    void GreedyGameSDK::setPath() {
        std::string path = GreedyGameSDK::_getActivePath();
        CCLOG("activepath %s", path.c_str());
        
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert (searchPaths.begin(), path);
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }

    void GreedyGameSDK::onCustomEvent(const char *event_name){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"onCustomEvent"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(event_name);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif        
    }
}
