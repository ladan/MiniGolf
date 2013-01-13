#include "MainMenuScene.h"
#include "LevelScene.h"
#include "ScoresScene.h"
#include "InfoScene.h"

#include "ConstValue.h"

using namespace cocos2d;

//------------------------------------------------------
CCScene* MainMenuScene::scene() {
    CCScene *scene = CCScene::node();
    MainMenuScene *layer = MainMenuScene::node();
    scene->addChild(layer);
    return scene;
}

//------------------------------------------------------
bool MainMenuScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    //button "play"
    CCMenuItemImage* playButton = CCMenuItemImage::itemFromNormalImage( "play.png", "play_s.png", this,
    		menu_selector(MainMenuScene::setLevelSceneCallback));
    playButton->setPosition(ccp(width/2, 331.0*(height/ConstValue::imageHeight)));
    playButton->setScaleX(width/ConstValue::imageWidth);
    playButton->setScaleY(height/ConstValue::imageHeight);
    //button "scores"
    CCMenuItemImage* scoresButton = CCMenuItemImage::itemFromNormalImage( "scores.png", "scores_s.png", this,
        		menu_selector(MainMenuScene::setScoresSceneCallback));
    scoresButton->setPosition(ccp(width/2, 246.0*(height/ConstValue::imageHeight)));
    scoresButton->setScaleX(width/ConstValue::imageWidth);
    scoresButton->setScaleY(height/ConstValue::imageHeight);
	//button "info"
	CCMenuItemImage* infoButton = CCMenuItemImage::itemFromNormalImage( "info.png", "info_s.png", this,
				menu_selector(MainMenuScene::setInfoSceneCallback));
	infoButton->setPosition(ccp(width/2, 158.0*(height/ConstValue::imageHeight)));
	infoButton->setScaleX(width/ConstValue::imageWidth);
	infoButton->setScaleY(height/ConstValue::imageHeight);
	//button "exit"
	CCMenuItemImage* exitButton = CCMenuItemImage::itemFromNormalImage( "exit.png", "exit_s.png", this,
				menu_selector(MainMenuScene::menuCloseCallback));
	exitButton->setPosition(ccp( width/2, 71.0*(height/ConstValue::imageHeight)));
	exitButton->setScaleX(width/ConstValue::imageWidth);
	exitButton->setScaleY(height/ConstValue::imageHeight);
    CCMenu* pMenu = CCMenu::menuWithItems(exitButton, infoButton, scoresButton, playButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    //background "main"
	CCSprite* pSprite = CCSprite::spriteWithFile("main.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	return true;
}

//------------------------------------------------------
void MainMenuScene::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
}

//------------------------------------------------------
void MainMenuScene::setLevelSceneCallback( CCObject* pSender ) {
	CCScene* levelScene = LevelScene::scene();
	CCDirector::sharedDirector()->pushScene( levelScene );
}

//------------------------------------------------------
void MainMenuScene::setScoresSceneCallback( CCObject* pSender ) {
	CCScene* scoresScene = ScoresScene::scene();
	CCDirector::sharedDirector()->pushScene( scoresScene );
}

//------------------------------------------------------
void MainMenuScene::setInfoSceneCallback( CCObject* pSender ) {
	CCScene* infoScene = InfoScene::scene();
	CCDirector::sharedDirector()->pushScene( infoScene );
}

//------------------------------------------------------
void MainMenuScene::keyBackClicked() {
	CCDirector::sharedDirector()->end();
}
