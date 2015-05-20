GreedyGame Cocos2d-x Integration Guide
===================

Common for both iOS & Android
---------------------------------------

#### Initialisation

* Download [GreedyGame_Cocos2-x.zip](#publish-a-document) and unzip it.
* You will find a folder named greedygame.
* In this folder you will find *GreedyGameSDK.h* . **iOS** and **Android** will share this header file. Add this to your cocos2d-x project.
* In your project's *AppDelegate.cpp*, add following code to `applicationDidFinishLaunching()` function:-

```
/*
 * All resource path with prefix greedygame/**, 
 * will be considered for native ads
 */ 
CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
std::vector<std::string> searchPaths;
searchPaths.push_back("greedygame/common");
searchPaths.push_back("greedygame/level1");
searchPaths.push_back("greedygame/level2");
CCFileUtils::sharedFileUtils()-> setSearchPaths(searchPaths);
```

> **Note:**
> All resource path with prefix greedygame/*,   will be considered for native ads
 
 
Fetching Campaigns
----------
In your Splash scene (very first scene of game), add following code in method `SplashScene::init()`. Where `onInit` is callback function. 

```
greedygameSDK::GreedyGameSDK::initialize("<your game id>", &onInit);

```

Define callback functions as

```
void onInit(int r) {
    /*
     * -1 = using no campaign
     * 0 = campaign already cached
     * 1 = new campaign found to download
     * 2 = new campaign is downloaded
     */
    if(r == 0 || r == 1) {
        if(r == 1){
            //check for button
            greedygameSDK::GreedyGameSDK::download(&onProgress);
        }
    }

    if(r == -1 || r == 0 || r == 2){
        if(r == 0 || r == 2){
            greedygameSDK::GreedyGameSDK::setPath();
        }
        pLabel->setString("using default theme");
        CCDirector *pDirector = CCDirector::sharedDirector();
        CCScene *pScene = HelloWorld::scene();
        pDirector->runWithScene(pScene);
    }
}
```


Android
----------
* Copy android folder (found in greedygame folder) to your project.
* In your project's jni/Android.mk file, add an entry for `GreedyGame.cpp` file.
* Copy `GreedyGameAgent.jar` to project's libs folder.
* Ensure `android-support-v4.jar` is present here.
* Add required permissions in **AndroidManifest.xml** file as shown below:-

```
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
<uses-permission android:name="android.permission.INTERNET"/>
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>
<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION"/>
```

* In your main activity's life cycle functions, add the following code:-
```
AdsGreedyGame.setup(this, Cocos2dxGLSurfaceView.getInstance()); 
```

iOS
-----

**TBD**




--------
Congratulations! You just completed the integration. Now you can test your game with GreedyGame integrated, by making an theme at panel.greedygame.com

------
