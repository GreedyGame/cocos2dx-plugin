
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
	#define GG_ENABLE_ADMOB "enableAdmob"
	#define GG_SEND_CRASH "sendCrash"
	

	#define CocosActivity_CLASS_NAME "org/cocos2dx/cpp/AppActivity"	
	#define COCOS_GETCONTEXT "ggActivityHelper"

namespace greedygame {

    IAgentListener* listener;
    jobject GreedyGameAgent::agentObject;
    bool initDone = false;
    bool GreedyGameAgent::enableCrashReport = true;
    bool GreedyGameAgent::enableAdmobBoolean = false;
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

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onProceed(JNIEnv* env, jobject thiz)
	        {
	        	if(listener != NULL){
	        		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	        			
	        			listener->onProceed();
	            		
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

	        JNIEXPORT void JNICALL Java_com_greedygame_android_JavaProxy_onProgress(JNIEnv* env, jobject thiz, jint ret)
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
	        CCLOG("GG[Cocos] CPP INITIALIZE");

	        if(cocos2d::JniHelper::getStaticMethodInfo(t,GreedyGame_CLASS_NAME, GG_ENABLE_ADMOB,"(Z)V")){
	        	CCLOG("GG[COCOS] Setting admob in GGAgent");
	        	t.env->CallStaticVoidMethod(t.classID,t.methodID, enableAdmobBoolean);
	        }

	        if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
	                                                    ,COCOS_GETCONTEXT
	                                                    ,"()Landroid/app/Activity;"))
	        	{
	        		
		           	jobject activity = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
		           	if(activity != NULL) {
		        		CCLOG("GG[COCOS] ACTVIITY IS NOT NULL");
		        		init(activity);
		        	} else {
	                    CCLOG("GG[COCOS] Please declare ggActivityHelper inside your AppActvity which extends cocos2dxActivity to initialize the GG SDK.Please refer to the integraton guide for more details.");
	        		}
	        	}
	        
		#endif
    }

    
    void GreedyGameAgent::init(jobject activity2) {

    	if(!initDone) {
    		CCLOG("GG[COCOS] inside overloaded init");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
	    	jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	        

    			jmethodID agentConstructor = env->GetMethodID(cls, "<init>", "()V");
    			jobject agent = env->NewObject(cls, agentConstructor);
    			agentObject = env->NewGlobalRef(agent);
				jmethodID run = env->GetMethodID(cls, "init", "(Landroid/app/Activity;ZLjava/lang/String;Ljava/lang/String;)V");
    			if(activity2 != NULL && run!= NULL && agentObject!=NULL) {
    				char* engine = "cocos";
    				jstring stringEngine = env->NewStringUTF(engine);
    				// std::stringstream ss;
    				// ss << COCOS2D_VERSION;
    				jstring cocosVersion = env->NewStringUTF(cocos2dVersion());
    			 	env->CallVoidMethod(agentObject, run,activity2,enableCrashReport,stringEngine,cocosVersion);
    			 	initDone = true;
    			} else {
    				CCLOG("GG[COCOS] Please declare ggActivityHelper inside your AppActivity which extends cocos2dxActivity to initialize the GG SDK.Please refer to the integraton guide for more details.");
    			}

    	} else {
    		startEventRefresh();
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
				if(startEventRefresh != NULL && agentObject != NULL){
					env->CallVoidMethod(agentObject, startEventRefresh);
					CCLOG("GG[COCOS] startEventRefresh completed successfully");
				}
			}
		#endif
    }


    void GreedyGameAgent::fetchFloatUnit(const char *unit_id)  {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
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
	           	if(showFloat != NULL && agentObject != NULL && activity!=NULL){
					env->CallVoidMethod(agentObject, showFloat,activity,stringId);
				}
	       	}
	    }
    	#endif
    }

    void GreedyGameAgent::removeAllFloatUnits(){
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		if(initDone) {
		CCLOG("GG[COCOS] removeAllFloatUnit called successfully");
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
    		jmethodID removeAllFloats = env->GetMethodID(cls, GG_REMOVE_ALL_FLOAT,"()V");
    		if(removeAllFloats != NULL && agentObject != NULL){
				env->CallVoidMethod(agentObject, removeAllFloats);
    			CCLOG("GG[COCOS] removeAllFloatUnit completed successfully");
    		}
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
		if(removeFloat != NULL && agentObject != NULL){
			env->CallVoidMethod(agentObject, removeFloat,stringId);
    		CCLOG("GG[COCOS] removeFloatUnit completed successfully");
    	}
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
		if(showUII != NULL && agentObject != NULL){
			env->CallVoidMethod(agentObject, showUII,stringId);
    		CCLOG("GG[COCOS] showEngagementWindow completed successfully");
    	}
    }
		#endif        
    }

	std::string GreedyGameAgent::getNativeUnitPathById(const char *unit_id){
		if(initDone) {
		return getPath(unit_id);
		} else {
			std::string path("");
			return path;
		}
	}

	std::string GreedyGameAgent::getFloatUnitPathById(const char *unit_id){
		if(initDone) {
		return getPath(unit_id); 
		} else {
			std::string path("");
			return path;
		}
    }

	std::string GreedyGameAgent::getPath(const char *unit_id) {
		if(initDone) {
		std::string path("");
		        
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
			jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
    		jmethodID getNative = env->GetMethodID(cls, GG_GET_NATIVE_PATH,"(Ljava/lang/String;)Ljava/lang/String;");
		    jstring stringId = env->NewStringUTF(unit_id);
		    if(getNative != NULL && agentObject != NULL){
				jstring str = (jstring) env->CallObjectMethod(agentObject,getNative ,stringId);
				path = JniHelper::jstring2string(str);
			}
			#endif      
		return path;  
		} else {
			std::string path("");
			return path;
		}
	}

	void GreedyGameAgent::sendCrashReport(const char *error, bool isFatal) {
		if(initDone) {
			#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
				JavaVM* vm = JniHelper::getJavaVM();
				JNIEnv* env;
				vm->GetEnv((void**)&env,JNI_VERSION_1_4);
				jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
	    		jmethodID getCrashMethodID = env->GetMethodID(cls, GG_SEND_CRASH,"(Ljava/lang/String;Z)V");
	    		jstring stringError = env->NewStringUTF(error);
			    env->CallVoidMethod(agentObject, getCrashMethodID, stringError, false);
			#endif    
		}
	}

	void GreedyGameAgent::enableCrashReporting(bool enable) {
		enableCrashReport = enable;
	}

	void GreedyGameAgent::enableAdmob(bool enable) {
		enableAdmobBoolean = enable;
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

}
