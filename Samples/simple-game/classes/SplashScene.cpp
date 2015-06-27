#include "SplashScene.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "GreedyGameSDK.h"



USING_NS_CC;



CCLabelTTF* pLabel;

CCScene* SplashScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScene *layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void downloadProgress(float f) {
	CCLog( "downloadProgress > : %f", f);
	ostringstream myString;
	myString << "Loading progress " << f <<"%";
	std::string s = myString.str();
	pLabel->setString(s.c_str());
}

void on_init(int r) {
	CCLog( "> on_init %d", r);
	/*
	 * GG_CAMPAIGN_NOT_FOUND, -1 = using no campaign
	 * GG_CAMPAIGN_CACHED, 0 = campaign already cached
	 * GG_CAMPAIGN_FOUND, 1 = new campaign found to Download
	 * GG_CAMPAIGN_DOWNLOADED, 2 = new campaign is Downloaded
	 * GG_ADUNIT_OPENED, 3 = AdUnit Opened
	 * GG_ADUNIT_CLOSED, 4 = AdUnit Closed
	 */
    
	int isBranded = -1;
	if(r == GG_CAMPAIGN_CACHED || r == GG_CAMPAIGN_DOWNLOADED){
		isBranded = 1;
	}else if(r == GG_CAMPAIGN_NOT_FOUND){
		isBranded = 0;
	}

	if(isBranded > -1){
		greedygame::GreedyGameSDK::fetchAdHead("unit-385");
		CCDirector *pDirector = CCDirector::sharedDirector();
		CCScene *pScene = HelloWorld::scene();
		pDirector->replaceScene(pScene);
	}

	if(r == GG_ADUNIT_OPENED){
		//Make pause
	}else if(r == GG_ADUNIT_CLOSED){
		//Make unpause
	}
}



// on "init" you need to initialize your instance
bool SplashScene::init()
{
	greedygame::GreedyGameSDK::setDebug(true);
	greedygame::GreedyGameSDK::initialize("43208054", &on_init, &downloadProgress);

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // add "SplashScene" splash screen"
    CCSprite* pSprite = CCSprite::create("splash.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
    
    pLabel = CCLabelTTF::create("Loading...", "Arial", 48);
    pLabel->setPosition(ccp(visibleSize.width/2 + origin.x,
                            visibleSize.height/2 + origin.y - 200));
    pLabel->setColor(ccc3(0,0,0));
    this->addChild(pLabel, 1);


    return true;
}




