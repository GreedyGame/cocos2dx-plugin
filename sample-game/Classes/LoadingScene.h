#include "cocos2d.h"



class MyListener {
        public:
            virtual void onAvailable(){};
            virtual void onUnavailable(){};
            virtual void onProgress(int progress){};
            virtual void onError(const char *msg){};
            virtual void onFound(){};
    };



class LoadingScene : public cocos2d::LayerColor
{
	LoadingScene();
	static LoadingScene* _instance;
public:
    static cocos2d::Scene* createScene();

    static void addListener(MyListener* myListener);

    virtual bool init();

    cocos2d::Label* label;

    static LoadingScene* getInstance();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
};


