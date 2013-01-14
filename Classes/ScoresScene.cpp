#include "ScoresScene.h"
#include "MiniGolfData.h"

#include "ConstValue.h"

using namespace cocos2d;

//------------------------------------------------------
CCScene* ScoresScene::scene() {
    CCScene *scene = CCScene::node();
    ScoresScene *layer = ScoresScene::node();
    scene->addChild(layer);
    return scene;
}

//------------------------------------------------------
bool ScoresScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled( true );
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    //background "scoresscene.png"
	CCSprite* pSprite = CCSprite::spriteWithFile("scoresscene.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	//button"back"
	CCMenuItemImage* backButton = CCMenuItemImage::itemFromNormalImage( "back.png", "back_s.png", this,
			menu_selector(ScoresScene::keyBackClicked));
	backButton->setPosition(ccp(width/2, 56.0*(height/ConstValue::imageHeight)));
	backButton->setScaleX(width/ConstValue::imageWidth);
	backButton->setScaleY(height/ConstValue::imageHeight);
	CCMenu* pMenu = CCMenu::menuWithItems(backButton, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
	double bestTimes[7];
	double lastTimes[7];
	for(int i=0; i<7; i++) {
		bestTimes[i]=MiniGolfData::getBestScore(i);
		lastTimes[i]=MiniGolfData::getLastScore(i);
	}
	CCLabelTTF* bestTimesLabel[7];
	CCLabelTTF* lastTimesLabel[7];
	for(int i=0; i<7; i++) {
		if(bestTimes[i]<0) {
			bestTimesLabel[i] = CCLabelTTF::labelWithString("-", "Arial", 28*height/ConstValue::imageHeight);
			bestTimesLabel[i]->setPosition( ccp(255*(width/ConstValue::imageWidth), (467.0-(i*57.0))*(height/ConstValue::imageHeight)) );
			this->addChild(bestTimesLabel[i], 1);
			lastTimesLabel[i] = CCLabelTTF::labelWithString("-", "Arial", 28*height/ConstValue::imageHeight);
			lastTimesLabel[i]->setPosition( ccp(365*(width/ConstValue::imageWidth), (467.0-(i*57.0))*(height/ConstValue::imageHeight)) );
			this->addChild(lastTimesLabel[i], 1);
		} else {
			char bestS[128];
			sprintf(bestS,"%0.2f",bestTimes[i]);
			char lastS[128];
			sprintf(lastS,"%0.2f",lastTimes[i]);
			bestTimesLabel[i] = CCLabelTTF::labelWithString(bestS, "Arial", 28*height/ConstValue::imageHeight);
			bestTimesLabel[i]->setPosition( ccp(255*(width/ConstValue::imageWidth), (467.0-(i*57.0))*(height/ConstValue::imageHeight)) );
			this->addChild(bestTimesLabel[i], 1);
			lastTimesLabel[i] = CCLabelTTF::labelWithString(lastS, "Arial", 28*height/ConstValue::imageHeight);
			lastTimesLabel[i]->setPosition( ccp(365*(width/ConstValue::imageWidth), (467.0-(i*57.0))*(height/ConstValue::imageHeight)) );
			this->addChild(lastTimesLabel[i], 1);
		}
	}
	return true;
}

//------------------------------------------------------
void ScoresScene::keyBackClicked() {
	CCDirector::sharedDirector()->popScene();
}
