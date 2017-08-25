
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"

using namespace cocos2d;
using namespace greedygame;


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

    //GreedyGameAgent::removeAllFloatUnits();
	auto winSize = Director::getInstance()->getWinSize();
	this->label = Label::createWithTTF("HERE...", "fonts/Marker Felt.ttf", 24);
	this->label->setColor(Color3B(0,0,0));
	this->label->setPosition( Vec2(winSize.width/2, winSize.height/2) );
	this->addChild(this->label, 1);

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

