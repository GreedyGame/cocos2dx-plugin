#include "cocos2d.h"

class LoadingScene : public cocos2d::LayerColor
{
	LoadingScene();
	static LoadingScene* _instance;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* label;

    static LoadingScene* getInstance();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
};

