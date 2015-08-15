
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
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
#define GG_ADUNIT_OPENED 3
#define GG_ADUNIT_CLOSED 4

namespace greedygame {

    class GreedyGameSDK
    {

    private:

    	static std::string _getActivePath();

    public:

        static void initialize(const char *gameId, void (*init_callback)(int), void (*progress_callback)(float));

        static void setPath();

        static void setDebug(bool b);

        static void cancelDownload();

        static void fetchAdHead(const char *unit_id);

        static void removeAdHead(const char *unit_id);

        static void onCustomEvent(const char *event_name);

    };
}


#endif
