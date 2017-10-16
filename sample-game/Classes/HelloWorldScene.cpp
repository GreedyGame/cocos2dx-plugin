#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"
#include <string>
#include <exception>
#include "LoadingScene.h"


using namespace cocos2d;
using namespace greedygame;
//using namespace loadingscene;

int i = 1;
Sprite* player ;
Node* greedyNative;

Sprite* floatSprite ;
Node* greedyFloatNode;

class HelloWorldGGListener : public IAgentListener {
    public:



    void onAvailable(const char *campaignId) {
    /**
     * TODO: New campaign is available and ready to use for the next scene.
     **/
        CCLOG("GG[HWScene] onAvailable : Hello world scene onAvailable");
        refreshNativeUnits();
        refreshFloatUnits();
    }

    void onUnavailable(){
    /**
     * TODO: Update and remove the native and float units since after refresh there was no campaign available.
     **/
     CCLOG("Hello world scene onUnavailable");
     refreshNativeUnits();
     refreshFloatUnits();
    }

    void onFound(){
    /**
     * TODO: progress will show value from o to 100,
     * which can be used to render loading bar.
     **/
     CCLOG("Hello world scene onFound");
    }

    void onProgress(int progress){
        /**
         * TODO: progress will show value from o to 100,
         * which can be used to render loading bar.
         **/
         CCLOG("Hello world scene onProgress");
        }

    void onError(const char *message){
        /**
     * TODO: Update and remove the native and float units since after refresh there was no campaign available.
     **/
        CCLOG("Hello world scene onError");
         //CCLOG("onError callback inside cocos cpp wrapper" + message);
        }    


    void refreshNativeUnits() {
        CCLOG("GG[HWScene] refresh native called from onAvailable callback");
        greedyNative->removeChild(player,true);
        auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
    	player = Sprite::create();
    	std::string unitPath = GreedyGameAgent::getNativeUnitPathById("unit-2335");
    	CCLOG("unitPath = %s", unitPath.c_str());
    	if(!unitPath.empty()){
    	    player = Sprite::create(unitPath);
    	    if(player == NULL) {
					player = Sprite::create("Player.png");
    		}
    	}else{
    	    player = Sprite::create("Player.png");
    	}
    	player->setAnchorPoint(Vec2(0.5,0.5));
    	player->setPosition( Vec2(origin.x + player->getContentSize().width/2 + 5,
                         origin.y + visibleSize.height/2));
    	greedyNative->addChild(player);
	}

