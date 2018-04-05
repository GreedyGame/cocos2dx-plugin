
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>
#include <string>
#include <jni.h>


using namespace std;

namespace greedygame {

    class IAgentListener {
        public:
            virtual void onAvailable(const char *id){};
            virtual void onUnavailable(){};
            virtual void onProgress(int progress){};
            virtual void onError(const char *msg){};
            virtual void onProceed(){};
            virtual void onFound(){};
    };

    class GreedyGameAgent {

        public:

            static jobject agentObject;

            static bool enableCrashReport;

            static bool enableAdmobBoolean;

            static bool enableMopubBoolean;

            static bool enableFacebookBoolean;

            static void initialize(IAgentListener* listener);

            static void init(jobject activity);

            static void startEventRefresh();

            static string getNativeUnitPathById(const char *unit_id);

            static string getFloatUnitPathById(const char *unit_id);

            static void fetchFloatUnit(const char *unit_id);

            static string getPath(const char *unitid);

            static void removeAllFloatUnits();
            
            static void showEngagementWindow(const char *unit_id);

            static void removeFloatUnit(const char *unit_id);

            static void enableCrashReporting(bool enable);

            static void setListener(IAgentListener* agentListener);

            static void removeListener();

            static void enableAdmob(bool enable);

            static void enableMopub(bool enable);

            static void sendCrashReport(const char *error, bool enable);
 
    };
}


#endif
