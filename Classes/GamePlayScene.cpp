#include "GamePlayScene.h"
#include "MyContactListener.h"

#include "ConstValue.h"

using namespace cocos2d;

enum Pole {
	BARRIER= 1,
	HOLE = 2
};

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
    // ball
    ball = CCSprite::spriteWithFile("ball.png");
    CCSize ballSize = ball->getTextureRect().size;
    ball->setPosition(ccp(width/2-(ballSize.width/2), height-(ballSize.height/2)));
    ball->setScale(height/ConstValue::imageHeight);
    this->addChild(ball, 2);
    b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	CCPoint ballPos = ball->getPosition();
	ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
	ballBodyDef.userData = ball;
	body = world->CreateBody(&ballBodyDef);
	b2CircleShape circle;
	circle.m_radius = ((((ballSize.width-4.0)*ratiox)/2.0))/ ptmRatio;
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 0.6f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.2f;
	_ballFixture = body->CreateFixture(&ballShapeDef);
    // hole
    hole = CCSprite::spriteWithFile("hole.png");
    CCSize holeSize = hole->getTextureRect().size;
    hole->setPosition(ccp(winSize.width /2, winSize.height / 2));
    hole->setScale(height/ConstValue::imageHeight);
    hole->setTag(HOLE);
    this->addChild(hole, 1);
    b2BodyDef holeBodyDef;
    holeBodyDef.type = b2_staticBody;
    CCPoint holePos = hole->getPosition();
    holeBodyDef.position.Set((holePos.x)/ptmRatio, (holePos.y)/ptmRatio);
    holeBodyDef.userData = hole;
    body = world->CreateBody(&holeBodyDef);
    circle.m_radius = 0.1/ ptmRatio;
    b2FixtureDef holeShapeDef;
    holeShapeDef.shape = &circle;
    holeShapeDef.density = 0.6f;
    holeShapeDef.friction = 0.2f;
    holeShapeDef.restitution = 0.2f;
    _holeFixture =  body->CreateFixture(&holeShapeDef);
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
    contactListener = new MyContactListener();
    world->SetContactListener(contactListener);
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
			CCDirector::sharedDirector()->popScene();
		}
	}
}

void GamePlayScene::didAccelerate(CCAcceleration* pAccelerationValue) {
    b2Vec2 gravity(pAccelerationValue->x * 10, pAccelerationValue->y * 10);
    world->SetGravity(gravity);
}

void GamePlayScene::keyBackClicked() {
	CCDirector::sharedDirector()->popScene();
}
