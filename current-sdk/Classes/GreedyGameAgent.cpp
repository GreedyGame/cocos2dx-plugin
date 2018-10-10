
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
	#define GreedyGame_BUILDER_CLASS_NAME "com/greedygame/android/agent/GreedyGameAgent$Builder"
	#define GreedyGame_PRIVACY_OPTIONS_CLASS_NAME "com/greedygame/android/agent/PrivacyOptions"
	#define ENFORCE_GG_NPA "setGgNpa"
	#define GG_INIT "init"
	#define GG_REFRESH "startEventRefresh"
    #define GG_SHOW_FLOAT "showFloat"
    #define GG_REMOVE_ALL_FLOAT "removeAllFloat"
    #define GG_REMOVE_FLOAT_UNIT "removeFloat"
    #define GG_SHOW_UII "showUII"
    #define GG_GET_NATIVE_PATH "getPath"
    #define GG_GET_FLOAT_PATH "getPath"
	#define GG_ADD_UNIT_ID "addUnitId"
	#define GG_SEND_CRASH "sendCrash"
	#define GG_ENABLE_ADMOB "enableAdmob"
    #define GG_ENABLE_CRASH "enableCrash"
	#define GG_ENABLE_FACEBOOK "enableFacebook"
	#define GG_ENABLE_MOPUB "enableMopub"
	#define GG_ENGINE_NAME "gameEngine"
	#define GG_ENGINE_VERSION "engineVersion"
	#define GG_BUILDER_LISTENER "withAgentListener"
	#define GG_ENABLE_COPPA "enableCOPPAFilter"
	#define GG_SET_GAME_ID "setGameId"

	#define CocosActivity_CLASS_NAME "org/cocos2dx/cpp/AppActivity"	
	#define COCOS_GETCONTEXT "ggActivityHelper"

namespace greedygame {

    IAgentListener* listener;
    jobject GreedyGameAgent::agentObject;
    jobject GGAdOptions::builderObj;

    bool initDone = false;
    bool GGAdOptions::enableCrashReportBoolean = true;
	bool GGAdOptions::enableAdmobBoolean = false;
	bool GGAdOptions::enableMopubBoolean = false;
	bool GGAdOptions::enableFacebookBoolean = false;
	bool GGAdOptions::enableNpaBoolean = false;

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
    
