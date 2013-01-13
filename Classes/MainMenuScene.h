#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback( CCObject* pSender );
    void setLevelSceneCallback( CCObject* pSender );
    void setScoresSceneCallback( CCObject* pSender );
    void setInfoSceneCallback( CCObject* pSender );
    void exitCallback( CCObject* pSender );
    virtual void keyBackClicked();
    LAYER_NODE_FUNC(MainMenuScene);
};

#endif // __MAINMENU_SCENE_H__
