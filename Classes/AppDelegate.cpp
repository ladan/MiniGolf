#include "AppDelegate.h"
#include "cocos2d.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::initInstance() {
    bool bRet = false;
    do
    {
        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching() {
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
	pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
	pDirector->setAnimationInterval(1.0 / 60);
	CCScene *pScene = MainMenuScene::scene();
	pDirector->runWithScene(pScene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->pause();
}

void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->resume();
}
