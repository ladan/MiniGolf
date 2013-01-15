#ifndef __SCORESLEVEL_SCENE_H__
#define __SCORESLEVEL_SCENE_H__

#include "cocos2d.h"

class ScoresLevelScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    static cocos2d::CCScene* scene(int l, double t,bool failed);
    void setLevelSceneCallback( CCObject* pSender );
    void setGamePlaySceneCallback( CCObject* pSender);
    void setGamePlayNextSceneCallback( CCObject* pSender);
    void keyBackClicked();
    LAYER_NODE_FUNC( ScoresLevelScene );
private:
    static const double MAX_TIME=15.0;
    static int level;
    static double time;
    static bool failed;
};

#endif // __SCORESLEVEL_SCENE_H__
