#ifndef __SCORES_SCENE_H__
#define __SCORES_SCENE_H__

#include "cocos2d.h"

class ScoresScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void keyBackClicked();
    LAYER_NODE_FUNC( ScoresScene );
};

#endif // __SCORES_SCENE_H__
