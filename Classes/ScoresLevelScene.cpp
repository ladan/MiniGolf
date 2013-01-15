#include "ScoresLevelScene.h"
#include "GamePlayScene.h"
#include "LevelScene.h"
#include "MiniGolfData.h"
#include <sstream>
#include <string>

#include "ConstValue.h"

using namespace cocos2d;

int ScoresLevelScene::level;
double ScoresLevelScene::time;
bool ScoresLevelScene::failed;
//------------------------------------------------------
CCScene* ScoresLevelScene::scene(int l, double t, bool f = false) {
	level=l;
	time=t;
	failed = f;
    CCScene *scene = CCScene::node();
    ScoresLevelScene *layer = ScoresLevelScene::node();
    scene->addChild(layer);
    return scene;
}

//------------------------------------------------------
bool ScoresLevelScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled( true );
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    //background "result.png"
	CCSprite* pSprite = CCSprite::spriteWithFile("result.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	//button"levels"
	CCMenuItemImage* levelsButton = CCMenuItemImage::itemFromNormalImage( "levels.png", "levels_s.png", this,
			menu_selector(ScoresLevelScene::setLevelSceneCallback));
	levelsButton->setPosition(ccp(width/2, 140.0*(height/ConstValue::imageHeight)));
	levelsButton->setScaleX(width/ConstValue::imageWidth);
	levelsButton->setScaleY(height/ConstValue::imageHeight);
	//button"repeat"
	CCMenuItemImage* repeatButton = CCMenuItemImage::itemFromNormalImage( "repeat.png", "repeat_s.png", this,
			menu_selector(ScoresLevelScene::setGamePlaySceneCallback));
	repeatButton->setPosition(ccp(width/2, 220.0*(height/ConstValue::imageHeight)));
	repeatButton->setScaleX(width/ConstValue::imageWidth);
	repeatButton->setScaleY(height/ConstValue::imageHeight);
	//button"nextlevel"
	CCMenuItemImage* nextlevelButton = CCMenuItemImage::itemFromNormalImage( "nextlevel.png", "nextlevel_s.png", this,
			menu_selector(ScoresLevelScene::setGamePlayNextSceneCallback));
	nextlevelButton->setPosition(ccp(width/2, 300.0*(height/ConstValue::imageHeight)));
	nextlevelButton->setScaleX(width/ConstValue::imageWidth);
	nextlevelButton->setScaleY(height/ConstValue::imageHeight);
	CCMenu* pMenu;

	CCLabelTTF* bestLabel;
	CCLabelTTF* resultLabel;

	char resultT[128];
	sprintf(resultT,"%0.2f",time);
	string resultS="Result: ";
	resultS+=resultT;
	if(failed)
	{
		resultS = "You failed... avoid ponds!";
	}else if((time > MAX_TIME))
	{
		resultS+=" - Too Slow!\n Be faster than 15 seconds!";
	}else if(7 < time && time <= MAX_TIME)
	{
		resultS+=" - Nice one!";
	}else
	{
		resultS+=" - Great one!";
	}
	resultLabel = CCLabelTTF::labelWithString(resultS.c_str(), "Arial", 22);
	ccColor3B colour;
	if((time > MAX_TIME) || failed)
	{
		colour.r = 139;
		colour.b = 0;
		colour.g = 0;
	}else if(time <= MAX_TIME)
	{
		colour.r = 238;
		colour.g = 173;
		colour.b = 14;
		}
	resultLabel->setColor(colour);
	resultLabel->setPosition( ccp(width/2, 470.0*(height/ConstValue::imageHeight)) );
	this->addChild(resultLabel, 1);
	char bestT[128];
	string bestS="Best: ";
	if(!failed)
	{
		MiniGolfData::addScore(level-1,time);
		MiniGolfData::save();

	}

	double bestScore=MiniGolfData::getBestScore(level-1);
	if(bestScore<0.0)
	{
		bestS+="-";
		bestLabel= CCLabelTTF::labelWithString(bestS.c_str(), "Arial", 20);
	} else
	{
		sprintf(bestT,"%0.2f",bestScore);
		bestS+=bestT;
		bestLabel= CCLabelTTF::labelWithString(bestS.c_str(), "Arial", 20);
	}
	if((time <= MAX_TIME) && !failed)
	{
		if((level)>MiniGolfData::getMaxUnlockedLevel() && level != 7)
		{
			MiniGolfData::unlockLevel(level);
			MiniGolfData::save();
		}
	}


	CCLOG("level = %d max = %d", level,MiniGolfData::getMaxUnlockedLevel() );
	if(level==7 || level > MiniGolfData::getMaxUnlockedLevel())
	{
		pMenu = CCMenu::menuWithItems(repeatButton, levelsButton, NULL);
	} else {

		pMenu = CCMenu::menuWithItems(nextlevelButton, repeatButton, levelsButton, NULL);
	}

	bestLabel->setPosition( ccp(width/2, 400.0*(height/ConstValue::imageHeight)) );
	this->addChild(bestLabel, 1);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
	return true;
}

//------------------------------------------------------
void ScoresLevelScene::setGamePlayNextSceneCallback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(level+1);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void ScoresLevelScene::setGamePlaySceneCallback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(level);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void ScoresLevelScene::setLevelSceneCallback( CCObject* pSender ) {
	CCScene* levelScene = LevelScene::scene();
	CCDirector::sharedDirector()->pushScene( levelScene );
}

//------------------------------------------------------
void ScoresLevelScene::keyBackClicked() {
	CCScene* levelScene = LevelScene::scene();
	CCDirector::sharedDirector()->pushScene( levelScene );
}
