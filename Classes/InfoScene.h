#ifndef __INFO_SCENE_H__
#define __INFO_SCENE_H__

#include "cocos2d.h"

class InfoScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void keyBackClicked();
    LAYER_NODE_FUNC( InfoScene );
};

#endif // __INFO_SCENE_H__
