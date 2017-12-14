
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
            virtual void onAvailable(){};
            virtual void onUnavailable(){};
            virtual void onProgress(int progress){};
            virtual void onError(const char *msg){};
            virtual void onFound(){};
    };

    class GreedyGameAgent {

        public:

            static jobject agentObject;

            static bool enableCrashReport;

            static void initialize(IAgentListener* listener);

            static void init(jobject activity);

            static string getNativeUnitPathById(const char *unit_id);

            static string getFloatUnitPathById(const char *unit_id);

            static void fetchFloatUnit(const char *unit_id);

            static string getPath(const char *unitid);

            static void removeAllFloatUnits();
            
            static void showEngagementWindow(const char *unit_id);

            static void removeFloatUnit(const char *unit_id);

            static void enableCrashReporting(bool enable);
 
    };
}


#endif