    void refreshFloatUnits() {
        CCLOG("GG[HWScene] refresh float called from onAvailable callback");
        greedyFloatNode->removeChild(floatSprite,true);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        floatSprite = Sprite::create();
        std::string unitPath = GreedyGameAgent::getFloatUnitPathById("float-1877");
        CCLOG("unitPath = %s", unitPath.c_str());
        if(!unitPath.empty()){
            floatSprite = Sprite::create(unitPath);
            if(floatSprite == NULL) {
                    floatSprite = Sprite::create("Player.png");
            }
        }else{
            floatSprite = Sprite::create("Player.png");
        }
        floatSprite->setAnchorPoint(Vec2(0.5,0.5));
        floatSprite->setPosition( Vec2(visibleSize.width - floatSprite->getContentSize().width/2 + 5,
                         origin.y + visibleSize.height/2));
        greedyFloatNode->addChild(floatSprite);
    }


};


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(172, 115, 57,255)) )
    {
        return false;
    }
    
    //////////////////////////////////////////////////////////////////////////
    // add your codes below...
    //////////////////////////////////////////////////////////////////////////

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. Add a menu item with "X" image, which is clicked to quit the program.

    // Create a "close" menu item with close icon, it's an auto release object.
    auto closeItem = MenuItemImage::create(
                        "CloseNormal.png",
                        "CloseSelected.png",
                        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    // Place the menu item bottom-right conner.
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                        origin.y + closeItem->getContentSize().height/2));
    

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    

    // INIT 
    auto initButton = MenuItemImage::create("ggbuttons/init.png","ggbuttons/init.png",CC_CALLBACK_1(HelloWorld::initCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    initButton->setPosition(Vec2(100 ,visibleSize.height - 40));
    auto initMenu = Menu::create(initButton, NULL);
    initMenu->setPosition(Vec2::ZERO);
    this->addChild(initMenu, 3);


    //ShowFloat
    auto showFloatButton = MenuItemImage::create("ggbuttons/showFloat.png","ggbuttons/showFloat.png",CC_CALLBACK_1(HelloWorld::showFloatCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    showFloatButton->setPosition(Vec2(210 ,visibleSize.height - 40));
    auto showFloatMenu = Menu::create(showFloatButton, NULL);
    showFloatMenu->setPosition(Vec2::ZERO);
    this->addChild(showFloatMenu, 4);


    //removeFloat
    auto removeFloatButton = MenuItemImage::create("ggbuttons/removeFloat.png","ggbuttons/removeFloat.png",CC_CALLBACK_1(HelloWorld::removeFloatCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    removeFloatButton->setPosition(Vec2(320 ,visibleSize.height - 40));
    auto removeFloatMenu = Menu::create(removeFloatButton, NULL);
    removeFloatMenu->setPosition(Vec2::ZERO);
    this->addChild(removeFloatMenu, 5);


    //removeAllFloats
    auto removeAllFloatsButton = MenuItemImage::create("ggbuttons/removeAllFloats.png","ggbuttons/removeAllFloats.png",CC_CALLBACK_1(HelloWorld::removeAllCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    removeAllFloatsButton->setPosition(Vec2(100 ,visibleSize.height - 100));
    auto removeAllFloatsMenu = Menu::create(removeAllFloatsButton, NULL);
    removeAllFloatsMenu->setPosition(Vec2::ZERO);
    this->addChild(removeAllFloatsMenu, 6);


    //getFloatPath
    auto getFloatPathButton = MenuItemImage::create("ggbuttons/getFloatPath.png","ggbuttons/getFloatPath.png",CC_CALLBACK_1(HelloWorld::getFloatPathCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    getFloatPathButton->setPosition(Vec2(210 ,visibleSize.height - 100));
    auto getFloatPathMenu = Menu::create(getFloatPathButton, NULL);
    getFloatPathMenu->setPosition(Vec2::ZERO);
    this->addChild(getFloatPathMenu, 6);

    //getNativePath
    auto getNativePathButton = MenuItemImage::create("ggbuttons/getNativePath.png","ggbuttons/getNativePath.png",CC_CALLBACK_1(HelloWorld::getNativePathCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    getNativePathButton->setPosition(Vec2(320 ,visibleSize.height - 100));
    auto getNativePathMenu = Menu::create(getNativePathButton, NULL);
    getNativePathMenu->setPosition(Vec2::ZERO);
    this->addChild(getNativePathMenu, 7);


    //showUII
    auto showUIIButton = MenuItemImage::create("ggbuttons/showUII.png","ggbuttons/showUII.png",CC_CALLBACK_1(HelloWorld::showUIICallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    showUIIButton->setPosition(Vec2(100 ,visibleSize.height - 160));
    auto showUIIMenu = Menu::create(showUIIButton, NULL);
    showUIIMenu->setPosition(Vec2::ZERO);
    this->addChild(showUIIMenu, 8);


    //setListener
    auto setListenerButton = MenuItemImage::create("ggbuttons/setListener.png","ggbuttons/setListener.png",CC_CALLBACK_1(HelloWorld::setListenerCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    setListenerButton->setPosition(Vec2(210 ,visibleSize.height - 160));
    auto setListenerMenu = Menu::create(setListenerButton, NULL);
    setListenerMenu->setPosition(Vec2::ZERO);
    this->addChild(setListenerMenu, 9);


    //startRefresh
    auto refreshButton = MenuItemImage::create("ggbuttons/refresh.png","ggbuttons/refresh.png",CC_CALLBACK_1(HelloWorld::refreshCallback, this));
    // initButton->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                     origin.y + closeItem->getContentSize().height/2));
    refreshButton->setPosition(Vec2(320 ,visibleSize.height - 160));
    auto refreshMenu = Menu::create(refreshButton, NULL);
    refreshMenu->setPosition(Vec2::ZERO);
    this->addChild(refreshMenu, 10);

    i = 1;    
    /////////////////////////////
    // 2. add your codes below...
        CCLOG( "GG[HWScene] Adding Native unit as native float for id : 2335 inside game by default" );
        	greedyNative = Node::create();
    		player = Sprite::create();
    		std::string unitPath = GreedyGameAgent::getNativeUnitPathById("unit-2335");
    		CCLOG("unitPath = %s", unitPath.c_str());
    	
    			if(!unitPath.empty()){
    			    player = Sprite::create(unitPath);
    			    if(player == NULL){
						player = Sprite::create("Player.png");
    			    }
    			}else{
    			    player = Sprite::create("Player.png");
    			}
    	
    	
    		player->setAnchorPoint(Vec2(0.5,0.5));
    		player->setPosition( Vec2(origin.x + player->getContentSize().width/2 + 5,
                             origin.y + visibleSize.height/2));
    		greedyNative->addChild(player);
    		this->addChild(greedyNative);





        CCLOG( "GG[HWScene] Adding FloatUnit as native float for id : 1877 inside game by default" );
            greedyFloatNode = Node::create();
            floatSprite = Sprite::create();
            std::string unitPath2 = GreedyGameAgent::getFloatUnitPathById("float-1877");
            CCLOG("unitPath = %s", unitPath2.c_str());
        
                if(!unitPath2.empty()){
                    floatSprite = Sprite::create(unitPath2);
                    if(floatSprite == NULL){
                        floatSprite = Sprite::create("Player.png");
                    }
                }else{
                    floatSprite = Sprite::create("Player.png");
                }
        
        
            floatSprite->setAnchorPoint(Vec2(0.5,0.5));
            floatSprite->setPosition( Vec2(visibleSize.width - floatSprite->getContentSize().width/2 + 5,
                             origin.y + visibleSize.height/2));
            greedyFloatNode->addChild(floatSprite);
            this->addChild(greedyFloatNode);
    
    
    // GreedyGameAgent::fetchFloatUnit("float-1877");

    // GreedyGameAgent::showEngagementWindow("float-1877");    
    
    
    

    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

 
    this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );

    _targets.clear();
    _projectiles.clear();
   
    this->schedule( schedule_selector(HelloWorld::updateGame) );
        
    return true;
}



//INIT callback
void HelloWorld::initCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] initCallback called");
    GreedyGameAgent::init(new HelloWorldGGListener());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//setListener callback
void HelloWorld::setListenerCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] setListener called");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//ShowfLoat callback
void HelloWorld::showFloatCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] showFloat will be called with id : 1877");
    GreedyGameAgent::fetchFloatUnit("float-1877");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//RemovefLoat callback
void HelloWorld::removeFloatCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] removeFloat will be called with id : 1877");
    GreedyGameAgent::removeFloatUnit("float-1877");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//getfLoatPath callback
void HelloWorld::getFloatPathCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] getFloatUnitPathById will be called with id 1877");
    GreedyGameAgent::getFloatUnitPathById("float-1877");
    refreshFloatUnits();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//getNativePath
void HelloWorld::getNativePathCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] calling getNativePath with unit id unit-2335");
    GreedyGameAgent::getNativeUnitPathById("unit-2335");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//remove All Callback callback
void HelloWorld::removeAllCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] calling 2 floats (1877 & 1878) and then calling removeAllFloatUnits");
    GreedyGameAgent::fetchFloatUnit("float-1877");
    GreedyGameAgent::fetchFloatUnit("float-1878");
    GreedyGameAgent::removeAllFloatUnits();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//getNativePath
void HelloWorld::refreshCallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] startEventRefresh will be called");
    GreedyGameAgent::setListener(new HelloWorldGGListener());
    GreedyGameAgent::startEventRefresh();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//show UII
void HelloWorld::showUIICallback(Ref* pSender)
{
    CCLOG( "GG[HWScene] showEngagementWindow will be called with float1877");
    GreedyGameAgent::showEngagementWindow("float-1877");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //GreedyGameAgent::forcedExit();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::menuRefreshCallback(Ref* pSender)
{

    std::string unitPath = GreedyGameAgent::getFloatUnitPathById("float-1877");
    CCLOG("GG[HWScene] inside menuRefreshCallback unitPath = %s", unitPath.c_str());
    GreedyGameAgent::startEventRefresh();
}

// cpp with cocos2d-x
void HelloWorld::addTarget()
{
    Sprite *target = Sprite::create("Monster.png", Rect(0,0,145,100) );
    // Determine where to spawn the target along the Y axis
    auto winSize = Director::getInstance()->getVisibleSize();
    float minY = target->getContentSize().height/2;
    float maxY = winSize.height -  target->getContentSize().height/2;
    int rangeY = (int)(maxY - minY);
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + (int)minY;

    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( 
        Vec2(winSize.width + (target->getContentSize().width/2), 
            Director::getInstance()->getVisibleOrigin().y + actualY) );
    this->addChild(target);

    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration ) + minDuration;

    // Create the actions
    auto actionMove = MoveTo::create((float)actualDuration, Vec2(0 - target->getContentSize().width/2, actualY));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    auto seq = Sequence::create(actionMove, actionMoveDone, NULL);
    target->runAction(seq);

    // Add to targets array
    target->setTag(1);
    _targets.pushBack(target);
}

void HelloWorld::spriteMoveFinished(cocos2d::Node* sender)
{
    Sprite *sprite = (Sprite *)sender;
    this->removeChild(sprite, true);

    if (sprite->getTag() == 1)  // target
    {
        _targets.erase(_targets.find(sprite));
        CCLOG( "Lose..");
    }
    else if (sprite->getTag() == 2) // projectile
    {
        _projectiles.erase(_projectiles.find(sprite));
    }
}

void HelloWorld::gameOver(std::string msg){

    CCLOG( "GG[HWScene] game over");
    GreedyGameAgent::removeFloatUnit("float-1877");
    GreedyGameAgent::removeListener();
    GameOverScene* layer = GameOverScene::create();
    layer->getLabel()->setString(msg);
    auto scene = Scene::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);  
}



void HelloWorld::gameLogic(float dt)
{
    this->addTarget();

    CCLOG( "in %d", i);
    i++;
    if(i > 50){
        CCLOG( "GG[HWScene] GAME OVER");
        this->gameOver("You Lose");
    }
}

// cpp with cocos2d-x
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    // Choose one of the touches to work with
    Point location = touch->getLocation();

    CCLOG("GG[HWScene] ++++++++after  x:%f, y:%f", location.x, location.y);

    // Set up initial location of projectile
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto projectile = Sprite::create("Projectile.png");
    projectile->setPosition( Vec2(origin.x+20, origin.y+visibleSize.height/2) );
    projectile->setTag(2);

    // Determinie offset of location to projectile
    float offX = location.x - projectile->getPosition().x;
    float offY = location.y - projectile->getPosition().y;

    // Bail out if we are shooting down or backwards
    if (offX <= 0) return false;

    // Ok to add now - we've double checked position
    this->addChild(projectile);

    // Determine where we wish to shoot the projectile to
    float realX = origin.x+visibleSize.width + (projectile->getContentSize().width/2);
    float ratio = offY / offX;
    float realY = (realX * ratio) + projectile->getPosition().y;
    Point realDest = Vec2(realX, realY);

    // Determine the length of how far we're shooting
    float offRealX = realX - projectile->getPosition().x;
    float offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
    float velocity = 480/1; // 480pixels/1sec
    float realMoveDuration = length/velocity;


    auto moveTo = MoveTo::create(realMoveDuration, realDest);
    auto callbackMoved = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    auto seq = Sequence::create(moveTo, callbackMoved,NULL);
    // Move projectile to actual endpoint
    projectile->runAction(seq);

    // Add to projectiles array
    _projectiles.pushBack(projectile);

    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("pew-pew-lei.wav");
    audio->playBackgroundMusic("pew-pew-lei.wav");

    return true;
}

void HelloWorld::updateGame(float dt)
{
    Vector<Sprite *> projectilesToDelete;
    for(auto it: _projectiles)
    {
        Sprite *projectile = dynamic_cast<Sprite *>(it);

        Rect projectileRect = Rect(
            projectile->getPosition().x - (projectile->getContentSize().width/2),
            projectile->getPosition().y - (projectile->getContentSize().height/2),
            projectile->getContentSize().width,
            projectile->getContentSize().height);

        Vector<Sprite *> targetsToDelete;

        for(auto jt: _targets)
        {
            Sprite *target = dynamic_cast<Sprite*>(jt);
            Rect targetRect = Rect(
                target->getPosition().x - (target->getContentSize().width/2),
                target->getPosition().y - (target->getContentSize().height/2),
                target->getContentSize().width,
                target->getContentSize().height);

            if (projectileRect.intersectsRect(targetRect))
            {
                targetsToDelete.pushBack(target);
            }
        }

        for(auto jt:targetsToDelete)
        {
            Sprite *target = dynamic_cast<Sprite*>(jt);
            _targets.erase(_targets.find(target));
            this->removeChild(target, true);

            _projectilesDestroyed++;
            if (_projectilesDestroyed >= 25)
            {
                CCLOG( "GG[HWScene] Win..");
                this->gameOver("You Win");
            }
        }

        if (targetsToDelete.size() > 0)
        {
            projectilesToDelete.pushBack(projectile);
        }
        targetsToDelete.clear();
    }

    for(auto it:projectilesToDelete)
    {
        Sprite* projectile = dynamic_cast<Sprite*>(it);
        _projectiles.erase(_projectiles.find(projectile));
        this->removeChild(projectile, true);
    }
    projectilesToDelete.clear();
}


void HelloWorld::refreshFloatUnits() {
        CCLOG("GG[HWScene] refresh float called from onAvailable for native float");
        //greedyFloatNode->removeChild(floatSprite,true);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        floatSprite = Sprite::create();
        std::string unitPath = GreedyGameAgent::getFloatUnitPathById("float-1877");
        CCLOG("GG[HWScene] unitPath = %s", unitPath.c_str());
        if(!unitPath.empty()){
            floatSprite = Sprite::create(unitPath);
            if(floatSprite == NULL) {
                    floatSprite = Sprite::create("Player.png");
            }
        }else{
            floatSprite = Sprite::create("Player.png");
        }
        floatSprite->setAnchorPoint(Vec2(0.5,0.5));
        floatSprite->setPosition( Vec2(visibleSize.width - floatSprite->getContentSize().width/2 + 5,
                         origin.y + visibleSize.height/2));
        greedyFloatNode->addChild(floatSprite);
}


void HelloWorld::refreshNativeUnits() {
        CCLOG("GG[HWScene] refresh native called from onAvailable");
        //greedyNative->removeChild(player,true);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        player = Sprite::create();
        std::string unitPath = GreedyGameAgent::getNativeUnitPathById("unit-2335");
        CCLOG("GG[HWScene] unitPath = %s", unitPath.c_str());
        if(!unitPath.empty()){
            player = Sprite::create(unitPath);
            if(player == NULL) {
                    player = Sprite::create("Player.png");
            }
        }else{
            player = Sprite::create("Player.png");
        }
        player->setAnchorPoint(Vec2(0.5,0.5));
        player->setPosition( Vec2(origin.x + player->getContentSize().width/2 + 5,
                         origin.y + visibleSize.height/2));
        greedyNative->addChild(player);
}
