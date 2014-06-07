#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "AdViewManager.h"
#include "AppData.h"
#include "sqliteUtil.h"
#include "ScoreData.h"

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
  
  AppData* appData = AppData::getInstance();
  appData->init();
  
  // 背景画像の表示
  background = CCSprite::create("background.png");
  background->setPosition(ccp(appData->getScaleWidth(160.0f),appData->getScaleHeight(240.0f)));
  this->addChild(background);

  // CCMenu
  CCMenuItemImage *easyStartItem = CCMenuItemImage::create("eazy.png", "eazy.png",this,menu_selector(TitleScene::easyStart));
  CCMenuItemImage *normalStartItem = CCMenuItemImage::create("normal.png", "normal.png",this,menu_selector(TitleScene::nomalStart));
  CCMenuItemImage *hardStartItem = CCMenuItemImage::create("hard.png", "hard.png",this,menu_selector(TitleScene::hardStart));
  CCMenuItemImage *scoreItem = CCMenuItemImage::create("score.png", "score.png",this,menu_selector(TitleScene::scoreMove));
  
  CCMenu* menu = CCMenu::create(easyStartItem, normalStartItem, hardStartItem, scoreItem, NULL);
  menu->alignItemsVerticallyWithPadding(appData->getScaleWidth(20.0f));
  menu->setPosition(ccp(appData->getScaleWidth(160.0f), appData->getScaleHeight(160.0f)));
    
  this->addChild(menu);
  AdViewManager::showAdView();
  
  sqliteUtil* sql;
  //sql->init();
  //sql->doSelect(data);
  int count = sql->doCount();
  //int i = 0;

  
  //不要なデータを削除
  if(count > 20) {
    sql->doDeleteMinData();
  }
  
  return true;
}

void TitleScene::easyStart() {

  // Levelの設定
  AppData* appData = AppData::getInstance();
  appData->level = AppData::Easy;

  // Transitionの設定
  float duration = 0.5f;
  CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);

  // GameSceneへ画面遷移
  CCDirector::sharedDirector()->replaceScene(pScene);
  return;
}


void TitleScene::nomalStart() {

  // Levelの設定
  AppData* appData = AppData::getInstance();
  appData->level = AppData::Normal;
  
  float duration = 0.5f;
  CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
  
  // GameSceneへ画面遷移
  CCDirector::sharedDirector()->replaceScene(pScene);

  return;
}

void TitleScene::hardStart() {

  // Levelの設定
  AppData* appData = AppData::getInstance();
  appData->level = AppData::Hard;
  
  float duration = 0.5f;
  CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
  
  // GameSceneへ画面遷移
  CCDirector::sharedDirector()->replaceScene(pScene);
  
  return;
}

void TitleScene::scoreMove() {
  
  float duration = 0.5f;
  CCScene* pScene = CCTransitionPageTurn::create(duration, ScoreScene::scene(), false);
  
  // GameSceneへ画面遷移
  CCDirector::sharedDirector()->replaceScene(pScene);
  
  return;
}

