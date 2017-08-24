
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

using namespace cocos2d;

USING_NS_CC;

	#define  GreedyGame_CLASS_NAME "com/greedygame/android/agent/GreedyGameAgent"
	#define GG_INIT "init"
    #define GG_GET_CAMPAIGN_PATH "getCampaignPath"
    #define GG_SHOW_FLOAT "showFloat"
    #define GG_REMOVE_ALL_FLOAT "removeAllFloat"
    #define GG_REMOVE_FLOAT_UNIT "removeFloat"
    #define GG_FORCED_EXIT "forcedExit"
    #define GG_SHOW_UII "showUII"
    #define GG_GET_NATIVE_PATH "getPath"
    #define GG_GET_FLOAT_PATH "getPath"
	#define GG_REFRESH "startEventRefresh"

	#define  CocosActivity_CLASS_NAME "org/cocos2dx/cpp/AppActivity"	
	#define COCOS_GETCONTEXT "myActivity"

namespace greedygame {

    IAgentListener* listener;
    jobject GreedyGameAgent::activity;
    jclass GreedyGameAgent::cls;
    jobject GreedyGameAgent::agentObject;
    // char* customActivityClass = "org/cocos2dx/cpp/AppActivity";
    // char* customActivityMethod = "myActivity";

    extern "C" {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onAvailable(JNIEnv* env, jobject thiz) {
	            listener->onAvailable();
	        }
	        
	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onUnavailable(JNIEnv* env, jobject thiz)
	        {
	            listener->onUnavailable();
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onFound(JNIEnv* env, jobject thiz)
	        {
	            listener->onFound();
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onError(JNIEnv* env, jobject thiz, jstring msg)
	        {
	            const char *nativeString = env->GetStringUTFChars(msg, 0);
	            listener->onError(nativeString);
				env->ReleaseStringUTFChars(msg, nativeString);
	        }

	        JNIEXPORT void JNICALL Javacom_greedygame_android_JavaProxy_onProgress(JNIEnv* env, jobject thiz, jint ret)
	        {
	            listener->onProgress(ret);
	        }
	        
		#endif
    }

    void GreedyGameAgent::initialize(IAgentListener* _listener) {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	        cocos2d::JniMethodInfo t;
	        listener = _listener;
	        CCLOG("DEBUGGG CPP INITIALIZE");

	        if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
	                                                    ,COCOS_GETCONTEXT
	                                                    ,"()Landroid/app/Activity;"))
	        {
	           activity = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
	           // activity = env->NewGlobalRef(localActivity);
	           if(activity == NULL) {
	        	CCLOG("DEBUGGG ACTVIITY IS NULL");

	        } else {
	        	CCLOG("DEBUGGG ACTIVITY IS NOT NULL");
	        	init(activity);
	        }
	        }

	        
		#endif
    }

    
    void GreedyGameAgent::init(jobject activity2) {

    		CCLOG("DEBUGGG inside overloaded init");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
	        cls = env->FindClass(GreedyGame_CLASS_NAME);
	        if (NULL == cls) {
        		CCLOG("DEBUGGG Agent find class is null");
        		return;
    		} else {
         		CCLOG("DEBUGGG Agent find class is not null");
    		}

    jmethodID agentConstructor = env->GetMethodID(cls, "<init>", "()V");
    if (NULL == agentConstructor) {
        CCLOG("DEBUGGG Agent constructor is null");
        return;
    } else {
         CCLOG("DEBUGGG Agent constructor is not null");
    }

    jobject agent = env->NewObject(cls, agentConstructor);
    agentObject = env->NewGlobalRef(agent);


    if (NULL == agentObject) {
        CCLOG("DEBUGGG Agent object is null");
        return;
    } else {
        CCLOG("DEBUGGG Agent object is not null");
    }

    jmethodID run = env->GetMethodID(cls, "init", "(Landroid/app/Activity;)V");
    if (NULL == run) {
        return;
    }

    if(activity2 != NULL) {
    	CCLOG("DEBUGGG activity2 is not null");
     	env->CallVoidMethod(agentObject, run,activity2);
     	CCLOG("DEBUGGG after init AAAA");
     		
    } else {
    	CCLOG("DEBUGGG activity is null");
    }




    }


