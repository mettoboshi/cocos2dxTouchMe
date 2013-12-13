#include "ScoreScene.h"
#include "SimpleAudioEngine.h"
#include "AppData.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* ScoreScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ScoreScene *layer = ScoreScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
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
    float screenWidth = pEGLView->getDesignResolutionSize().width;
    float screenHeight = pEGLView->getDesignResolutionSize().height;
    scaleSize = screenWidth / 320;
    
    // 背景画像の表示
/*
    background = CCSprite::create("background.png");
    background->setPosition(ccp(160 * scaleSize,240 * scaleSize));
    this->addChild(background);
*/
    
    // CCMenu
    CCMenuItemImage *startItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(ScoreScene::forTitle));
    CCMenuItemImage *retryItem = CCMenuItemImage::create("score.png", "score.png",this,menu_selector(ScoreScene::forRetry));

    CCMenu* menu = CCMenu::create(retryItem, startItem, NULL);
    menu->setPosition(ccp(160 * scaleSize,100 * scaleSize));
    menu->alignItemsHorizontallyWithPadding(50.0f);
    
    this->addChild(menu);

    CCTableView* tableView = CCTableView::create(this, CCSizeMake(screenWidth, screenHeight - (200 * scaleSize)));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(0, 150 * scaleSize));
    tableView->setDelegate(this);
    
    this->addChild(tableView);
//    tableView->reloadData();
    
    return true;
}

void ScoreScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
}

CCSize ScoreScene::cellSizeForTable(CCTableView* table){
    return CCSizeMake(300 * scaleSize, 20 * scaleSize);
}

CCTableViewCell* ScoreScene::tableCellAtIndex(CCTableView* table, unsigned int idx){
    CCString * string = CCString::createWithFormat("%i行目", idx + 1);
    
    CCTableViewCell* cell = table->dequeueCell();
    cell = new CCTableViewCell();
    cell->autorelease();
    
    CCLabelTTF* label = CCLabelTTF::create(string->getCString(), "Hiragino Kaku Gothic ProN", 20 * scaleSize);
    label->setAnchorPoint(ccp(0, 0));
    label->setPosition(ccp(20 * scaleSize, 0));
    label->setColor(ccc3(0, 0, 0));

    //label->setHorizontalAlignment(kCCTextAlignmentLeft);
    cell->addChild(label);
    return cell;
}

unsigned int ScoreScene::numberOfCellsInTableView(CCTableView* table){
    return 20;
}

void ScoreScene::forRetry() {
    // Transitionの設定
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}

void ScoreScene::forTitle() {
    // Transitionの設定
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, TitleScene::scene(), false);
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}

