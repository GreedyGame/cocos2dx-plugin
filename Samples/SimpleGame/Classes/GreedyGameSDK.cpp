
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

    void GreedyGameSDK::fetchAdHead(const char *unit_id, int x, int y){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"fetchAdHeadGreedyGameJNI"
                                                    ,"(Ljava/lang/String;II)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1, x, y);
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
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();

        std::string path = GreedyGameSDK::_getActivePath();
        CCLOG("activepath %s", path.c_str());
        std::string prefix("greedygame/");
        std::vector<std::string> newSearchPaths;
        std::vector<std::string>::iterator it1 = newSearchPaths.begin();
        for(std::vector<std::string>::iterator it = searchPaths.begin(); it != searchPaths.end(); ++it) {
            std::string s = *it;
            std::size_t found = s.find(prefix);
            if (found!=std::string::npos) {
                std::string p = s.substr(found + prefix.length());
                std::string n = path + "/" + p;
                it1 = newSearchPaths.insert ( it1 , path + "/" + p );
            }
        }
        it1 = searchPaths.begin();
        for(std::vector<std::string>::iterator it = newSearchPaths.begin(); it != newSearchPaths.end(); ++it) {
            it1 = searchPaths.insert ( it1 , *it );
        }

        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }
}
