
/****************************************************************************
 Copyright (c) 2014-15  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>

using namespace std;

#define GG_CAMPAIGN_NOT_FOUND -1
#define GG_CAMPAIGN_CACHED 0
#define GG_CAMPAIGN_FOUND 1
#define GG_CAMPAIGN_DOWNLOADED 2

namespace greedygame {

    class GreedyGameSDK
    {


    public:

        static void initialize(const char *gameId, void (*init_callback)(int), void (*progress_callback)(float));

        static void setDebug(bool b);

        static void fetchAdHead(const char *unit_id);

        static void removeAdHead(const char *unit_id);

        static std::string getActivePath();

        static void onCustomEvent(const char *event_name);

    };
}


#endif
