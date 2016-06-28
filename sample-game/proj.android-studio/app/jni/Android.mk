LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../libs/cocos2d-x)
$(call import-add-path,$(LOCAL_PATH)/../../../libs/cocos2d-x/external)
$(call import-add-path,$(LOCAL_PATH)/../../../libs/cocos2d-x/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../libs/cocos2d-x/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/LoadingScene.cpp \
                   ../../../Classes/HelloWorldScene.cpp \
                   ../../../Classes/GameOverScene.cpp \
                   ../../../../current-sdk/Classes/GreedyGameAgent.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
