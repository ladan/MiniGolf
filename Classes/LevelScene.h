#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"

class LevelScene : public cocos2d::CCLayer
{
public:
	int maxlevel;
	int a;
    virtual bool init();
    static cocos2d::CCScene* scene();
    void setGamePlayScene1Callback( CCObject* pSender );
    void setGamePlayScene2Callback( CCObject* pSender );
    void setGamePlayScene3Callback( CCObject* pSender );
    void setGamePlayScene4Callback( CCObject* pSender );
    void setGamePlayScene5Callback( CCObject* pSender );
    void setGamePlayScene6Callback( CCObject* pSender );
    void setGamePlayScene7Callback( CCObject* pSender );
    void setMainMenuSceneCallback( CCObject* pSender );
    virtual void keyBackClicked();
    LAYER_NODE_FUNC(LevelScene);
};

#endif // __LEVEL_SCENE_H__
