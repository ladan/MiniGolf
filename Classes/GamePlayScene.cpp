#include "GamePlayScene.h"
#include "ScoresLevelScene.h"
#include "LevelScene.h"
#include "MyContactListener.h"

#include "ConstValue.h"

using namespace cocos2d;

enum Pole {
	BARRIER= 1,
	HOLE = 2
};
int GamePlayScene::level;

//------------------------------------------------------
GamePlayScene::~GamePlayScene() {
	if (world) {
		delete world;
		world = NULL;
	}
    if (body) {
		body = NULL;
	}
}

//------------------------------------------------------
GamePlayScene::GamePlayScene() :world(NULL) ,body(NULL) ,ball(NULL)
,ptmRatio(CCDirector::sharedDirector()->getWinSize().width / 10) {
}

//------------------------------------------------------
CCScene* GamePlayScene::scene() {
	return scene(0);
}

//------------------------------------------------------
CCScene* GamePlayScene::scene(int l) {
	level=l;
	CCScene *scene = CCScene::node();
	GamePlayScene *layer = GamePlayScene::node();
	scene->addChild(layer);
	return scene;
}

//------------------------------------------------------
bool GamePlayScene::init() {
	if(!CCLayer::init()) {
		return false;
	}
	b2Vec2 gravity = b2Vec2(0.0, 0.0);
	world = new b2World(gravity);
	this->setIsKeypadEnabled(true);
    this->setIsAccelerometerEnabled(true);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float width = winSize.width;
    float height = winSize.height;
    float ratiox= width/ConstValue::imageWidth;
    float ratioy= height/ConstValue::imageHeight;
    CCSprite* pSprite = CCSprite::spriteWithFile("grass.png");
    pSprite->setPosition( ccp(width/2.0, height/2.0) );
    pSprite->setScaleX(width/ConstValue::imageWidth);
    pSprite->setScaleY(height/ConstValue::imageHeight);
    this->addChild(pSprite, 0);
    //borderTop
	CCSprite *borderTop = CCSprite::spriteWithFile("bordertop.png");
	borderTop->setScaleX(ratiox);
	borderTop->setScaleY(ratioy);
	borderTop->setPosition(ccp(width/2, height-(15.0*ratioy)));
	borderTop->setTag(BARRIER);
	addChild(borderTop);
	b2BodyDef borderTopBodyDef;
	borderTopBodyDef.type = b2_staticBody;
	borderTopBodyDef.position.Set(borderTop->getPosition().x/ptmRatio, borderTop->getPosition().y/ptmRatio);
	borderTopBodyDef.userData = borderTop;
	body = world->CreateBody(&borderTopBodyDef);
	CCSize borderTopSize = borderTop->getTextureRect().size;
	b2PolygonShape borderTopPolygon;
	borderTopPolygon.SetAsBox(((borderTopSize.width)/2*ratiox)/ptmRatio, ((borderTopSize.height)/2*ratioy)/ ptmRatio);
	b2FixtureDef borderTopShapeDef;
	borderTopShapeDef.shape = &borderTopPolygon;
	borderTopShapeDef.density = 1.0f;
	borderTopShapeDef.friction = 0.2f;
	borderTopShapeDef.restitution = 0.4f;
	body->CreateFixture(&borderTopShapeDef);
    //borderBottom
    CCSprite *borderBottom = CCSprite::spriteWithFile("borderbottom.png");
    borderBottom->setScaleX(ratiox);
    borderBottom->setScaleY(ratioy);
    borderBottom->setPosition(ccp(width/2, 15.0*ratioy));
    borderBottom->setTag(BARRIER);
	addChild(borderBottom);
    b2BodyDef borderBottomBodyDef;
    borderBottomBodyDef.type = b2_staticBody;
    borderBottomBodyDef.position.Set(borderBottom->getPosition().x/ptmRatio, borderBottom->getPosition().y/ptmRatio);
    borderBottomBodyDef.userData = borderBottom;
    body = world->CreateBody(&borderBottomBodyDef);
    CCSize borderBottomSize = borderBottom->getTextureRect().size;
    b2PolygonShape borderBottomPolygon;
    borderBottomPolygon.SetAsBox(((borderBottomSize.width)/2*ratiox)/ptmRatio, ((borderBottomSize.height)/2*ratioy)/ ptmRatio);
    b2FixtureDef borderBottomShapeDef;
    borderBottomShapeDef.shape = &borderBottomPolygon;
    borderBottomShapeDef.density = 1.0f;
    borderBottomShapeDef.friction = 0.2f;
    borderBottomShapeDef.restitution = 0.4f;
    body->CreateFixture(&borderBottomShapeDef);
    //borderLeft
	CCSprite *borderLeft = CCSprite::spriteWithFile("borderleft.png");
	borderLeft->setScaleX(ratiox);
	borderLeft->setScaleY(ratioy);
	borderLeft->setPosition(ccp(15.0*ratiox, height/2));
	borderLeft->setTag(BARRIER);
	addChild(borderLeft);
	b2BodyDef borderLeftBodyDef;
	borderLeftBodyDef.type = b2_staticBody;
	borderLeftBodyDef.position.Set(borderLeft->getPosition().x/ptmRatio, borderLeft->getPosition().y/ptmRatio);
	borderLeftBodyDef.userData = borderLeft;
	body = world->CreateBody(&borderLeftBodyDef);
	CCSize borderLeftSize = borderLeft->getTextureRect().size;
	b2PolygonShape borderLeftPolygon;
	borderLeftPolygon.SetAsBox(((borderLeftSize.width)/2*ratiox)/ptmRatio, ((borderLeftSize.height)/2*ratioy)/ ptmRatio);
	b2FixtureDef borderLeftShapeDef;
	borderLeftShapeDef.shape = &borderLeftPolygon;
	borderLeftShapeDef.density = 1.0f;
	borderLeftShapeDef.friction = 0.2f;
	borderLeftShapeDef.restitution = 0.4f;
	body->CreateFixture(&borderLeftShapeDef);
	//borderRight
	CCSprite *borderRight = CCSprite::spriteWithFile("borderright.png");
	borderRight->setScaleX(ratiox);
	borderRight->setScaleY(ratioy);
	borderRight->setPosition(ccp(width-(15.0*ratiox), height/2));
	borderRight->setTag(BARRIER);
	addChild(borderRight);
	b2BodyDef borderRightBodyDef;
	borderRightBodyDef.type = b2_staticBody;
	borderRightBodyDef.position.Set(borderRight->getPosition().x/ptmRatio, borderRight->getPosition().y/ptmRatio);
	borderRightBodyDef.userData = borderRight;
	body = world->CreateBody(&borderRightBodyDef);
	CCSize borderRightSize = borderRight->getTextureRect().size;
	b2PolygonShape borderRightPolygon;
	borderRightPolygon.SetAsBox(((borderRightSize.width)/2*ratiox)/ptmRatio, ((borderRightSize.height)/2*ratioy)/ ptmRatio);
	b2FixtureDef borderRightShapeDef;
	borderRightShapeDef.shape = &borderRightPolygon;
	borderRightShapeDef.density = 1.0f;
	borderRightShapeDef.friction = 0.2f;
	borderRightShapeDef.restitution = 0.4f;
	body->CreateFixture(&borderRightShapeDef);
	CCSize ballSize, holeSize, barrierLevel2_1_Size, barrierLevel3_1_Size, barrierLevel3_2_Size;
	CCSize barrierLevel4_1_Size, barrierLevel4_2_Size, barrierLevel4_3_Size, barrierLevel4_4_Size;
	CCSize barrierLevel5_1_Size, barrierLevel5_2_Size, barrierLevel5_3_Size;
	CCSize barrierLevel6_1_Size;
	b2BodyDef ballBodyDef, holeBodyDef, barrierLevel2_1_BodyDef, barrierLevel3_1_BodyDef, barrierLevel3_2_BodyDef, pondSmallBodyDef,pondLargeBodyDef;
	b2BodyDef barrierLevel4_1_BodyDef, barrierLevel4_2_BodyDef, barrierLevel4_3_BodyDef, barrierLevel4_4_BodyDef;
	b2BodyDef barrierLevel5_1_BodyDef, barrierLevel5_2_BodyDef, barrierLevel5_3_BodyDef;
	b2BodyDef barrierLevel6_1_BodyDef;
	CCPoint ballPos, holePos, pondSmallPos,pondLargePos;
	b2CircleShape circle;
	b2FixtureDef ballShapeDef, holeShapeDef, pondSShapeDef,pondLShapeDef;
	CCSprite *barrierLevel2_1_, *barrierLevel3_1_, *barrierLevel3_2_;
	CCSprite *barrierLevel4_1_, *barrierLevel4_2_, *barrierLevel4_3_, *barrierLevel4_4_;
	CCSprite *barrierLevel5_1_, *barrierLevel5_2_, *barrierLevel5_3_;
	CCSprite *barrierLevel6_1_;
	b2PolygonShape barrierLevel2_1_Polygon, barrierLevel3_1_Polygon, barrierLevel3_2_Polygon;
	b2PolygonShape barrierLevel4_1_Polygon, barrierLevel4_2_Polygon, barrierLevel4_3_Polygon, barrierLevel4_4_Polygon;
	b2PolygonShape barrierLevel5_1_Polygon, barrierLevel5_2_Polygon, barrierLevel5_3_Polygon;
	b2PolygonShape barrierLevel6_1_Polygon;
	b2FixtureDef barrierLevel2_1_ShapeDef, barrierLevel3_1_ShapeDef, barrierLevel3_2_ShapeDef;
	b2FixtureDef barrierLevel4_1_ShapeDef, barrierLevel4_2_ShapeDef, barrierLevel4_3_ShapeDef, barrierLevel4_4_ShapeDef;
	b2FixtureDef barrierLevel5_1_ShapeDef, barrierLevel5_2_ShapeDef, barrierLevel5_3_ShapeDef;
	b2FixtureDef barrierLevel6_1_ShapeDef;
	switch(level)
	{
	case 1:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(50*ratiox)-(ballSize.width/2), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width /2, winSize.height / 2));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		// pond
		pondSmall = CCSprite::spriteWithFile("pondSmall.png");
		pondSmall->setPosition(ccp(winSize.width /2, winSize.height / 2 - 100.0*ratioy));
		pondSmall->setScale(ratioy);
		pondSmall->setTag(BARRIER);
		this->addChild(pondSmall, 1);
		pondSmallBodyDef.type = b2_staticBody;
		pondSmallPos = pondSmall->getPosition();
		pondSmallBodyDef.position.Set((pondSmallPos.x)/ptmRatio, (pondSmallPos.y)/ptmRatio);
		pondSmallBodyDef.userData = pondSmall;
		body = world->CreateBody(&pondSmallBodyDef);
		circle.m_radius = (pondSmall->getTexture()->getContentSize().width*ratioy)/2 / ptmRatio;
		pondSShapeDef.shape = &circle;
		pondSShapeDef.density = 0.6f;
		pondSShapeDef.friction = 0.2f;
		pondSShapeDef.restitution = 0.2f;
		_pondSFixture =  body->CreateFixture(&pondSShapeDef);
		break;
	case 2:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width /2, 150.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		// pond LArge
		pondLarge = CCSprite::spriteWithFile("pondLarge.png");
		pondLarge->setPosition(ccp(winSize.width /2, winSize.height / 2 + 100*ratioy));
		pondLarge->setScale(ratioy);
		pondLarge->setTag(BARRIER);
		this->addChild(pondLarge, 1);
		pondLargeBodyDef.type = b2_staticBody;
		pondLargePos = pondLarge->getPosition();
		pondLargeBodyDef.position.Set((pondLargePos.x)/ptmRatio, (pondLargePos.y)/ptmRatio);
		pondLargeBodyDef.userData = pondLarge;
		body = world->CreateBody(&pondLargeBodyDef);
		circle.m_radius = (pondLarge->getTexture()->getContentSize().width*ratioy) / 2 / ptmRatio;
		pondLShapeDef.shape = &circle;
		pondLShapeDef.density = 0.6f;
		pondLShapeDef.friction = 0.2f;
		pondLShapeDef.restitution = 0.2f;
		_pondLFixture =  body->CreateFixture(&pondLShapeDef);
		 //barrier_level2
		barrierLevel2_1_ = CCSprite::spriteWithFile("barrier_level2.png");
		barrierLevel2_1_->setScaleX(ratiox);
		barrierLevel2_1_->setScaleY(ratioy);
		barrierLevel2_1_->setPosition(ccp(width/2, height/2));
		barrierLevel2_1_->setTag(BARRIER);
		addChild(barrierLevel2_1_);
		barrierLevel2_1_BodyDef.type = b2_staticBody;
		barrierLevel2_1_BodyDef.position.Set(barrierLevel2_1_->getPosition().x/ptmRatio, barrierLevel2_1_->getPosition().y/ptmRatio);
		barrierLevel2_1_BodyDef.userData = barrierLevel2_1_;
		body = world->CreateBody(&barrierLevel2_1_BodyDef);
		barrierLevel2_1_Size = barrierLevel2_1_->getTextureRect().size;
		barrierLevel2_1_Polygon.SetAsBox(((barrierLevel2_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel2_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel2_1_ShapeDef.shape = &barrierLevel2_1_Polygon;
		barrierLevel2_1_ShapeDef.density = 1.0f;
		barrierLevel2_1_ShapeDef.friction = 0.2f;
		barrierLevel2_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel2_1_ShapeDef);
		break;
	case 3:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2)-(100.0*ratiox), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width/2-(150.0*ratiox), 150.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		// pond
		pondSmall = CCSprite::spriteWithFile("pondSmall.png");
		pondSmall->setPosition(ccp(winSize.width/2-(150.0*ratiox), 80.0*ratioy));
		pondSmall->setScale(ratioy);
		pondSmall->setTag(BARRIER);
		this->addChild(pondSmall, 1);
		pondSmallBodyDef.type = b2_staticBody;
		pondSmallPos = pondSmall->getPosition();
		pondSmallBodyDef.position.Set((pondSmallPos.x)/ptmRatio, (pondSmallPos.y)/ptmRatio);
		pondSmallBodyDef.userData = pondSmall;
		body = world->CreateBody(&pondSmallBodyDef);
		circle.m_radius = pondSmall->getTexture()->getContentSize().width / 2 / ptmRatio;
		pondSShapeDef.shape = &circle;
		pondSShapeDef.density = 0.6f;
		pondSShapeDef.friction = 0.2f;
		pondSShapeDef.restitution = 0.2f;
		_pondSFixture =  body->CreateFixture(&pondSShapeDef);
		// pond LArge
		pondLarge = CCSprite::spriteWithFile("pondLarge.png");
		pondLarge->setPosition(ccp(winSize.width /2 + 100.0*ratiox, winSize.height / 2 + 200.0*ratioy));
		pondLarge->setScale(ratioy);
		pondLarge->setTag(BARRIER);
		this->addChild(pondLarge, 1);
		pondLargeBodyDef.type = b2_staticBody;
		pondLargePos = pondLarge->getPosition();
		pondLargeBodyDef.position.Set((pondLargePos.x)/ptmRatio, (pondLargePos.y)/ptmRatio);
		pondLargeBodyDef.userData = pondLarge;
		body = world->CreateBody(&pondLargeBodyDef);
		circle.m_radius = (pondLarge->getTexture()->getContentSize().width*ratiox) / 2 / ptmRatio;
		pondLShapeDef.shape = &circle;
		pondLShapeDef.density = 0.6f;
		pondLShapeDef.friction = 0.2f;
		pondLShapeDef.restitution = 0.2f;
		_pondLFixture =  body->CreateFixture(&pondLShapeDef);
		//barrier_level3_1
		barrierLevel3_1_ = CCSprite::spriteWithFile("barrier_level3.png");
		barrierLevel3_1_Size = barrierLevel3_1_->getTextureRect().size;
		barrierLevel3_1_->setScaleX(ratiox);
		barrierLevel3_1_->setScaleY(ratioy);
		barrierLevel3_1_->setPosition(ccp((barrierLevel3_1_Size.width/2*ratiox)+(25.0*ratiox), height/2+25.0*ratioy));
		barrierLevel3_1_->setTag(BARRIER);
		addChild(barrierLevel3_1_);
		barrierLevel3_1_BodyDef.type = b2_staticBody;
		barrierLevel3_1_BodyDef.position.Set(barrierLevel3_1_->getPosition().x/ptmRatio, barrierLevel3_1_->getPosition().y/ptmRatio);
		barrierLevel3_1_BodyDef.userData = barrierLevel3_1_;
		body = world->CreateBody(&barrierLevel3_1_BodyDef);
		barrierLevel3_1_Polygon.SetAsBox(((barrierLevel3_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel3_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel3_1_ShapeDef.shape = &barrierLevel3_1_Polygon;
		barrierLevel3_1_ShapeDef.density = 1.0f;
		barrierLevel3_1_ShapeDef.friction = 0.2f;
		barrierLevel3_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel3_1_ShapeDef);
		//barrier_level3_2
		barrierLevel3_2_ = CCSprite::spriteWithFile("barrier_level3.png");
		barrierLevel3_2_Size = barrierLevel3_2_->getTextureRect().size;
		barrierLevel3_2_->setScaleX(ratiox);
		barrierLevel3_2_->setScaleY(ratioy);
		barrierLevel3_2_->setPosition(ccp(width-((barrierLevel3_2_Size.width/2*ratiox)+(25.0*ratiox)), height/2-25.0*ratioy));
		barrierLevel3_2_->setTag(BARRIER);
		addChild(barrierLevel3_2_);
		barrierLevel3_2_BodyDef.type = b2_staticBody;
		barrierLevel3_2_BodyDef.position.Set(barrierLevel3_2_->getPosition().x/ptmRatio, barrierLevel3_2_->getPosition().y/ptmRatio);
		barrierLevel3_2_BodyDef.userData = barrierLevel3_2_;
		body = world->CreateBody(&barrierLevel3_2_BodyDef);
		barrierLevel3_2_Polygon.SetAsBox(((barrierLevel3_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel3_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel3_2_ShapeDef.shape = &barrierLevel3_2_Polygon;
		barrierLevel3_2_ShapeDef.density = 1.0f;
		barrierLevel3_2_ShapeDef.friction = 0.2f;
		barrierLevel3_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel3_2_ShapeDef);
		break;
	case 4:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2)+(100.0*ratiox), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width/2-(150.0*ratiox), 100.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		//barrier_Level4_1
		barrierLevel4_1_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_1_Size = barrierLevel4_1_->getTextureRect().size;
		barrierLevel4_1_->setScaleX(ratiox);
		barrierLevel4_1_->setScaleY(ratioy);
		barrierLevel4_1_->setPosition(ccp(width-(barrierLevel4_1_Size.width/2*ratiox)-(25.0*ratiox), height/2+125.0*ratioy));
		barrierLevel4_1_->setTag(BARRIER);
		addChild(barrierLevel4_1_);
		barrierLevel4_1_BodyDef.type = b2_staticBody;
		barrierLevel4_1_BodyDef.position.Set(barrierLevel4_1_->getPosition().x/ptmRatio, barrierLevel4_1_->getPosition().y/ptmRatio);
		barrierLevel4_1_BodyDef.userData = barrierLevel4_1_;
		body = world->CreateBody(&barrierLevel4_1_BodyDef);
		barrierLevel4_1_Polygon.SetAsBox(((barrierLevel4_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_1_ShapeDef.shape = &barrierLevel4_1_Polygon;
		barrierLevel4_1_ShapeDef.density = 1.0f;
		barrierLevel4_1_ShapeDef.friction = 0.2f;
		barrierLevel4_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_1_ShapeDef);
		//barrier_Level4_2
		barrierLevel4_2_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_2_Size = barrierLevel4_2_->getTextureRect().size;
		barrierLevel4_2_->setScaleX(ratiox);
		barrierLevel4_2_->setScaleY(ratioy);
		barrierLevel4_2_->setPosition(ccp(((barrierLevel4_2_Size.width/2*ratiox)+(25.0*ratiox)), height/2+75.0*ratioy));
		barrierLevel4_2_->setTag(BARRIER);
		addChild(barrierLevel4_2_);
		barrierLevel4_2_BodyDef.type = b2_staticBody;
		barrierLevel4_2_BodyDef.position.Set(barrierLevel4_2_->getPosition().x/ptmRatio, barrierLevel4_2_->getPosition().y/ptmRatio);
		barrierLevel4_2_BodyDef.userData = barrierLevel4_2_;
		body = world->CreateBody(&barrierLevel4_2_BodyDef);
		barrierLevel4_2_Polygon.SetAsBox(((barrierLevel4_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_2_ShapeDef.shape = &barrierLevel4_2_Polygon;
		barrierLevel4_2_ShapeDef.density = 1.0f;
		barrierLevel4_2_ShapeDef.friction = 0.2f;
		barrierLevel4_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_2_ShapeDef);
		//barrier_Level4_3
		barrierLevel4_3_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_3_Size = barrierLevel4_3_->getTextureRect().size;
		barrierLevel4_3_->setScaleX(ratiox);
		barrierLevel4_3_->setScaleY(ratioy);
		barrierLevel4_3_->setPosition(ccp((width-(barrierLevel4_3_Size.width/2*ratiox)-(25.0*ratiox)), height/2-75.0*ratioy));
		barrierLevel4_3_->setTag(BARRIER);
		addChild(barrierLevel4_3_);
		barrierLevel4_3_BodyDef.type = b2_staticBody;
		barrierLevel4_3_BodyDef.position.Set(barrierLevel4_3_->getPosition().x/ptmRatio, barrierLevel4_3_->getPosition().y/ptmRatio);
		barrierLevel4_3_BodyDef.userData = barrierLevel4_3_;
		body = world->CreateBody(&barrierLevel4_3_BodyDef);
		barrierLevel4_3_Polygon.SetAsBox(((barrierLevel4_3_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_3_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_3_ShapeDef.shape = &barrierLevel4_3_Polygon;
		barrierLevel4_3_ShapeDef.density = 1.0f;
		barrierLevel4_3_ShapeDef.friction = 0.2f;
		barrierLevel4_3_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_3_ShapeDef);
		//barrier_Level4_4
		barrierLevel4_4_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_4_Size = barrierLevel4_4_->getTextureRect().size;
		barrierLevel4_4_->setScaleX(ratiox);
		barrierLevel4_4_->setScaleY(ratioy);
		barrierLevel4_4_->setPosition(ccp(((barrierLevel4_4_Size.width/2*ratiox)+(25.0*ratiox)), height/2-125.0*ratioy));
		barrierLevel4_4_->setTag(BARRIER);
		addChild(barrierLevel4_4_);
		barrierLevel4_4_BodyDef.type = b2_staticBody;
		barrierLevel4_4_BodyDef.position.Set(barrierLevel4_4_->getPosition().x/ptmRatio, barrierLevel4_4_->getPosition().y/ptmRatio);
		barrierLevel4_4_BodyDef.userData = barrierLevel4_4_;
		body = world->CreateBody(&barrierLevel4_4_BodyDef);
		barrierLevel4_4_Polygon.SetAsBox(((barrierLevel4_4_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_4_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_4_ShapeDef.shape = &barrierLevel4_4_Polygon;
		barrierLevel4_4_ShapeDef.density = 1.0f;
		barrierLevel4_4_ShapeDef.friction = 0.2f;
		barrierLevel4_4_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_4_ShapeDef);
		break;
	case 5:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width/2, 250.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		// pond
		pondSmall = CCSprite::spriteWithFile("pondSmall.png");
		pondSmall->setPosition(ccp(winSize.width/2, 310.0*ratioy));
		pondSmall->setScale(ratioy);
		pondSmall->setTag(BARRIER);
		this->addChild(pondSmall, 1);
		pondSmallBodyDef.type = b2_staticBody;
		pondSmallPos = pondSmall->getPosition();
		pondSmallBodyDef.position.Set((pondSmallPos.x)/ptmRatio, (pondSmallPos.y)/ptmRatio);
		pondSmallBodyDef.userData = pondSmall;
		body = world->CreateBody(&pondSmallBodyDef);
		circle.m_radius = (pondSmall->getTexture()->getContentSize().width*ratioy) / 2 / ptmRatio;
		pondSShapeDef.shape = &circle;
		pondSShapeDef.density = 0.6f;
		pondSShapeDef.friction = 0.2f;
		pondSShapeDef.restitution = 0.2f;
		_pondSFixture =  body->CreateFixture(&pondSShapeDef);
		//barrier_Level5_1
		barrierLevel5_1_ = CCSprite::spriteWithFile("barrier_level5_1.png");
		barrierLevel5_1_Size = barrierLevel5_1_->getTextureRect().size;
		barrierLevel5_1_->setScaleX(ratiox);
		barrierLevel5_1_->setScaleY(ratioy);
		barrierLevel5_1_->setPosition(ccp((width/2-125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_1_->setTag(BARRIER);
		addChild(barrierLevel5_1_);
		barrierLevel5_1_BodyDef.type = b2_staticBody;
		barrierLevel5_1_BodyDef.position.Set(barrierLevel5_1_->getPosition().x/ptmRatio, barrierLevel5_1_->getPosition().y/ptmRatio);
		barrierLevel5_1_BodyDef.userData = barrierLevel5_1_;
		body = world->CreateBody(&barrierLevel5_1_BodyDef);
		barrierLevel5_1_Polygon.SetAsBox(((barrierLevel5_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_1_ShapeDef.shape = &barrierLevel5_1_Polygon;
		barrierLevel5_1_ShapeDef.density = 1.0f;
		barrierLevel5_1_ShapeDef.friction = 0.2f;
		barrierLevel5_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_1_ShapeDef);
		//barrier_Level5_2
		barrierLevel5_2_ = CCSprite::spriteWithFile("barrier_level5_2.png");
		barrierLevel5_2_Size = barrierLevel5_2_->getTextureRect().size;
		barrierLevel5_2_->setScaleX(ratiox);
		barrierLevel5_2_->setScaleY(ratioy);
		barrierLevel5_2_->setPosition(ccp((width/2+125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_2_->setTag(BARRIER);
		addChild(barrierLevel5_2_);
		barrierLevel5_2_BodyDef.type = b2_staticBody;
		barrierLevel5_2_BodyDef.position.Set(barrierLevel5_2_->getPosition().x/ptmRatio, barrierLevel5_2_->getPosition().y/ptmRatio);
		barrierLevel5_2_BodyDef.userData = barrierLevel5_2_;
		body = world->CreateBody(&barrierLevel5_2_BodyDef);
		barrierLevel5_2_Polygon.SetAsBox(((barrierLevel5_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_2_ShapeDef.shape = &barrierLevel5_2_Polygon;
		barrierLevel5_2_ShapeDef.density = 1.0f;
		barrierLevel5_2_ShapeDef.friction = 0.2f;
		barrierLevel5_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_2_ShapeDef);
		//barrier_level5_3
		barrierLevel5_3_ = CCSprite::spriteWithFile("barrier_level5_3.png");
		barrierLevel5_3_->setScaleX(ratiox);
		barrierLevel5_3_->setScaleY(ratioy);
		barrierLevel5_3_->setPosition(ccp(width/2, height/2+(30.0*ratioy)));
		barrierLevel5_3_->setTag(BARRIER);
		addChild(barrierLevel5_3_);
		barrierLevel5_3_BodyDef.type = b2_staticBody;
		barrierLevel5_3_BodyDef.position.Set(barrierLevel5_3_->getPosition().x/ptmRatio, barrierLevel5_3_->getPosition().y/ptmRatio);
		barrierLevel5_3_BodyDef.userData = barrierLevel5_3_;
		body = world->CreateBody(&barrierLevel5_3_BodyDef);
		barrierLevel5_3_Size = barrierLevel5_3_->getTextureRect().size;
		barrierLevel5_3_Polygon.SetAsBox(((barrierLevel5_3_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_3_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_3_ShapeDef.shape = &barrierLevel5_3_Polygon;
		barrierLevel5_3_ShapeDef.density = 1.0f;
		barrierLevel5_3_ShapeDef.friction = 0.2f;
		barrierLevel5_3_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_3_ShapeDef);
		break;
	case 6:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width/2, 300.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);
		//barrier_Level5_1
		barrierLevel5_1_ = CCSprite::spriteWithFile("barrier_level5_1.png");
		barrierLevel5_1_Size = barrierLevel5_1_->getTextureRect().size;
		barrierLevel5_1_->setScaleX(ratiox);
		barrierLevel5_1_->setScaleY(ratioy);
		barrierLevel5_1_->setPosition(ccp((width/2-125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_1_->setTag(BARRIER);
		addChild(barrierLevel5_1_);
		barrierLevel5_1_BodyDef.type = b2_staticBody;
		barrierLevel5_1_BodyDef.position.Set(barrierLevel5_1_->getPosition().x/ptmRatio, barrierLevel5_1_->getPosition().y/ptmRatio);
		barrierLevel5_1_BodyDef.userData = barrierLevel5_1_;
		body = world->CreateBody(&barrierLevel5_1_BodyDef);
		barrierLevel5_1_Polygon.SetAsBox(((barrierLevel5_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_1_ShapeDef.shape = &barrierLevel5_1_Polygon;
		barrierLevel5_1_ShapeDef.density = 1.0f;
		barrierLevel5_1_ShapeDef.friction = 0.2f;
		barrierLevel5_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_1_ShapeDef);
		//barrier_Level5_2
		barrierLevel5_2_ = CCSprite::spriteWithFile("barrier_level5_2.png");
		barrierLevel5_2_Size = barrierLevel5_2_->getTextureRect().size;
		barrierLevel5_2_->setScaleX(ratiox);
		barrierLevel5_2_->setScaleY(ratioy);
		barrierLevel5_2_->setPosition(ccp((width/2+125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_2_->setTag(BARRIER);
		addChild(barrierLevel5_2_);
		barrierLevel5_2_BodyDef.type = b2_staticBody;
		barrierLevel5_2_BodyDef.position.Set(barrierLevel5_2_->getPosition().x/ptmRatio, barrierLevel5_2_->getPosition().y/ptmRatio);
		barrierLevel5_2_BodyDef.userData = barrierLevel5_2_;
		body = world->CreateBody(&barrierLevel5_2_BodyDef);
		barrierLevel5_2_Polygon.SetAsBox(((barrierLevel5_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_2_ShapeDef.shape = &barrierLevel5_2_Polygon;
		barrierLevel5_2_ShapeDef.density = 1.0f;
		barrierLevel5_2_ShapeDef.friction = 0.2f;
		barrierLevel5_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_2_ShapeDef);
		//barrier_level5_3
		barrierLevel5_3_ = CCSprite::spriteWithFile("barrier_level5_3.png");
		barrierLevel5_3_->setScaleX(ratiox);
		barrierLevel5_3_->setScaleY(ratioy);
		barrierLevel5_3_->setPosition(ccp(width/2, height/2+(30.0*ratioy)));
		barrierLevel5_3_->setTag(BARRIER);
		addChild(barrierLevel5_3_);
		barrierLevel5_3_BodyDef.type = b2_staticBody;
		barrierLevel5_3_BodyDef.position.Set(barrierLevel5_3_->getPosition().x/ptmRatio, barrierLevel5_3_->getPosition().y/ptmRatio);
		barrierLevel5_3_BodyDef.userData = barrierLevel5_3_;
		body = world->CreateBody(&barrierLevel5_3_BodyDef);
		barrierLevel5_3_Size = barrierLevel5_3_->getTextureRect().size;
		barrierLevel5_3_Polygon.SetAsBox(((barrierLevel5_3_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_3_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_3_ShapeDef.shape = &barrierLevel5_3_Polygon;
		barrierLevel5_3_ShapeDef.density = 1.0f;
		barrierLevel5_3_ShapeDef.friction = 0.2f;
		barrierLevel5_3_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_3_ShapeDef);
		//barrier_level6_1
		barrierLevel6_1_ = CCSprite::spriteWithFile("barrier_level6_1.png");
		barrierLevel6_1_->setScaleX(ratiox);
		barrierLevel6_1_->setScaleY(ratioy);
		barrierLevel6_1_->setPosition(ccp(width/2, height/2-(280.0*ratioy)));
		barrierLevel6_1_->setTag(BARRIER);
		addChild(barrierLevel6_1_);
		barrierLevel6_1_BodyDef.type = b2_staticBody;
		barrierLevel6_1_BodyDef.position.Set(barrierLevel6_1_->getPosition().x/ptmRatio, barrierLevel6_1_->getPosition().y/ptmRatio);
		barrierLevel6_1_BodyDef.userData = barrierLevel6_1_;
		body = world->CreateBody(&barrierLevel6_1_BodyDef);
		barrierLevel6_1_Size = barrierLevel6_1_->getTextureRect().size;
		barrierLevel6_1_Polygon.SetAsBox(((barrierLevel6_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel6_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel6_1_ShapeDef.shape = &barrierLevel6_1_Polygon;
		barrierLevel6_1_ShapeDef.density = 1.0f;
		barrierLevel6_1_ShapeDef.friction = 0.2f;
		barrierLevel6_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel6_1_ShapeDef);
		break;
	case 7:
		// ball
		ball = CCSprite::spriteWithFile("ball.png");
		ballSize = ball->getTextureRect().size;
		ball->setPosition(ccp(width/2-(ballSize.width/2), height-(20.0*ratioy)-(ballSize.height/2)));
		ball->setScale(height/ConstValue::imageHeight);
		this->addChild(ball, 2);
		ballBodyDef.type = b2_dynamicBody;
		ballPos = ball->getPosition();
		ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
		ballBodyDef.userData = ball;
		body = world->CreateBody(&ballBodyDef);
		circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 0.6f;
		ballShapeDef.friction = 0.2f;
		ballShapeDef.restitution = 0.2f;
		_ballFixture = body->CreateFixture(&ballShapeDef);
		// hole
		hole = CCSprite::spriteWithFile("hole.png");
		holeSize = hole->getTextureRect().size;
		hole->setPosition(ccp(winSize.width/2, 300.0*ratioy));
		hole->setScale(height/ConstValue::imageHeight);
		hole->setTag(HOLE);
		this->addChild(hole, 1);
		holeBodyDef.type = b2_staticBody;
		holePos = hole->getPosition();
		holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
		holeBodyDef.userData = hole;
		body = world->CreateBody(&holeBodyDef);
		circle.m_radius = 0.1/ ptmRatio;
		holeShapeDef.shape = &circle;
		holeShapeDef.density = 0.6f;
		holeShapeDef.friction = 0.2f;
		holeShapeDef.restitution = 0.2f;
		_holeFixture =  body->CreateFixture(&holeShapeDef);


		//barrier_Level4_1
		barrierLevel4_1_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_1_Size = barrierLevel4_1_->getTextureRect().size;
		barrierLevel4_1_->setScaleX(ratiox);
		barrierLevel4_1_->setScaleY(ratioy);
		barrierLevel4_1_->setPosition(ccp(width-(barrierLevel4_1_Size.width/2*ratiox)-(25.0*ratiox), height/2+125.0*ratioy));
		barrierLevel4_1_->setTag(BARRIER);
		addChild(barrierLevel4_1_);
		barrierLevel4_1_BodyDef.type = b2_staticBody;
		barrierLevel4_1_BodyDef.position.Set(barrierLevel4_1_->getPosition().x/ptmRatio, barrierLevel4_1_->getPosition().y/ptmRatio);
		barrierLevel4_1_BodyDef.userData = barrierLevel4_1_;
		body = world->CreateBody(&barrierLevel4_1_BodyDef);
		barrierLevel4_1_Polygon.SetAsBox(((barrierLevel4_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_1_ShapeDef.shape = &barrierLevel4_1_Polygon;
		barrierLevel4_1_ShapeDef.density = 1.0f;
		barrierLevel4_1_ShapeDef.friction = 0.2f;
		barrierLevel4_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_1_ShapeDef);
		//barrier_Level4_2
		barrierLevel4_2_ = CCSprite::spriteWithFile("barrier_level4.png");
		barrierLevel4_2_Size = barrierLevel4_2_->getTextureRect().size;
		barrierLevel4_2_->setScaleX(ratiox);
		barrierLevel4_2_->setScaleY(ratioy);
		barrierLevel4_2_->setPosition(ccp(((barrierLevel4_2_Size.width/2*ratiox)+(25.0*ratiox)), height/2+75.0*ratioy));
		barrierLevel4_2_->setTag(BARRIER);
		addChild(barrierLevel4_2_);
		barrierLevel4_2_BodyDef.type = b2_staticBody;
		barrierLevel4_2_BodyDef.position.Set(barrierLevel4_2_->getPosition().x/ptmRatio, barrierLevel4_2_->getPosition().y/ptmRatio);
		barrierLevel4_2_BodyDef.userData = barrierLevel4_2_;
		body = world->CreateBody(&barrierLevel4_2_BodyDef);
		barrierLevel4_2_Polygon.SetAsBox(((barrierLevel4_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel4_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel4_2_ShapeDef.shape = &barrierLevel4_2_Polygon;
		barrierLevel4_2_ShapeDef.density = 1.0f;
		barrierLevel4_2_ShapeDef.friction = 0.2f;
		barrierLevel4_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel4_2_ShapeDef);
		//barrier_Level5_1
		barrierLevel5_1_ = CCSprite::spriteWithFile("barrier_level5_1.png");
		barrierLevel5_1_Size = barrierLevel5_1_->getTextureRect().size;
		barrierLevel5_1_->setScaleX(ratiox);
		barrierLevel5_1_->setScaleY(ratioy);
		barrierLevel5_1_->setPosition(ccp((width/2-125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_1_->setTag(BARRIER);
		addChild(barrierLevel5_1_);
		barrierLevel5_1_BodyDef.type = b2_staticBody;
		barrierLevel5_1_BodyDef.position.Set(barrierLevel5_1_->getPosition().x/ptmRatio, barrierLevel5_1_->getPosition().y/ptmRatio);
		barrierLevel5_1_BodyDef.userData = barrierLevel5_1_;
		body = world->CreateBody(&barrierLevel5_1_BodyDef);
		barrierLevel5_1_Polygon.SetAsBox(((barrierLevel5_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_1_ShapeDef.shape = &barrierLevel5_1_Polygon;
		barrierLevel5_1_ShapeDef.density = 1.0f;
		barrierLevel5_1_ShapeDef.friction = 0.2f;
		barrierLevel5_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_1_ShapeDef);
		//barrier_Level5_2
		barrierLevel5_2_ = CCSprite::spriteWithFile("barrier_level5_2.png");
		barrierLevel5_2_Size = barrierLevel5_2_->getTextureRect().size;
		barrierLevel5_2_->setScaleX(ratiox);
		barrierLevel5_2_->setScaleY(ratioy);
		barrierLevel5_2_->setPosition(ccp((width/2+125.0*ratiox), height/2-125.0*ratioy));
		barrierLevel5_2_->setTag(BARRIER);
		addChild(barrierLevel5_2_);
		barrierLevel5_2_BodyDef.type = b2_staticBody;
		barrierLevel5_2_BodyDef.position.Set(barrierLevel5_2_->getPosition().x/ptmRatio, barrierLevel5_2_->getPosition().y/ptmRatio);
		barrierLevel5_2_BodyDef.userData = barrierLevel5_2_;
		body = world->CreateBody(&barrierLevel5_2_BodyDef);
		barrierLevel5_2_Polygon.SetAsBox(((barrierLevel5_2_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_2_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_2_ShapeDef.shape = &barrierLevel5_2_Polygon;
		barrierLevel5_2_ShapeDef.density = 1.0f;
		barrierLevel5_2_ShapeDef.friction = 0.2f;
		barrierLevel5_2_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_2_ShapeDef);
		//barrier_level5_3
		barrierLevel5_3_ = CCSprite::spriteWithFile("barrier_level5_3.png");
		barrierLevel5_3_->setScaleX(ratiox);
		barrierLevel5_3_->setScaleY(ratioy);
		barrierLevel5_3_->setPosition(ccp(width/2, height/2+(30.0*ratioy)));
		barrierLevel5_3_->setTag(BARRIER);
		addChild(barrierLevel5_3_);
		barrierLevel5_3_BodyDef.type = b2_staticBody;
		barrierLevel5_3_BodyDef.position.Set(barrierLevel5_3_->getPosition().x/ptmRatio, barrierLevel5_3_->getPosition().y/ptmRatio);
		barrierLevel5_3_BodyDef.userData = barrierLevel5_3_;
		body = world->CreateBody(&barrierLevel5_3_BodyDef);
		barrierLevel5_3_Size = barrierLevel5_3_->getTextureRect().size;
		barrierLevel5_3_Polygon.SetAsBox(((barrierLevel5_3_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel5_3_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel5_3_ShapeDef.shape = &barrierLevel5_3_Polygon;
		barrierLevel5_3_ShapeDef.density = 1.0f;
		barrierLevel5_3_ShapeDef.friction = 0.2f;
		barrierLevel5_3_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel5_3_ShapeDef);
		//barrier_level6_1
		barrierLevel6_1_ = CCSprite::spriteWithFile("barrier_level6_1.png");
		barrierLevel6_1_->setScaleX(ratiox);
		barrierLevel6_1_->setScaleY(ratioy);
		barrierLevel6_1_->setPosition(ccp(width/2, height/2-(280.0*ratioy)));
		barrierLevel6_1_->setTag(BARRIER);
		addChild(barrierLevel6_1_);
		barrierLevel6_1_BodyDef.type = b2_staticBody;
		barrierLevel6_1_BodyDef.position.Set(barrierLevel6_1_->getPosition().x/ptmRatio, barrierLevel6_1_->getPosition().y/ptmRatio);
		barrierLevel6_1_BodyDef.userData = barrierLevel6_1_;
		body = world->CreateBody(&barrierLevel6_1_BodyDef);
		barrierLevel6_1_Size = barrierLevel6_1_->getTextureRect().size;
		barrierLevel6_1_Polygon.SetAsBox(((barrierLevel6_1_Size.width)/2*ratiox)/ptmRatio, ((barrierLevel6_1_Size.height)/2*ratioy)/ ptmRatio);
		barrierLevel6_1_ShapeDef.shape = &barrierLevel6_1_Polygon;
		barrierLevel6_1_ShapeDef.density = 1.0f;
		barrierLevel6_1_ShapeDef.friction = 0.2f;
		barrierLevel6_1_ShapeDef.restitution = 0.4f;
		body->CreateFixture(&barrierLevel6_1_ShapeDef);
		break;
	}
    contactListener = new MyContactListener();
    world->SetContactListener(contactListener);
    start=clock();
    this->schedule(schedule_selector(GamePlayScene::tick));
	return true;
}

void GamePlayScene::tick(cocos2d::ccTime delta) {
	bool blockFound = false;
	world->Step(delta, 10, 10);
	for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData();
	        sprite->setPosition(ccp(b->GetPosition().x * ptmRatio, b->GetPosition().y * ptmRatio));
	        sprite->setRotation(1.0 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	std::vector<MyContact>::iterator pos;
	for(pos = contactListener->_contacts.begin(); pos != contactListener->_contacts.end(); ++pos) {
		MyContact contact = *pos;
		if ((contact.fixtureA == _holeFixture && contact.fixtureB == _ballFixture) ||
			(contact.fixtureA == _ballFixture && contact.fixtureB == _holeFixture)) {
			stop=clock();
			CCScene* resultScene = ScoresLevelScene::scene(level,(stop-start)/(CLOCKS_PER_SEC*1.0),false);
			CCDirector::sharedDirector()->pushScene( resultScene );
		}else if ((contact.fixtureA == _pondSFixture && contact.fixtureB == _ballFixture) ||
				(contact.fixtureA == _ballFixture && contact.fixtureB == _pondSFixture)) {
				stop=clock();
				CCScene* resultScene = ScoresLevelScene::scene(level,(stop-start)/(CLOCKS_PER_SEC*1.0), true);
				CCDirector::sharedDirector()->pushScene( resultScene );
		}else if ((contact.fixtureA == _pondLFixture && contact.fixtureB == _ballFixture) ||
				(contact.fixtureA == _ballFixture && contact.fixtureB == _pondLFixture)) {
				stop=clock();
				CCScene* resultScene = ScoresLevelScene::scene(level,(stop-start)/(CLOCKS_PER_SEC*1.0), true);
				CCDirector::sharedDirector()->pushScene( resultScene );
		}

	}
}

void GamePlayScene::didAccelerate(CCAcceleration* pAccelerationValue) {
    b2Vec2 gravity(pAccelerationValue->x * 10, pAccelerationValue->y * 10);
    world->SetGravity(gravity);
}

void GamePlayScene::keyBackClicked() {
	CCScene* levelScene = LevelScene::scene();
	CCDirector::sharedDirector()->pushScene( levelScene );
}
