#include "ScoreScene.h"
#include "SimpleAudioEngine.h"
#include "AppData.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ScoreScene.h"
#include "sqliteUtil.h"
#include <string>

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
/*
  scaleSize = screenWidth / 320;
  if (screenHeight / screenWidth >= 1.5) {
    baseSize = 1136.0f - 960.0f;
  }
*/
  cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
  float screenWidth = pEGLView->getDesignResolutionSize().width;
  float screenHeight = pEGLView->getDesignResolutionSize().height;

  AppData* appData = AppData::getInstance();
  
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
  menu->setPosition(ccp(appData->getScaleWidth(160), appData->getScaleHeight(20)));
  menu->alignItemsHorizontallyWithPadding(50.0f);
  
  this->addChild(menu);

  //Scoreを取得
  sqliteUtil* sql;
  count = sql->doCount();
  sql->doSelect(data);
  
/*
  for (int i = 0; i < count; i++) {
    CCLog("score-select %d, %d, %d, %d", data[i].id, data[i].level, data[i].score, i);
  }
*/

  CCTableView* tableView = CCTableView::create(this, CCSizeMake(screenWidth, screenHeight - appData->getScaleWidth(200)));
  tableView->setDirection(kCCScrollViewDirectionVertical);
  tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
  tableView->setPosition(ccp(0, appData->getScaleHeight(50)));
  tableView->setDelegate(this);
  
  this->addChild(tableView);
//    tableView->reloadData();
  
  return true;
}

void ScoreScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
}

CCSize ScoreScene::cellSizeForTable(CCTableView* table){
  AppData* appData = AppData::getInstance();
  return CCSizeMake(appData->getScaleWidth(300), appData->getScaleWidth(20));
}

CCTableViewCell* ScoreScene::tableCellAtIndex(CCTableView* table, unsigned int idx){
  AppData* appData = AppData::getInstance();

  CCString* tableStrNo = CCString::create("");
  CCString* tableStrLevel = CCString::create("");
  CCString* tableStrScore = CCString::create("");
  
  string str = "";
  if (idx < count) {
    if (data[idx].level == 0) {
      str = "Easy";
    } else if(data[idx].level == 1) {
      str = "Nomal";
    } else if(data[idx].level == 2) {
      str = "Hard";
    }
    tableStrNo = CCString::createWithFormat("%2i", idx + 1);
    tableStrLevel = CCString::createWithFormat(": (Level) %6s", str.c_str());
    tableStrScore = CCString::createWithFormat("(Score) %3d", data[idx].score);
  }
  
  CCTableViewCell* cell = table->dequeueCell();
  cell = new CCTableViewCell();
  cell->autorelease();
  
  CCLabelTTF* labelNo = CCLabelTTF::create(tableStrNo->getCString(), "Hiragino Kaku Gothic ProN", appData->getScaleWidth(18));
  labelNo->setAnchorPoint(ccp(0, 0));
  labelNo->setPosition(ccp(appData->getScaleWidth(20), 0));
  labelNo->setColor(ccc3(0, 0, 0));
  //label->setHorizontalAlignment(kCCTextAlignmentLeft);
  cell->addChild(labelNo);

  CCLabelTTF* labelScore = CCLabelTTF::create(tableStrScore->getCString(), "Hiragino Kaku Gothic ProN", appData->getScaleWidth(18));
  labelScore->setAnchorPoint(ccp(0, 0));
  labelScore->setPosition(ccp(appData->getScaleWidth(50), 0));
  labelScore->setColor(ccc3(0, 0, 0));
  //label->setHorizontalAlignment(kCCTextAlignmentLeft);
  cell->addChild(labelScore);

  CCLabelTTF* labelLevel = CCLabelTTF::create(tableStrLevel->getCString(), "Hiragino Kaku Gothic ProN", appData->getScaleWidth(18));
  labelLevel->setAnchorPoint(ccp(0, 0));
  labelLevel->setPosition(ccp(appData->getScaleWidth(160), 0));
  labelLevel->setColor(ccc3(0, 0, 0));
  //label->setHorizontalAlignment(kCCTextAlignmentLeft);
  cell->addChild(labelLevel);
  

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

