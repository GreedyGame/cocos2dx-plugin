
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

	#define GreedyGame_CLASS_NAME "com/greedygame/android/agent/GreedyGameAgent"
	#define GG_INIT "init"
	#define GG_REFRESH "startEventRefresh"
    #define GG_SHOW_FLOAT "showFloat"
    #define GG_REMOVE_ALL_FLOAT "removeAllFloat"
    #define GG_REMOVE_FLOAT_UNIT "removeFloat"
    #define GG_SHOW_UII "showUII"
    #define GG_GET_NATIVE_PATH "getPath"
    #define GG_GET_FLOAT_PATH "getPath"
	

	#define CocosActivity_CLASS_NAME "org/cocos2dx/cpp/AppActivity"	
	#define COCOS_GETCONTEXT "ggActivityHelper"

namespace greedygame {

    IAgentListener* listener;
    jobject GreedyGameAgent::agentObject;
    bool initDone = false;
    bool GreedyGameAgent::enableCrashReport = true;
    // char* customActivityClass = "org/cocos2dx/cpp/AppActivity";
    // char* customActivityMethod = "myActivity";

    extern "C" {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onAvailable(JNIEnv* env, jobject thiz, jstring id) {
	        	if(listener != NULL){
	        		const char *nativeId = env->GetStringUTFChars(id, 0);
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onAvailable(nativeId);
	            		
					});
					env->ReleaseStringUTFChars(id, nativeId);
	            	
	        	}
	        }
	        
	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onUnavailable(JNIEnv* env, jobject thiz)
	        {
	        	if(listener != NULL){
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onUnavailable();
	            		
					});
	        	}
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onFound(JNIEnv* env, jobject thiz)
	        {
	        	if(listener != NULL){
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onFound();
	            		
					});
	        	}
	        }

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onError(JNIEnv* env, jobject thiz, jstring msg)
	        {
	        	if(listener != NULL){
	        		const char *nativeString = env->GetStringUTFChars(msg, 0);
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onError(nativeString);
	            		
					});
					env->ReleaseStringUTFChars(msg, nativeString);
	        	}
	        }

	        JNIEXPORT void JNICALL Javacom_greedygame_android_JavaProxy_onProgress(JNIEnv* env, jobject thiz, jint ret)
	        {
	        	if(listener != NULL){
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onProgress(ret);
	            		
					});
	        	}
	        }
	        
		#endif
    }

    void GreedyGameAgent::initialize(IAgentListener* _listener) {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	        cocos2d::JniMethodInfo t;
	        listener = _listener;
	        CCLOG("GG[Cocos] initialize called");

	        if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
	                                                    ,COCOS_GETCONTEXT
	                                                    ,"()Landroid/app/Activity;"))
	        	{
	           	jobject activity = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
	           	if(activity != NULL) {
	        		init(activity);
	        	} else {
	        		CCLOG("GG[cocos] Activity is null. Please make sure that you have added ggActivityHelper() method which returns activity in your Cocos2dxActivity");
	        	}
	        }
		#endif
    }

    
    void GreedyGameAgent::init(jobject activity2) {

    	if(!initDone) {
    		CCLOG("GG[Cocos] init called ");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
	    	jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	        

    			jmethodID agentConstructor = env->GetMethodID(cls, "<init>", "()V");
    			jobject agent = env->NewObject(cls, agentConstructor);
    			agentObject = env->NewGlobalRef(agent);
				jmethodID run = env->GetMethodID(cls, "init", "(Landroid/app/Activity;ZLjava/lang/String;Ljava/lang/String;)V");
    			if(activity2 != NULL && run!= NULL && agentObject!=NULL) {
    				char* engine = "cocos2dx";
    				jstring stringEngine = env->NewStringUTF(engine);
    				// std::stringstream ss;
    				// ss << COCOS2D_VERSION;

    				jstring cocosVersion = env->NewStringUTF(cocos2dVersion());
    			 	env->CallVoidMethod(agentObject, run,activity2,enableCrashReport,stringEngine,cocosVersion);
    			 	initDone = true;
    			} else {
    				CCLOG("GG[Cocos] make sure that the activity is not null.");
    			}

    	} 

    }

    void GreedyGameAgent::startEventRefresh(){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			if(initDone) {
				CCLOG("GG[COCOS] startEventRefresh called successfully");
				JavaVM* vm = JniHelper::getJavaVM();
				JNIEnv* env;
				vm->GetEnv((void**)&env,JNI_VERSION_1_4);
				jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
				jmethodID startEventRefresh = env->GetMethodID(cls, GG_REFRESH, "()V");
				if(agentObject!=null) {
					env->CallVoidMethod(agentObject, startEventRefresh);
				}
				CCLOG("GG[COCOS] startEventRefresh completed successfully");
			}
		#endif
    }


    void GreedyGameAgent::fetchFloatUnit(const char *unit_id)  {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCLOG("GG[COCOS] fetchFloatUnit called.");
		if(initDone) {
	    	JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
			jmethodID showFloat = env->GetMethodID(cls, GG_SHOW_FLOAT
		                                                    ,"(Landroid/app/Activity;Ljava/lang/String;)V");
			cocos2d::JniMethodInfo t;
		    	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
		                                                    ,COCOS_GETCONTEXT
		                                                    ,"()Landroid/app/Activity;"))
			        {
			           	jobject activity = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
			           	jstring stringId = env->NewStringUTF(unit_id);
						env->CallVoidMethod(agentObject, showFloat,activity,stringId);
			       	}
	    }
    	#endif
    }

    void GreedyGameAgent::removeAllFloatUnits(){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		if(initDone) {
			CCLOG("GG[COCOS] removeAllFloatUnits called successfully");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
    		jmethodID removeAllFloats = env->GetMethodID(cls, GG_REMOVE_ALL_FLOAT,"()V");
			env->CallVoidMethod(agentObject, removeAllFloats);
    		CCLOG("GG[COCOS] removeAllFloatUnit completed successfully");
    	}
		#endif
    }

    void GreedyGameAgent::removeFloatUnit(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		if(initDone) {
			CCLOG("GG[COCOS] removeFloatUnit called successfully");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	    	jmethodID removeFloat = env->GetMethodID(cls, GG_REMOVE_FLOAT_UNIT,"(Ljava/lang/String;)V");
			jstring stringId = env->NewStringUTF(unit_id);
			env->CallVoidMethod(agentObject, removeFloat,stringId);
	    	CCLOG("GG[COCOS] removeFloatUnit completed successfully");
	    }
		#endif
    }


     void GreedyGameAgent::showEngagementWindow(const char *unit_id){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		if(initDone) {
			CCLOG("GG[COCOS] showEngagementWindow called successfully");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	    	jmethodID showUII = env->GetMethodID(cls, GG_SHOW_UII,"(Ljava/lang/String;)V");
			jstring stringId = env->NewStringUTF(unit_id);
			env->CallVoidMethod(agentObject, showUII,stringId);
	    	CCLOG("GG[COCOS] showEngagementWindow completed successfully");
    	}
		#endif        
    }

	std::string GreedyGameAgent::getNativeUnitPathById(const char *unit_id){
		if(initDone) {
			CCLOG("GG[COCOS] getNativeUnitPathById");
			return getPath(unit_id);
		}
	}

	std::string GreedyGameAgent::getFloatUnitPathById(const char *unit_id){
		if(initDone) {
			CCLOG("GG[COCOS] getFloatUnitPathById");
			return getPath(unit_id); 
		}
    }

	std::string GreedyGameAgent::getPath(const char *unit_id) {
		if(initDone) {
			std::string path("");
			CCLOG("GG[COCOS] getPath called");        
			#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
				JavaVM* vm = JniHelper::getJavaVM();
				JNIEnv* env;
				vm->GetEnv((void**)&env,JNI_VERSION_1_4);
				jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	    		jmethodID getNative = env->GetMethodID(cls, GG_GET_NATIVE_PATH,"(Ljava/lang/String;)Ljava/lang/String;");
			    jstring stringId = env->NewStringUTF(unit_id);
				jstring str = (jstring) env->CallObjectMethod(agentObject,getNative ,stringId);
				path = JniHelper::jstring2string(str);
			#endif      
			return path;  
		}
	}

	void GreedyGameAgent::enableCrashReporting(bool enable) {
		CCLOG("GG[COCOS] enable crash reporting");        
		enableCrashReport = enable;
	}

	void GreedyGameAgent::setListener(IAgentListener* _listener) {
    	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    	CCLOG("GG[COCOS] setListener");        
    	listener = _listener;
    	#endif
    }

    void GreedyGameAgent::removeListener() {
    	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    	CCLOG("GG[COCOS] removeListener called"); 
    	listener = NULL;
    	#endif
    }

}
