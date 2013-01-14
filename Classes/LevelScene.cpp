#include "LevelScene.h"
#include "GamePlayScene.h"
#include "MainMenuScene.h"
#include "MiniGolfData.h"

#include "ConstValue.h"

using namespace cocos2d;

//------------------------------------------------------
CCScene* LevelScene::scene() {
    CCScene *scene = CCScene::node();
    LevelScene *layer = LevelScene::node();
    scene->addChild(layer);
    return scene;
}

//------------------------------------------------------
bool LevelScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    MiniGolfData::open();
    maxlevel=MiniGolfData::getMaxUnlockedLevel()+1;
    //maxlevel=7;
    CCMenuItemImage* levelButton[6];
    CCMenu* pMenulevel[6];
    switch(maxlevel)
    {
    case 7:
    	//button"level7"
    	levelButton[5] = CCMenuItemImage::itemFromNormalImage( "level7.png", "level7_s.png", this,
				menu_selector(LevelScene::setGamePlayScene7Callback));
    	levelButton[5]->setPosition(ccp(width/2,136.0*(height/ConstValue::imageHeight)));
    	levelButton[5]->setScaleX(width/ConstValue::imageWidth);
    	levelButton[5]->setScaleY(height/ConstValue::imageHeight);
		pMenulevel[5] = CCMenu::menuWithItems(levelButton[5], NULL);
		pMenulevel[5]->setPosition( CCPointZero );
		this->addChild(pMenulevel[5], 1);
    case 6:
    	//button"level6"
    	levelButton[4] = CCMenuItemImage::itemFromNormalImage( "level6.png", "level6_s.png", this,
				menu_selector(LevelScene::setGamePlayScene6Callback));
    	levelButton[4]->setPosition(ccp(width/2, 202.0*(height/ConstValue::imageHeight)));
    	levelButton[4]->setScaleX(width/ConstValue::imageWidth);
    	levelButton[4]->setScaleY(height/ConstValue::imageHeight);
    	pMenulevel[4] = CCMenu::menuWithItems(levelButton[4], NULL);
    	pMenulevel[4]->setPosition( CCPointZero );
		this->addChild(pMenulevel[4], 1);
    case 5:
    	//button"level5"
    	levelButton[3] = CCMenuItemImage::itemFromNormalImage( "level5.png", "level5_s.png", this,
				menu_selector(LevelScene::setGamePlayScene5Callback));
    	levelButton[3]->setPosition(ccp(width/2,268.0*(height/ConstValue::imageHeight)));
    	levelButton[3]->setScaleX(width/ConstValue::imageWidth);
    	levelButton[3]->setScaleY(height/ConstValue::imageHeight);
    	pMenulevel[3] = CCMenu::menuWithItems(levelButton[3], NULL);
    	pMenulevel[3]->setPosition( CCPointZero );
		this->addChild(pMenulevel[3], 1);
    case 4:
    	//button"level4"
    	levelButton[2] = CCMenuItemImage::itemFromNormalImage( "level4.png", "level4_s.png", this,
				menu_selector(LevelScene::setGamePlayScene4Callback));
    	levelButton[2]->setPosition(ccp(width/2,334.0*(height/ConstValue::imageHeight)));
    	levelButton[2]->setScaleX(width/ConstValue::imageWidth);
    	levelButton[2]->setScaleY(height/ConstValue::imageHeight);
		pMenulevel[2] = CCMenu::menuWithItems(levelButton[2], NULL);
		pMenulevel[2]->setPosition( CCPointZero );
		this->addChild(pMenulevel[2], 1);
    case 3:
    	//button"level3"
    	levelButton[1]= CCMenuItemImage::itemFromNormalImage( "level3.png", "level3_s.png", this,
				menu_selector(LevelScene::setGamePlayScene3Callback));
    	levelButton[1]->setPosition(ccp(width/2,400.0*(height/ConstValue::imageHeight)));
    	levelButton[1]->setScaleX(width/ConstValue::imageWidth);
    	levelButton[1]->setScaleY(height/ConstValue::imageHeight);
		pMenulevel[1] = CCMenu::menuWithItems(levelButton[1], NULL);
		pMenulevel[1]->setPosition( CCPointZero );
		this->addChild(pMenulevel[1], 1);
    case 2:
    	//button"level2"
		levelButton[0] = CCMenuItemImage::itemFromNormalImage( "level2.png", "level2_s.png", this,
				menu_selector(LevelScene::setGamePlayScene2Callback));
		levelButton[0]->setPosition(ccp(width/2,466.0*(height/ConstValue::imageHeight)));
		levelButton[0]->setScaleX(width/ConstValue::imageWidth);
		levelButton[0]->setScaleY(height/ConstValue::imageHeight);
		pMenulevel[0] = CCMenu::menuWithItems(levelButton[0], NULL);
		pMenulevel[0]->setPosition( CCPointZero );
		this->addChild(pMenulevel[0], 1);
    default:
    	break;
    }
    //button"level1"
    CCMenuItemImage* level1Button = CCMenuItemImage::itemFromNormalImage( "level1.png", "level1_s.png", this,
			menu_selector(LevelScene::setGamePlayScene1Callback));
	level1Button->setPosition(ccp(width/2,532.0*(height/ConstValue::imageHeight)));
	level1Button->setScaleX(width/ConstValue::imageWidth);
	level1Button->setScaleY(height/ConstValue::imageHeight);
	CCMenu* pMenulevel1 = CCMenu::menuWithItems(level1Button, NULL);
	pMenulevel1->setPosition( CCPointZero );
	this->addChild(pMenulevel1, 1);
	//button"back"
	CCMenuItemImage* backButton = CCMenuItemImage::itemFromNormalImage( "back.png", "back_s.png", this,
			menu_selector(LevelScene::setMainMenuSceneCallback));
	backButton->setPosition(ccp(width/2, 56.0*(height/ConstValue::imageHeight)));
	backButton->setScaleX(width/ConstValue::imageWidth);
	backButton->setScaleY(height/ConstValue::imageHeight);
	CCMenu* pMenuback = CCMenu::menuWithItems(backButton, NULL);
	pMenuback->setPosition( CCPointZero );
	this->addChild(pMenuback, 1);
    //background "levelscene"
	CCSprite* pSprite = CCSprite::spriteWithFile("levelscene.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	return true;
}

//------------------------------------------------------
void LevelScene::setGamePlayScene1Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(1);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene2Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(2);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene3Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(3);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene4Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(4);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene5Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(5);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene6Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(6);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setGamePlayScene7Callback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene(7);
	CCDirector::sharedDirector()->pushScene( gamePlayScene );
}

//------------------------------------------------------
void LevelScene::setMainMenuSceneCallback( CCObject* pSender) {
	CCScene* mainMenuScene = MainMenuScene::scene();
	CCDirector::sharedDirector()->pushScene( mainMenuScene );
}

//------------------------------------------------------
void LevelScene::keyBackClicked() {
	CCDirector::sharedDirector()->end();
}
