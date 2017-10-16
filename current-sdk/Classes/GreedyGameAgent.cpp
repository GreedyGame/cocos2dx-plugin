
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
	#define GG_INIT "init"
    #define GG_GET_CAMPAIGN_PATH "getCampaignPath"
    #define GG_SHOW_FLOAT "showFloat"
    #define GG_REMOVE_ALL_FLOAT "removeAllFloat"
    #define GG_REMOVE_FLOAT_UNIT "removeFloat"
    #define GG_FORCED_EXIT "forcedExit"
    #define GG_SHOW_UII "showUII"
    #define GG_GET_NATIVE_PATH "getNativeUnitPath"
    #define GG_GET_FLOAT_PATH "getFloatUnitPath"
	#define GG_REFRESH "startEventRefresh"

namespace greedygame {

    IAgentListener* listener;

    extern "C" {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onAvailable(JNIEnv* env, jobject thiz,jstring id) {
	        	if(listener!=NULL) { 
	        		const char *nativeId = env->GetStringUTFChars(id, 0);
	            	listener->onAvailable(nativeId);
	            	env->ReleaseStringUTFChars(id, nativeId);
	            }
	        }
	        
	        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onUnavailable(JNIEnv* env, jobject thiz)
	        {
	        	if(listener!=NULL) {
	            	listener->onUnavailable();
	            }
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onFound(JNIEnv* env, jobject thiz)
	        {
	        	if(listener!=NULL) {
	            	listener->onFound();
	            }
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onError(JNIEnv* env, jobject thiz, jstring msg)
	        {
	        	if(listener!=NULL) {
	            	const char *nativeString = env->GetStringUTFChars(msg, 0);
	            	listener->onError(nativeString);
					env->ReleaseStringUTFChars(msg, nativeString);
				}
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_platforms_cocos2dx_GreedyGame_onProgress(JNIEnv* env, jobject thiz, jint ret)
	        {
	        	if(listener!=NULL) {
	            	listener->onProgress(ret);
	        	}
	        }
	        
		#endif
    }

    void GreedyGameAgent::init(IAgentListener* _listener) {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		        cocos2d::JniMethodInfo t;
		        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
		                                                    ,GG_INIT
		                                                    ,"()V"))
		        {
		            
		            t.env->CallStaticVoidMethod(t.classID,t.methodID);
		            listener = _listener;
		            
		        }
		#endif
    }

    void GreedyGameAgent::setListener(IAgentListener* _listener) {
    	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    	listener = _listener;
    	#endif
    }

    void GreedyGameAgent::removeListener() {
    	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    	listener = NULL;
    	#endif
    }


    void GreedyGameAgent::fetchFloatUnit(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	        cocos2d::JniMethodInfo t;
	        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
	                                                    ,GG_SHOW_FLOAT
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
		                                                ,GG_REMOVE_ALL_FLOAT
		                                                ,"()V"))
		    {
		        t.env->CallStaticVoidMethod(t.classID,t.methodID);
		    }
		#endif
    }

    void GreedyGameAgent::removeFloatUnit(const char *unit_id){
        CCLOG("removeFloatUnit");
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		    cocos2d::JniMethodInfo t;
		    if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
		                                                ,GG_REMOVE_FLOAT_UNIT
		                                                ,"(Ljava/lang/String;)V"))
		    {
		        jstring StringArg1 = t.env->NewStringUTF(unit_id);
		        t.env->CallStaticVoidMethod(t.classID,t.methodID,StringArg1);
		    }
		#endif
    }

     void GreedyGameAgent::showEngagementWindow(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		    cocos2d::JniMethodInfo t;
		    if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
		                                                ,GG_SHOW_UII
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
		                                                ,GG_GET_NATIVE_PATH
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
		                                                ,GG_GET_FLOAT_PATH
		                                                ,"(Ljava/lang/String;)Ljava/lang/String;"))
		    {
		        jstring StringArg1 = t.env->NewStringUTF(unit_id);
		        jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
		        path = JniHelper::jstring2string(str);
		    }
		#endif      
		return path;  
    }

    void GreedyGameAgent::startEventRefresh(){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		    cocos2d::JniMethodInfo t;
		    if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
		                                                ,GG_REFRESH
		                                                ,"()V"))
		    {
		        
		        t.env->CallStaticVoidMethod(t.classID,t.methodID);
		    }
		#endif
    }


}
