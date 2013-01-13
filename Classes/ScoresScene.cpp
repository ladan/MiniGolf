#include "ScoresScene.h"
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
	return true;
}

//------------------------------------------------------
void ScoresScene::keyBackClicked() {
	CCDirector::sharedDirector()->popScene();
}