		#endif
    }

    GGAdOptions::GGAdOptions() {

				cocos2d::JniMethodInfo t;
    			if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosActivity_CLASS_NAME
	                                                    ,COCOS_GETCONTEXT
	                                                    ,"()Landroid/app/Activity;"))
	        	{
	        		JavaVM* vm;
    				JNIEnv* env;
    				jclass cls;
    				
		           	jobject activity = (jobject) t.env->CallStaticObjectMethod(t.classID,t.methodID);
		           	if(activity != NULL) {
		        		vm = JniHelper::getJavaVM();
						vm->GetEnv((void**)&env,JNI_VERSION_1_4);
						cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
						jmethodID constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    					jobject Obj = env->NewObject(cls, constructor, activity);
    					builderObj = env->NewGlobalRef(Obj);

    					//Updating game engine name
    					jmethodID gameEngine = env->GetMethodID(cls, GG_ENGINE_NAME, "(Ljava/lang/String;)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
    					char* engine = "cocos";
    					jstring stringEngine = env->NewStringUTF(engine);
    					env->CallObjectMethod(builderObj, gameEngine ,stringEngine);

    					//Updating game engine version
    					jmethodID engineV = env->GetMethodID(cls, GG_ENGINE_VERSION, "(Ljava/lang/String;)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
    					jstring cocosVersion = env->NewStringUTF(cocos2dVersion());
    					env->CallObjectMethod(builderObj, engineV, cocosVersion);

		        	} else {
	                    CCLOG("GG[COCOS] Please declare ggActivityHelper inside your AppActivity which extends cocos2dxActivity to initialize the GG SDK.Please refer to the integraton guide for more details.");
	        		}
	        	}
    		}

    		GGAdOptions* GGAdOptions::enableAdmobMediation(bool enable){
    			if(builderObj != NULL) {
    				enableAdmobBoolean = enable;
    				JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
    				jmethodID admob = env->GetMethodID(cls, GG_ENABLE_ADMOB, "(Z)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
    				env->CallObjectMethod(builderObj, admob ,enableAdmobBoolean);
    			}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::enableFacebookMediation(bool enable) {
    			if(builderObj != NULL) {
	    			enableFacebookBoolean = enable;
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
	    			jmethodID facebook = env->GetMethodID(cls, GG_ENABLE_FACEBOOK, "(Z)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			env->CallObjectMethod(builderObj, facebook, enableFacebookBoolean);
    			}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::enableMopubMediation(bool enable){
    			if(builderObj != NULL) {
	    			enableMopubBoolean = enable;
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
	    			jmethodID mopub = env->GetMethodID(cls, GG_ENABLE_MOPUB, "(Z)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			env->CallObjectMethod(builderObj, mopub, enableMopubBoolean);
	    		}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::enableCrashReporting(bool enable){
    			if(builderObj != NULL) {
	    			enableCrashReportBoolean = enable;
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
	    			jmethodID crash = env->GetMethodID(cls, GG_ENABLE_CRASH, "(Z)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			env->CallObjectMethod(builderObj, crash, enableCrashReportBoolean);
    			}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::enableCOPPA(bool enable){
    			if(builderObj != NULL) {
	    			enableCrashReportBoolean = enable;
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
	    			jmethodID coppa = env->GetMethodID(cls, GG_ENABLE_COPPA, "(Z)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			env->CallObjectMethod(builderObj, coppa, enableCrashReportBoolean);
    			}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::withAgentListener(IAgentListener* agentListener){
    			listener = agentListener;
    			return this;
    		}

    		GGAdOptions* GGAdOptions::addUnitId(const char* unitId){
    			if(builderObj != NULL) {
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
					jmethodID addUnitMethod = env->GetMethodID(cls, GG_ADD_UNIT_ID, "(Ljava/lang/String;)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			jstring stringId = env->NewStringUTF(unitId);
	    			env->CallObjectMethod(builderObj, addUnitMethod, stringId);
	    		}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::setGameId(const char* unitId){
    			if(builderObj != NULL) {
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
					jmethodID addUnitMethod = env->GetMethodID(cls, GG_SET_GAME_ID, "(Ljava/lang/String;)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
	    			jstring stringId = env->NewStringUTF(unitId);
	    			env->CallObjectMethod(builderObj, addUnitMethod, stringId);
	    		}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::addUnitList(const string* unitIdList, int unitListSize){
    			if(builderObj != NULL) {
	    			JavaVM* vm = JniHelper::getJavaVM();
					JNIEnv* env;
					vm->GetEnv((void**)&env,JNI_VERSION_1_4);
					jclass cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
					jmethodID addUnitMethod = env->GetMethodID(cls, GG_ADD_UNIT_ID, "(Ljava/lang/String;)Lcom/greedygame/android/agent/GreedyGameAgent$Builder;");
					if(unitListSize >= 0)
					{
						for(int i=0; i<unitListSize; i++) {
		    				CCLOG("GG[COCOS] Size %i",unitListSize);
		    				if(unitIdList[i].c_str() != NULL) {CCLOG("GG[COCOS] Size %i",unitListSize);
		    				CCLOG("GG[COCOS] Name %s",unitIdList[i].c_str());
		    					jstring stringId = env->NewStringUTF(unitIdList[i].c_str());
		    					env->CallObjectMethod(builderObj, addUnitMethod, stringId);
	    					}
	    				}
					}
					else{
						CCLOG("GG[COCOS] Unit List Size cannot accept negative values");
					}
	    		}
    			return this;
    		}

    		GGAdOptions* GGAdOptions::enableNpa(bool enforce) {
    			enableNpaBoolean = enforce;
    			return this;
    		}

    		jobject GGAdOptions::getBuilderObject() {
    			CCLOG("GG[COCOS] ggadoptions get builder object");
    			return builderObj;
    		}

    		bool GGAdOptions::getGgNpa() {
    			return enableNpaBoolean;
    		}


    		

    void GreedyGameAgent::initialize(GGAdOptions* ggAdOptions) {
		#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			if(agentObject == NULL) {
				JavaVM* vm = JniHelper::getJavaVM();
				JNIEnv* env;
				jclass cls;
				jclass privacyOptionsCls;

				vm->GetEnv((void**)&env,JNI_VERSION_1_4);
				cls = env->FindClass(GreedyGame_BUILDER_CLASS_NAME);
		        jmethodID buildCall = env->GetMethodID(cls, "build", "()Lcom/greedygame/android/agent/GreedyGameAgent;");
	    		jobject builderOptions = ggAdOptions->getBuilderObject();
	    		if(builderOptions != NULL) {
		    		jobject jGreedyGameAgent = env->CallObjectMethod(builderOptions, buildCall);
		    		agentObject = env->NewGlobalRef(jGreedyGameAgent);

		    		privacyOptionsCls = env->FindClass(GreedyGame_PRIVACY_OPTIONS_CLASS_NAME);
	    		jmethodID constructor = env->GetMethodID(privacyOptionsCls, "<init>", "()V");
	    		jobject privacyOptionsObject = env->NewObject(privacyOptionsCls, constructor);
	    		jmethodID enforceGgNpa = env->GetMethodID(privacyOptionsCls, ENFORCE_GG_NPA, "(Z)V");
	    		if(enforceGgNpa!= NULL && privacyOptionsObject!=NULL) {
	    			env->CallVoidMethod(privacyOptionsObject, enforceGgNpa, ggAdOptions->getGgNpa());
				}

				jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
				jmethodID run = env->GetMethodID(cls, "withPrivacyOptions", "(Lcom/greedygame/android/agent/PrivacyOptions;)V");
				env->CallVoidMethod(agentObject, run, privacyOptionsObject);


	    		} else {
	    			CCLOG("GG[COCOS] Please declare ggActivityHelper inside your AppActivity which extends cocos2dxActivity to initialize the GG SDK.Please refer to the integraton guide for more details.");
					return;
				}
	    	}

			init();
		#endif
    }

    
    void GreedyGameAgent::init() {
    	if(!initDone) {
			JavaVM* vm = JniHelper::getJavaVM();
			JNIEnv* env;
			vm->GetEnv((void**)&env,JNI_VERSION_1_4);
	    	jclass cls = env->FindClass(GreedyGame_CLASS_NAME);
			jmethodID run = env->GetMethodID(cls, "init", "()V");
    		if(run!= NULL && agentObject!=NULL) {
    			char* engine = "cocos";
    			jstring stringEngine = env->NewStringUTF(engine);
    			jstring cocosVersion = env->NewStringUTF(cocos2dVersion());
    			env->CallVoidMethod(agentObject, run);
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
