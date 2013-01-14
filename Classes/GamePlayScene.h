#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyContactListener.h"
#include <time.h>

class GamePlayScene : public cocos2d::CCLayer {
public:
	GamePlayScene();
	~GamePlayScene();
	virtual bool init();
	static cocos2d::CCScene* scene();
	static cocos2d::CCScene* scene(int l);
	virtual void keyBackClicked();
	LAYER_NODE_FUNC(GamePlayScene);

private:
    virtual void didAccelerate(cocos2d::CCAcceleration *pAccelerationValue);
    void tick(cocos2d::ccTime delta);
    b2World *world;
    b2Body *body;
    cocos2d::CCSprite *ball;
    cocos2d::CCSprite *hole;
    MyContactListener * contactListener;
    b2Fixture *_ballFixture;
    b2Fixture *_holeFixture;
    int ptmRatio;
    clock_t start, stop;
    static int level;
};

#endif // __GAMEPLAY_SCENE_H__
