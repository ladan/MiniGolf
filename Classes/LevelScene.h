#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"

class LevelScene : public cocos2d::CCLayer
{
public:
	int maxlevel;
    virtual bool init();
    static cocos2d::CCScene* scene();
    void setGamePlaySceneCallback( CCObject* pSender);
    void setMainMenuSceneCallback( CCObject* pSender );
    virtual void keyBackClicked();
    LAYER_NODE_FUNC(LevelScene);
};

#endif // __LEVEL_SCENE_H__
