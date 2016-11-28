
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

    class CampaignStateListener {
        public:
            virtual void onAvailable(){};
            virtual void onUnavailable(){};
            virtual void onFound(){};
    };

    class CampaignProgressListener {
        public:
            virtual void onProgress(int progress){};
    };

    class GreedyGameAgent {

        public:

            static void init();

            static void setCampaignStateListener(CampaignStateListener* state_listener);

            static void setCampaignProgressListener(CampaignProgressListener* progress_listener);

            static string getNativeUnitPath(const char *unit_id);

            static string getFloatUnitPath(const char *unit_id);

            static void showFloat(const char *unit_id);

            static void removeFloat(const char *unit_id);
            
            static void showUII(const char *unit_id);

            static void forcedExit();
 
    };
}


#endif
