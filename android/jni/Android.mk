LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MainMenuScene.cpp\
                   ../../Classes/LevelScene.cpp\
                   ../../Classes/GamePlayScene.cpp\
                   ../../Classes/ScoresScene.cpp\
                   ../../Classes/InfoScene.cpp\
                   ../../Classes/MyContactListener.cpp\
                   ../../Classes/MiniGolfData.cpp
                   
   		   		                      
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static box2d_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx) $(call import-module,Box2D)
