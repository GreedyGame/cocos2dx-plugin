GreedyGame Cocos2d-x's SDK Reference
---------------------
 * [Introduction](#introduction)
 * [Requirements](#requirements)
 * [Integration](#integration)
 * [Documentation](#documentation)
    * [GreedyGameAgent](#greedygameagent)
    * [interface IAgentListener](#interface-iagentlistener)
 * [FAQ](#faq)

 
# Introduction
Before we get started with the detailed reference, let’s brush through the definitions of some important terms that we’ll see referenced regularly. [Here at greedygame.github.io] (http://greedygame.github.io/)

# Requirements
* Android API Version: 14
* Gradle 1.6 or lastest

# Integration
If you have gone through the definitions of important key words. To make the rest of the integration an absolute breeze for you, we’ve set up an integration wizard on your [publisher panel](http://publisher.greedygame.com).

Once you’ve logged in, on the top of your page and select **SDK Integration Wizard** and we’ll walk you through the integration from the comfort of your own publisher panel.

![PublisherPanel's top menu](http://greedygame.github.io/images/wizard.png "SDK Integration Wizard")


# Documentation
### GreedyGameAgent
#### Class Overview
Contains high-level classes encapsulating the overall GreedyGame ad flow and model.
#### Public Constructor
##### `GreedyGameAgent(Activity gameActivity, IAgentListner greedyListner)`
Constructs a new instance of GreedyGame handler.
Install the GreedygameAgent in the activity

#### Public Methods

##### `static void init(IAgentListener *agentListener)`
Lookup for an active campaign from the server.

##### `static string getNativeUnitPathById(const char *unit_id);`
Return path of the [nativeunit](http://greedygame.github.io/#nativeunits), with unit_id, being used in current campaign or null.

##### `static string getNativeUnitPathByName(const char *unit_id)`
Return path of the [nativeunit](http://greedygame.github.io/#nativeunits), with name, being used in current campaign or null.

##### `static void fetchFloatUnit(const char *unit_id)`
Fetch FloatUnit and add view to current context.

##### `static void removeAllFloatUnits()`
Remove all showing FloatUnits
##### `public void showEngagementWindow(string unit_id)`
Open [engagement window](http://greedygame.github.io/#engagementwindow) attached with provided floatunit

##### `static string getCampaignPath`
Return path of folder, where assets of current campaign is stored.

##### `public String getVersion()`
Return version of SDK

##### `static void setDebugLog(bool b)`
Control display of debug of SDK 

##### `static void forcedExit()`
Call this method if game is being exit as
* `System.exit(0);` or
* `android.os.Process.killProcess(android.os.Process.myPid());`

**Note**: if you are using `finish();` function inside the Activity then you **should not call** the above code snippet

----
### interface IAgentListener
#### Class Overview
It is used as a callback listener argument for GreedyGameAgent class

#### Public Methods
##### `void onAvailable()`
When a new campaign is available and ready to use for the next scene.

##### `void onUnavailable()`
When no campaign is available

##### `void onProgress(int progress)`
Gives progress of campaign being downloaded as an integer.

##### `void onPermissionsUnavailable(ArrayList permissions)`
Gives a list of permission unavailable or revoked by the user.

**Permissions that are checked**
```
Manifest.permission.ACCESS_COARSE_LOCATION
Manifest.permission.WRITE_EXTERNAL_STORAGE
Manifest.permission.READ_PHONE_STATE
```
**Interface Example**
```cpp
class GreedyAgentListener: public IAgentListener {
    public:

    void onAvailable() {
        /**
         * TODO: New campaign is available and ready to use for the next scene.
         **/
    }

    void onUnavailable() {
        /**
         * TODO: No campaign is available, proceed with normal follow of the game.
         **/
    }

    void onProgress(int progress) {
        /**
         * TODO: Progress bar can be shown using progress value from 0 to 100.
         **/
    }

    void onPermissionsUnavailable(std::vector <std::string> permissions) {
        /**
         * TODO: Prompt user to give required permission
         **/
        for (int i = 0; i < permissions.size(); i++) {
            std::string p = permissions[i];
            CCLOG("permission unavailable = %s", p.c_str());
        }
    }
};
```

-----

### Proguard Settings

If you are using Proguard add the following to your Proguard settings ! 
```
-keep class com.greedygame.android.** { *;}
-keepattributes JavascriptInterface
-keepclassmembers class * {
    @android.webkit.JavascriptInterface <methods>;
 }
```
 
# FAQ
For more help please see [FAQ](https://github.com/GreedyGame/unity-plugin/wiki/FAQs)