    void GreedyGameAgent::fetchFloatUnit(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCLOG("DEBUGGG new 22222222222 start");
    	JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			CCLOG("DEBUGGG new 22222222222 start2");
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			CCLOG("DEBUGGG new 22222222222 start 3");
			cls = env->FindClass(GreedyGame_CLASS_NAME);
			CCLOG("DEBUGGG new 22222222222 start 4");
    	jmethodID showFloat = env->GetMethodID(cls, GG_SHOW_FLOAT
	                                                    ,"(Landroid/app/Activity;Ljava/lang/String;)V");
		 CCLOG("DEBUGGG activity2 is not null KIRTTT 22222222222");
		 if(showFloat==NULL){
		 	CCLOG("DEBUGGG showfloat is null 2222222222222");
		 } else {
		 	CCLOG("DEBUGGG showfloat is not null 2222222222222");
		 }

		 if(agentObject == NULL) {
		 	CCLOG("DEBUGGG agentObject is null 2222222222222");
		 } else {
		 	CCLOG("DEBUGGG agentObject is not null 2222222222222");
		 }

		if(activity == NULL) {
		 	CCLOG("DEBUGGG activity is null 2222222222222");
		 } else {
		 	CCLOG("DEBUGGG activity is not null 2222222222222");
		 }


		 cocos2d::JniMethodInfo t;
	     
	        CCLOG("DEBUGGG CPP INITIALIZE");

	        if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
	                                                    ,COCOS_GETCONTEXT
	                                                    ,"()Landroid/app/Activity;"))
	        {
	           	jobject activity3 = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
	           	jstring stringId = env->NewStringUTF(unit_id);
				env->CallVoidMethod(agentObject, showFloat,activity3,stringId);
    			CCLOG("DEBUGGG activity3 is not GTTTT 222222222222222222");

	       }

    	
    	#endif
    }

    void GreedyGameAgent::removeAllFloatUnits(){
        CCLOG("removeAllFloatUnits");
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCLOG("GG[COCOS] removeAllFloatUnit called successfully");
		JavaVM* vm = JniHelper::getJavaVM();
		JNIEnv* env;
		vm->GetEnv((void**)&env,JNI_VERSION_1_4);
		cls = env->FindClass(GreedyGame_CLASS_NAME);
    	jmethodID removeAllFloats = env->GetMethodID(cls, GG_REMOVE_ALL_FLOAT,"()V");
		env->CallVoidMethod(agentObject, removeAllFloats);
    	CCLOG("GG[COCOS] removeAllFloatUnit completed successfully");
		#endif
    }

    void GreedyGameAgent::removeFloatUnit(const char *unit_id){
        CCLOG("removeFloatUnit");
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCLOG("GG[COCOS] removeFloatUnit called successfully");
		JavaVM* vm = JniHelper::getJavaVM();
		JNIEnv* env;
		vm->GetEnv((void**)&env,JNI_VERSION_1_4);
		cls = env->FindClass(GreedyGame_CLASS_NAME);
    	jmethodID removeFloat = env->GetMethodID(cls, GG_REMOVE_FLOAT_UNIT,"(Ljava/lang/String;)V");
		jstring stringId = env->NewStringUTF(unit_id);
		env->CallVoidMethod(agentObject, removeFloat,stringId);
    	CCLOG("GG[COCOS] removeFloatUnit completed successfully");
		#endif
    }


     void GreedyGameAgent::showEngagementWindow(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCLOG("GG[COCOS] showEngagementWindow called successfully");
		JavaVM* vm = JniHelper::getJavaVM();
		JNIEnv* env;
		vm->GetEnv((void**)&env,JNI_VERSION_1_4);
		cls = env->FindClass(GreedyGame_CLASS_NAME);
    	jmethodID showFloat = env->GetMethodID(cls, GG_SHOW_UII,"(Ljava/lang/String;)V");
		jstring stringId = env->NewStringUTF(unit_id);
		env->CallVoidMethod(agentObject, showFloat,stringId);
    	CCLOG("GG[COCOS] showEngagementWindow completed successfully");
		#endif        
    }

	std::string GreedyGameAgent::getNativeUnitPathById(const char *unit_id){
		return getPath(unit_id);
	}

	std::string GreedyGameAgent::getFloatUnitPathById(const char *unit_id){
		return getPath(unit_id); 
    }

	std::string GreedyGameAgent::getPath(const char *unit_id) {
		std::string path("");
		        
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			CCLOG("DEBUGGG new 22222222222 start2");
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			CCLOG("DEBUGGG new 22222222222 start 3");
			cls = env->FindClass(GreedyGame_CLASS_NAME);
			CCLOG("DEBUGGG new 22222222222 start 4");
    		jmethodID getNative = env->GetMethodID(cls, GG_GET_NATIVE_PATH,"(Ljava/lang/String;)Ljava/lang/String;");
		    jstring stringId = env->NewStringUTF(unit_id);
			jstring str = (jstring) env->CallObjectMethod(agentObject,getNative ,stringId);
			path = JniHelper::jstring2string(str);
			#endif      
		return path;  
	}

}
