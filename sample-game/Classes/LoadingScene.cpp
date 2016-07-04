#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"

USING_NS_CC;
using namespace greedygame;

void moveToNextScene() {

    LoadingScene::getInstance()->label->setString("Tap to start game!");
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto scene = HelloWorld::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene); 
        return true;
    };
    LoadingScene::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, LoadingScene::getInstance());
}

class AgentListener : public IAgentListener {
    public:

    void onAvailable() {
    /**
     * TODO: New campaign is available and ready to use for the next scene.
     **/
        moveToNextScene();
    }

    void onUnavailable(){
    /**
     * TODO: New campaign has been loaded, move to next scene
     **/
        moveToNextScene();
    }

    void onProgress(int progress){
    /**
     * TODO: progress will show value from o to 100,
     * which can be used to render loading bar.
     **/
    }

    void onPermissionsUnavailable(std::vector<std::string> permissions){
    /**
     * TODO: Prompt user to give required permission
     **/
        for (int i=0; i < permissions.size(); i++) {
            std::string p = permissions[i];
            CCLOG("permission unavailable = %s", p.c_str());
        }
    }
};



LoadingScene* LoadingScene::_instance = NULL;
LoadingScene::LoadingScene(){
    CCLOG("LoadingScene Constructor");
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
    
    GreedyGameAgent::init(new AgentListener());

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
    
    return true;
}
