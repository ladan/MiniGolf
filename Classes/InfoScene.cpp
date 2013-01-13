#include "InfoScene.h"
#include "ConstValue.h"

using namespace cocos2d;

//------------------------------------------------------
CCScene* InfoScene::scene()
{
    CCScene *scene = CCScene::node();
    InfoScene *layer = InfoScene::node();
    scene->addChild(layer);
    return scene;
}

//------------------------------------------------------
bool InfoScene::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled( true );
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    //background "infoscene.png"
	CCSprite* pSprite = CCSprite::spriteWithFile("infoscene.png");
	pSprite->setPosition( ccp(width/2.0, height/2.0) );
	pSprite->setScaleX(width/ConstValue::imageWidth);
	pSprite->setScaleY(height/ConstValue::imageHeight);
	this->addChild(pSprite, 0);
	//button"back"
	CCMenuItemImage* backButton = CCMenuItemImage::itemFromNormalImage( "back.png", "back_s.png", this,
			menu_selector(InfoScene::keyBackClicked));
	backButton->setPosition(ccp(width/2, 56.0*(height/ConstValue::imageHeight)));
	backButton->setScaleX(width/ConstValue::imageWidth);
	backButton->setScaleY(height/ConstValue::imageHeight);
	CCMenu* pMenu = CCMenu::menuWithItems(backButton, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
	return true;
}

//------------------------------------------------------
void InfoScene::keyBackClicked() {
	CCDirector::sharedDirector()->popScene();
}
