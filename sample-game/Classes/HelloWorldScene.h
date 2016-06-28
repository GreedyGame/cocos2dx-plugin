#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"



#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::LayerColor
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer

	static cocos2d::Scene* createScene();

	// a selector callback
	virtual void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void spriteMoveFinished(cocos2d::Node* sender);

	void gameLogic(float dt);

	void updateGame(float dt);

	void gameOver(std::string msg);

   
protected:
	cocos2d::Vector<cocos2d::Sprite *> _targets;
	cocos2d::Vector<cocos2d::Sprite *> _projectiles;
	int _projectilesDestroyed;

	void addTarget();


};

#endif  // __HELLOWORLD_SCENE_H__