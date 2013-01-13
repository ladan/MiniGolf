#include "LevelScene.h"
#include "GamePlayScene.h"
#include "MainMenuScene.h"
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
	//button"level1"
	CCMenuItemImage* level1Button = CCMenuItemImage::itemFromNormalImage( "level1.png", "level1_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	level1Button->setPosition(ccp(width/2,532.0*(height/ConstValue::imageHeight)));
	level1Button->setScaleX(width/ConstValue::imageWidth);
	level1Button->setScaleY(height/ConstValue::imageHeight);
	//button"level2"
	CCMenuItemImage* level2Button = CCMenuItemImage::itemFromNormalImage( "level2.png", "level2_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	level2Button->setPosition(ccp(width/2, 466.0*(height/ConstValue::imageHeight)));
	level2Button->setScaleX(width/ConstValue::imageWidth);
	level2Button->setScaleY(height/ConstValue::imageHeight);
	//button"level3"
	CCMenuItemImage* level3Button = CCMenuItemImage::itemFromNormalImage( "level3.png", "level3_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	level3Button->setPosition(ccp(width/2, 400.0*(height/ConstValue::imageHeight)));
	level3Button->setScaleX(width/ConstValue::imageWidth);
	level3Button->setScaleY(height/ConstValue::imageHeight);
	//button"level4"
	CCMenuItemImage* level4Button = CCMenuItemImage::itemFromNormalImage( "level4.png", "level4_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	level4Button->setPosition(ccp(width/2, 334.0*(height/ConstValue::imageHeight)));
	level4Button->setScaleX(width/ConstValue::imageWidth);
	level4Button->setScaleY(height/ConstValue::imageHeight);
	//button"level5"
	CCMenuItemImage* level5Button = CCMenuItemImage::itemFromNormalImage( "level5.png", "level5_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	level5Button->setPosition(ccp(width/2, 268.0*(height/ConstValue::imageHeight)));
	level5Button->setScaleX(width/ConstValue::imageWidth);
	level5Button->setScaleY(height/ConstValue::imageHeight);
	//button"level6"
	CCMenuItemImage* level6Button = CCMenuItemImage::itemFromNormalImage( "level6.png", "level6_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	//level6Button->setRotation(-90);
	level6Button->setPosition(ccp(width/2, 202.0*(height/ConstValue::imageHeight)));
	level6Button->setScaleX(width/ConstValue::imageWidth);
	level6Button->setScaleY(height/ConstValue::imageHeight);
	//button"level5"
	CCMenuItemImage* level7Button = CCMenuItemImage::itemFromNormalImage( "level7.png", "level7_s.png", this,
			menu_selector(LevelScene::setGamePlaySceneCallback));
	//level7Button->setRotation(-90);
	level7Button->setPosition(ccp(width/2, 136.0*(height/ConstValue::imageHeight)));
	level7Button->setScaleX(width/ConstValue::imageWidth);
	level7Button->setScaleY(height/ConstValue::imageHeight);
	//button"back"
	CCMenuItemImage* backButton = CCMenuItemImage::itemFromNormalImage( "back.png", "back_s.png", this,
			menu_selector(LevelScene::setMainMenuSceneCallback));
	//backButton->setRotation(-90);
	backButton->setPosition(ccp(width/2, 56.0*(height/ConstValue::imageHeight)));
	backButton->setScaleX(width/ConstValue::imageWidth);
	backButton->setScaleY(height/ConstValue::imageHeight);
    CCMenu* pMenu = CCMenu::menuWithItems(level1Button, level2Button, level3Button, level4Button, level5Button, level6Button, level7Button, backButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    //background "levelscene"
	CCSprite* pSprite = CCSprite::spriteWithFile("levelscene.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	return true;
}

//------------------------------------------------------
void LevelScene::setGamePlaySceneCallback( CCObject* pSender) {
	CCScene* gamePlayScene = GamePlayScene::scene();
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
