
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

#define  GreedyGame_CLASS_NAME "com/greedygame/android/cocos2dx/GreedyGame"

namespace greedygame
{

    IAgentListener* listener;
    IActionListener* floatListener;
    std::map<string, IActionListener* >  floatListenerMap;



    extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_GreedyGame_onAvailable(JNIEnv* env, jobject thiz)
        {
            listener->onAvailable();
        }
        
        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_GreedyGame_onUnavailable(JNIEnv* env, jobject thiz)
        {
            listener->onUnavailable();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_GreedyGame_onProgress(JNIEnv* env, jobject thiz, jint ret)
        {
            listener->onProgress(ret);
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_GreedyGame_onPermissionsUnavailable(JNIEnv* env, jobject thiz, jstring permissions)
        {   
            std::string p = JniHelper::jstring2string(permissions);
            std::vector<std::string> permissionsVect;
            std::stringstream ss(p);
            while( ss.good() )
            {
                std::string substr;
                getline( ss, substr, ',' );
                if(!substr.empty()) 
                {
                    permissionsVect.push_back( substr );
                }
            }

            listener->onPermissionsUnavailable(permissionsVect);
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_GreedyGame_onActionPerformed(JNIEnv* env, jobject thiz, jstring _float_unit, jstring _action)
        {
            CCLOG("COCOS onActionPerformed callback received in JNI Bridge" );
            std::string action = JniHelper::jstring2string(_action);
            std::string float_unit = JniHelper::jstring2string(_float_unit);
            CCLOG("COCOSGG  %s",action.c_str());
            CCLOG("COCOSGG  %s",float_unit.c_str());
            
            floatListener = floatListenerMap[float_unit];
            if(!floatListener){
                CCLOG("COCOSGG floatlistener is null ");
                return;
            }
            bool isActionConsumed = floatListener->onActionPerformed(action); 
            if(!isActionConsumed) {
                listener->onActionPerformed(float_unit, action);
                CCLOG("COCOSGG isActionConsumed boolean from float listener received and triggered IAgentListener Callback");
            }

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
                                                    ,"fetchFloatUnit"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif
    }


    void GreedyGameAgent::setActionListener(const std::string unit_id, IActionListener* action_listener){
        CCLOG("COCOS setActionListener" );
        floatListenerMap[unit_id] = action_listener;
    }



    void GreedyGameAgent::removeAllFloatUnits(){
        CCLOG("removeAllFloatUnits");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"removeAllFloatUnits"
                                                    ,"()V"))
        {
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
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
                                                    ,"showEngagementWindow"
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
                                                    ,"getNativeUnitPathById"
                                                    ,"(Ljava/lang/String;)Ljava/lang/String;"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }


std::string GreedyGameAgent::getNativeUnitPathByName(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getNativeUnitPathByName"
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
