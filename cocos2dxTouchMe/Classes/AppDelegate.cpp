#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "AppData.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    
	//画面サイズを取得するためにCCEGLViewを作成
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    CCSize frameSize = pEGLView->getFrameSize();


    // 4inch対応
    if (frameSize.height / frameSize.width > 1.5) {
        pEGLView->setDesignResolutionSize(640.0f, 1136.0f, kResolutionNoBorder);
    } else {
        pEGLView->setDesignResolutionSize(640.0f, 960.0f, kResolutionNoBorder);
    }

    // create a scene. it's an autorelease object
    CCScene *pScene = TitleScene::scene();
//    CCScene *pScene = ScoreScene::scene();
    // run
    pDirector->runWithScene(pScene);


    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}