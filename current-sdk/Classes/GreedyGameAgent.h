
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>
#include <string>

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

            static void init(IAgentListener* agentListener);

            static void setDebugLog(bool b);

            static string getCampaignPath();

            static string getNativeUnitPathById(const char *unit_id);

            static string getFloatUnitPathById(const char *unit_id);

            static void fetchFloatUnit(const char *unit_id);

            static void removeAllFloatUnits();
            
            static void showEngagementWindow(const char *unit_id);

            static void forcedExit();

            static void removeFloatUnit(const char *unit_id);

            static void startEventRefresh();

            static void setRefreshListener(IAgentListener* agentListener);
 
    };
}


#endif
