
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"

using namespace cocos2d;
using namespace greedygame;


class GreedyAgentListener : public IAgentListener {
    public:

    void onAvailable(const char *message) {
    /**
     * TODO: New campaign is available and ready to use for the next scene.
     **/
        //restartGame();
        CCLOG("GG[GOScene] onAvailable callback removing listener and switching to gameplay scene");
       // GreedyGameAgent::fetchFloatUnit("float-1935");
        GreedyGameAgent::removeListener();
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene);
    }

    void onUnavailable(){
    /**
     * TODO: New campaign has been loaded, move to next scene
     **/
        CCLOG("GG[GOScene] onUnavailable callback removing listener and switching to gameplay scene");
        GreedyGameAgent::removeListener();
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene);
    }

    void onFound(){
    /**
     * TODO: progress will show value from o to 100,
     * which can be used to render loading bar.
     **/
    }

    void onProgress(int progress){
        /**
         * TODO: progress will show value from o to 100,
         * which can be used to render loading bar.
         **/
         CCLOG("onProgress callback inside cocos cpp wrapper");
        }

    void onError(const char *message){
        /**
         * TODO: callback which notifies of the error
         **/
        std::string s(message);
        CCLOG("GG[GOScene] onError callback removing listener and switching to gameplay scene");
        GreedyGameAgent::removeListener();
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene);
        }

    };

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool GameOverScene::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
	auto winSize = Director::getInstance()->getWinSize();
	this->label = Label::createWithTTF("HERE...", "fonts/Marker Felt.ttf", 24);
	this->label->setColor(Color3B(0,0,0));
	this->label->setPosition( Vec2(winSize.width/2, winSize.height/2) );
	this->addChild(this->label, 1);
    GreedyGameAgent::setListener(new GreedyAgentListener());
    GreedyGameAgent::startEventRefresh();
	Label* tapLabel = Label::createWithTTF("Tap to restart", "fonts/Marker Felt.ttf", 18);
	tapLabel->setColor(Color3B(0,0,0));
	tapLabel->setPosition( Vec2(winSize.width/2, winSize.height/2 - 30) );
	this->addChild(tapLabel, 1);

	auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene); 
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
	return true;
}



