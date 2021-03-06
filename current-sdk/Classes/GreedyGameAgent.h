
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
            virtual void onError(const char *msg){};
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

                    static bool enableNpaBoolean;

                    static bool enableCOPPABoolean;

                    GGAdOptions();

                    GGAdOptions* enableAdmobMediation(bool enable);

                    GGAdOptions* enableFacebookMediation(bool enable);

                    GGAdOptions* enableMopubMediation(bool enable);

                    GGAdOptions* enableCrashReporting(bool enable);

                    GGAdOptions* gameEngine();

                    GGAdOptions* engineVersion();

                    GGAdOptions* setGameId(const char* gameId);

                    GGAdOptions* enableCOPPA(bool enable);

                    GGAdOptions* addUnitId(const char* unitId);

                    GGAdOptions* addUnitList(const string* unitIdList, int unitListSize);

                    GGAdOptions* withAgentListener(IAgentListener* listener);

                    GGAdOptions* enableNpa(bool enforce);

                    jobject getBuilderObject();

                    bool getGgNpa();

            };

    class GreedyGameAgent {

        public:

            static jobject agentObject;

            jclass privacyOptionsClass;

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
