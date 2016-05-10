GreedyGame Cocos2d-x Integration Guide
===================
​
## Setup Units
​
All the units can be setup easily from panel.greedygame.com
​

### Native Ad-units
* Goto, sidemenu, AdUnit then drag and drop assets which has to be used for branding.
​

### Floating Ad-units
* Goto, sidemenu, AdUnit then click on "Add float unit" to create one unit.
* Note down the floating unit-ID that was generated ! (Use the same ID's while initializing GreedyGameAgent)

​
---------------------------------------
## Initialisation
​
* Download [Android library project](Current_sdk/proj.android) from Current_sdk/proj.android.
* You will find a folder named [Classes](Current_sdk/Classes).
* In this folder you will find *GreedyGameSDK.h* . **iOS** and **Android** will share this header file. Add this to your cocos2d-x project.
* Put all branded assets under folder Resources/greedygame
​
> **Note:**
> Resources/greedygame directory should only contain images and no sub-directories
 
 Declare the following string in strings.xml file  under the res/values folder.
```xml
<string name="greedy_game_profile">"your-game-id-without-quotes"</string>
```
 
## Cocos Android Activity : 

* In your Game's Cocos Android Activity's onCreate() function add the following code
```java
protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);

		AdsGreedyGame.setup(this, Cocos2dxGLSurfaceView.getInstance());
		AdsGreedyGame.setDebug(false);
		AdsGreedyGame.addFloatUnits("float-701");
		AdsGreedyGame.addNativeUnits("Projectile.png");
	}
```
> **Note:**
> use addFloatUnits(String floatID) and addNativeUnits(String filenamewithextension) for adding any number of native and float units you want in your game ! 



## Fetching Campaigns
​
In your Splash scene (very first scene of game), add following code in method `SplashScene::init()`. Where `onInit` is callback function. 
​
```cpp
greedygame::GreedyGameSDK::initialize(&onInit, &onProgress);
​
```
​
### Define callback functions as

#### onInit

```cpp
void onInit(int event) {
    CCLog( "> onInit %d", event);
    /*
     * CAMPAIGN_NOT_AVAILABLE, -1 = campaign is not available              
     * CAMPAIGN_AVAILABLE, 1 = campaign is available 
     * CAMPAIGN_DOWNLOADED, 2 = new campaign is Downloaded
     *
     */
    
    int isBranded = -1;
    if(event == CAMPAIGN_AVAILABLE){
        isBranded = 1;
    } else if(event == CAMPAIGN_NOT_AVAILABLE){
        isBranded = 0;
    } else if(event == CAMPAIGN_DOWNLOADED) {
        isBranded = 1;
    }
​
    if(isBranded == 1){
        greedygame::GreedyGameSDK::fetchAdHead("<floating unit-id>");
        CCDirector *pDirector = CCDirector::sharedDirector();
        CCScene *pScene = HelloWorld::scene();
        pDirector->replaceScene(pScene);
    }
}
```
​
#### onProgress
```cpp
void onProgress(float f) {
    CCLog( "downloadProgress > : %f", f);
    ostringstream myString;
    myString << "Loading progress " << f <<"%";
    std::string s = myString.str();
    pLabel->setString(s.c_str());
}
```



### **FLOAT AD UNIT**

#### Fetch floating units
`greedygame::GreedyGameSDK::fetchAdHead("<floating unit-id>");`
​
#### Remove floating units
`greedygame::GreedyGameSDK::removeAdHead();`
​
Android
----------
* Copy android folder (found in greedygame folder) to your project.
* In your project's jni/Android.mk file, add an entry for `GreedyGameSDK.cpp` file.
* Add required permissions in **AndroidManifest.xml** file as shown below:-
​
```xml
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
<uses-permission android:name="android.permission.GET_ACCOUNTS" />
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
​
<application >      
    <activity
        android:name="com.greedygame.android.adhead.GGAdHeadActivity"          
        android:theme="@style/Theme.Transparent" 
        android:configChanges = "keyboardHidden|orientation|screenSize|screenLayout|layoutDirection" 
        android:launchMode="singleTask">
    </activity>
    
    <receiver 
            android:name="com.greedygame.android.agent.GreedyRefReceiver" 
            android:enabled="true" 
            android:exported="true">
      <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
        <action android:name="com.greedygame.broadcast" />
        <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
      </intent-filter>
    </receiver>
</application>
```
​​
#### **CALLBACK METHOD IN WRAPPER :** onPermissionsUnavailable(ArrayList<String> permissions)
* This method needs to be used only if your game is targetting SDK version 23 or higher. This callback gives a list of permissions that are not available at runtime and is invoked after GreedyGameAgent initialization.
​
  NB : Only performs check for 4 runtime permissions that are required by GreedyGameSDK. 
​
  Permissions that are checked : 
​
   * Manifest.permission.ACCESS_COARSE_LOCATION
   * Manifest.permission.WRITE_EXTERNAL_STORAGE
   * Manifest.permission.GET_ACCOUNTS
   * Manifest.permission.READ_PHONE_STATE
​
   NB : The above strings itself are returned in the argument if they are not available.
​
##### 
Congratulations! You just completed the integration. Now you can test your game with GreedyGame integrated, by making an theme at panel.greedygame.com
​​
### External Jars
GreedyGame SDK uses Volley from Google as external jar. In case of conflicts you can remove it from libs folder of the wrapper. 
​
### For more help please see [FAQ] (https://github.com/GreedyGame/unity-plugin/wiki/FAQs)
