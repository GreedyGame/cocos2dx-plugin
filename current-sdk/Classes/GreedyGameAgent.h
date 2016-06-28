
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>

using namespace std;

namespace greedygame {

    class IAgentListener {
        public:
            virtual void onAvailable(){};
            virtual void onUnavailable(){};
            virtual void onProgress(int progress){};
            virtual void onPermissionsUnavailable(vector<string> permissionsVect){};
    };

    class GreedyGameAgent {

        public:

            static void init(IAgentListener *agentListener);

            static void setDebugLog(bool b);

            static string getCampaignPath();

            static string getNativeUnitPathById(const char *unit_id);

            static string getNativeUnitPathByName(const char *unit_id);

            static void fetchFloatUnit(const char *unit_id);

            static void removeAllFloatUnits();
            
            static void showEngagementWindow(const char *unit_id);

            static void forcedExit();
 
    };
}


#endif
