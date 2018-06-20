#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"
#include <string>

USING_NS_CC;
using namespace greedygame;

bool isLoaded = false;


void moveToNextScene() {

if(!isLoaded) {
    CCLOG("GG[LS]-move to next scene");
    isLoaded = true;
    LoadingScene::getInstance()->label->setString("Tap to start game!");
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        CCLOG("GG[LS]-Touch Began");
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene); 
        CCLOG("GG[LS]-Hello World Scene created successfully");
        return true;
    };
    CCLOG("GG[LS]-Touch completed");
    LoadingScene::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, LoadingScene::getInstance());

    }
}


class GreedyAgentListener : public IAgentListener {
    public:

    void onAvailable(const char *campaignId) {
    /**
     * TODO: New campaign is available and ready to use for the next scene.
     **/
        moveToNextScene();
        CCLOG("GG[LS]-onAvailable callback inside cocos cpp wrapper");
       // GreedyGameAgent::fetchFloatUnit("float-1935");
    }

    void onUnavailable(){
    /**
     * TODO: New campaign has been loaded, move to next scene
     **/
        moveToNextScene();
     CCLOG("GG[LS]-onUnavailable callback inside cocos cpp wrapper");
    }

    void onFound(){
    /**
     * TODO: progress will show value from o to 100,
     * which can be used to render loading bar.
     **/
     CCLOG("GG[LS]-onFound callback inside cocos cpp wrapper");
    }

    void onError(const char *message){
        /**
         * TODO: callback which notifies of the error
         **/
    	std::string s(message);
    	CCLOG("GG[LS]-the string received is NIKHIL : %s",s.c_str());
    	 
         //CCLOG("onError callback inside cocos cpp wrapper" + message);
        }

    };



LoadingScene* LoadingScene::_instance = NULL;
LoadingScene::LoadingScene(){
    CCLOG("GG[LS]-LoadingScene Constructor");
    LoadingScene::_instance = this;
}

LoadingScene* LoadingScene::getInstance(){
    return LoadingScene::_instance;
}

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }

    /*CCLOG("GG[LS] init called");*/
    //GreedyGameAgent::init(new GreedyAgentListener());
    // GreedyGameAgent::enableAdmob(true);
    // GreedyGameAgent::enableFacebook(true);
    // GreedyGameAgent::enableMopub(true);
    GGAdOptions* adOptions = new GGAdOptions();
    adOptions->enableAdmobMediation(true);
    adOptions->enableMopubMediation(true);
    adOptions->enableFacebookMediation(true);
    adOptions->withAgentListener(new GreedyAgentListener());
    string unitList[2] = {"float-1877","unit-2335"};
    adOptions->addUnitList(unitList,2);
    adOptions->enforceGgNpa(true);
    //adOptions->addUnitId("float-1877");
    //adOptions->addUnitId("unit-2335");
    GreedyGameAgent::initialize(adOptions);
    //GreedyGameAgent::init();

    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    this->label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 24);
    this->label->setColor(Color3B(0,0,0));
    
    // position the label on the center of the screen
    this->label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(this->label, 1);

    // add "Loading" splash screen"
    auto sprite = Sprite::create("loading.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    //moveToNextScene();
    return true;
}
