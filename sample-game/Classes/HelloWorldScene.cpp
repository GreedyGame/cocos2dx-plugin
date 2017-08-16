#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "../../current-sdk/Classes/GreedyGameAgent.h"
#include <string>

using namespace cocos2d;
using namespace greedygame;

int i = 1;
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
    // this->label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    // this->label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                         origin.y + visibleSize.height/2 - label->getContentSize().height));

    // // add the label as a child to this layer
    // this->addChild(this->label, 1);
    //////////////////////////////
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


    //Refresh button
    auto refreshItem = MenuItemImage::create(
                        "CloseNormal.png",
                        "CloseSelected.png",
                        CC_CALLBACK_1(HelloWorld::menuRefreshCallback, this));
    
    // Place the menu item bottom-right conner.
    refreshItem->setPosition(Vec2(origin.x + visibleSize.width - (closeItem->getContentSize().width*2) ,
                        origin.y + closeItem->getContentSize().height/2));
    

    // create menu, it's an autorelease object
    auto menu2 = Menu::create(refreshItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);




    i = 1;

    /////////////////////////////
    // 2. add your codes below...
    auto player = Sprite::create();
    std::string unitPath = GreedyGameAgent::getNativeUnitPathById("unit-2335");
    CCLOG("unitPath = %s", unitPath.c_str());
    if(!unitPath.empty()){
        player = Sprite::create(unitPath);
    }else{
        player = Sprite::create("Player.png");
    }
    player->setAnchorPoint(Vec2(0.5,0.5));
    
    GreedyGameAgent::fetchFloatUnit("float-1877");

    GreedyGameAgent::showEngagementWindow("float-1877");
    
    
    player->setPosition( Vec2(origin.x + player->getContentSize().width/2 + 5,
                             origin.y + visibleSize.height/2));
    this->addChild(player);

    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

 
    this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );

    _targets.clear();
    _projectiles.clear();
   
    this->schedule( schedule_selector(HelloWorld::updateGame) );
        
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    GreedyGameAgent::forcedExit();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::menuRefreshCallback(Ref* pSender)
{
    
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

    GreedyGameAgent::removeFloatUnit("float-1877");

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
        CCLOG( "GAME OVER");
        this->gameOver("You Lose");
    }
}

// cpp with cocos2d-x
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    // Choose one of the touches to work with
    Point location = touch->getLocation();

    CCLOG("++++++++after  x:%f, y:%f", location.x, location.y);

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
                CCLOG( "Win..");
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



