#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // 背景色を変更
    CCLayerColor *color = CCLayerColor::create(ccc4(255.0f,255.0f,255.0f,255.0f));
    this->addChild(color);
    
    // 画面サイズを取得。縦の場合画面サイズの幅は320px か 640pxしかないので、ここから拡大幅を求める。
    cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
    scaleSize = pEGLView->getDesignResolutionSize().width / 320;
    
    // 背景画像の表示
    background = CCSprite::create("background.png");
    background->setPosition(ccp(160 * scaleSize,240 * scaleSize));
    this->addChild(background);

    // CCMenu
    CCMenuItemImage *moveSceneItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(TitleScene::screenChange));

    moveSceneItem->setPosition(ccp(200,200));
    CCMenu* moveMenu = CCMenu::create(moveSceneItem, NULL);
    moveMenu->setPosition(CCPointZero);

    
    CCMenuItemImage *modalSceneItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(TitleScene::modalPush));

    modalSceneItem->setPosition(ccp(400,200));
    CCMenu* modalMenu = CCMenu::create(modalSceneItem, NULL);
    modalMenu->setPosition(CCPointZero);
    
    this->addChild(moveMenu);
    this->addChild(modalMenu);
    
    return true;
}

void TitleScene::screenChange() {
    // Transitionの設定
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);

    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}

void TitleScene::modalPush() {
    // Transitionの設定
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->pushScene(pScene);
    return;
}

