
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

    class GGAdOptions {
            
                public:

                    JavaVM* vm;

                    JNIEnv* env;
            
                    jclass cls;

                    static jobject builderObj;

                    static bool enableCrashReportBoolean;

                    static bool enableAdmobBoolean;

                    static bool enableMopubBoolean;

                    static bool enableFacebookBoolean;

                    GGAdOptions();

                    GGAdOptions* enableAdmobMediation(bool enable);

                    GGAdOptions* enableFacebookMediation(bool enable);

                    GGAdOptions* enableMopubMediation(bool enable);

                    GGAdOptions* enableCrashReporting(bool enable);

                    GGAdOptions* gameEngine();

                    GGAdOptions* engineVersion();

                    GGAdOptions* addUnitId(const char* unitId);

                    GGAdOptions* addUnitList(const string* unitIdList);

                    GGAdOptions* withAgentListener(IAgentListener* listener);

                    jobject getBuilderObject();

            };

    class GreedyGameAgent {

        public:

            static jobject agentObject;

            static void initialize(GGAdOptions* ggAdOptions);

            static void init();

            static void startEventRefresh();

            static string getNativeUnitPathById(const char *unit_id);

            static string getFloatUnitPathById(const char *unit_id);

            static void fetchFloatUnit(const char *unit_id);

            static string getPath(const char *unitid);

            static void removeAllFloatUnits();
            
            static void showEngagementWindow(const char *unit_id);

            static void removeFloatUnit(const char *unit_id);

            static void setListener(IAgentListener* agentListener);

            static void removeListener();

            static void sendCrashReport(const char *error, bool enable);
 
    };
}


#endif
