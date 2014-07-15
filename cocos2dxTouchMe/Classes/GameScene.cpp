#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "AppData.h"
#include "ScoreScene.h"
#include "sqliteUtil.h"
#include "ScoreData.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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

/*
  // 画面サイズを取得。縦の場合画面サイズの幅は320px か 640pxしかないので、ここから拡大幅を求める。
  cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
  scaleSize = pEGLView->getDesignResolutionSize().width / 320;
*/

  AppData* appData = AppData::getInstance();

  background = CCSprite::create("background.png");
  background->setPosition(ccp(appData->getScaleWidth(160),appData->getScaleHeight(190)));
  this->addChild(background);

  // 1マス分のスプライトを生成
  highLight = CCSprite::create("alpha.png");
  highLight->setPosition(ccp(appData->getScaleWidth(baseX), appData->getScaleHeight(baseY)));
  this->addChild(highLight);

  // 1マス分のスプライトを生成
  touchArea = CCSprite::create("alpha.png");
  touchArea->setPosition(ccp(appData->getScaleWidth(baseX), appData->getScaleHeight(baseY)));
  this->addChild(touchArea);

  // 得点表示用のラベルを用意
  score = 0;
  str = CCString::createWithFormat("Score : %7d", score);
  scoreLabel = CCLabelTTF::create(str->getCString() , "arial", 40);
  scoreLabel->setColor(ccc3(0,0,0));
  scoreLabel->setPosition(ccp(appData->getScaleWidth(230), appData->getScaleHeight(400)));
  this->addChild(scoreLabel);

  // コンボ数のラベルを用意
  combo = 0;
  comboStr = CCString::createWithFormat("%3d Hit", combo);
  comboLabel = CCLabelTTF::create(comboStr->getCString() , "arial", 40);
  comboLabel->setColor(ccc3(0,0,0));
  comboLabel->setPosition(ccp(appData->getScaleWidth(50), appData->getScaleHeight(400)));
  this->addChild(comboLabel);

  
  // プログレスバーを生成
  progressBar = CCSprite::create("progress-bar.png");
  progressTimer = CCProgressTimer::create(progressBar);
  progressTimer->setType(kCCProgressTimerTypeBar);
  progressTimer->setPercentage(100.0f);
  progressTimer->setMidpoint(ccp(0.0f, 0.0f));
  progressTimer->setBarChangeRate(ccp(1.0f, 0.0f));
  progressTimer->setPosition(ccp(appData->getScaleWidth(150), appData->getScaleHeight(370)));
  this->addChild(progressTimer);

  //Ready画面の生成
  readyArea = CCSprite::create("ready.png");
  readyArea->setPosition(ccp(appData->getScaleWidth(160), appData->getScaleHeight(200)));
  readyArea->setTag(1);
  this->addChild(readyArea);

  //効果音の読み込み
  SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
  SimpleAudioEngine::sharedEngine()->preloadEffect("rare.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("touch.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("speedUp.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("speedDown.mp3");
  
  if(appData->level == 0) {
    baseTimer = 1.0f;
    timer = 1.0f;
  } else if(appData->level == 1) {
    baseTimer = 0.5f;
    timer = 0.5f;
  } else if(appData->level == 2) {
    baseTimer = 0.2f;
    timer = 0.2f;
  }

  gameTime = 0;

  // タッチモードを設定する
  this->setTouchMode(kCCTouchesOneByOne);

	// タッチを有効にする
	this->setTouchEnabled(true);
  this->scheduleOnce(schedule_selector(GameScene::gameStartTimer), 2);

  return true;
}

void GameScene::gameStartTimer(float time)
{
  //readyを消す
  removeChildByTag(1);
  this->schedule(schedule_selector(GameScene::gameTimer), 0.1);
  this->schedule(schedule_selector(GameScene::gameEndTimer), 1);
  return;
}

void GameScene::gameEndTimer(float time)
{
  gameTime++;
  progressTimer->setPercentage(100.0f - (gameTime * 10));
  
  if (gameTime > 10){
    this->pauseSchedulerAndActions();

    AppData* appData = AppData::getInstance();
    sqliteUtil* sql;
    ScoreData scoreData;
    scoreData.id = 0;
    scoreData.level = appData->level;
    scoreData.score = score;
    
    sql->doInsert(scoreData);
    
    float duration = 0.5f;
    CCScene* pScene = CCTransitionRotoZoom::create(duration, ScoreScene::scene());
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
  }
  
  return;
}

void GameScene::gameTimer(float time)
{
  nowTime += time;
  if (nowTime < timer) {
    return;
  }
 
  nowTime = 0.0f;
  //初期化
  CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("alpha.png");
  touchArea->setTexture(pTexture);
  touchFlag = false;
  
  // 0-15の乱数を求める
  int randNum = arc4random() % 16;
  
  // Cookieの種類を変えられるようにする 0-1 : timePlus, 2-3 : speedPlus, 4-10 : other
  int cookieNum = arc4random() % 10;
  
  
  // マスに当てはめる
  areaPos = ccp(floor(randNum / 4), randNum % 4);
  CCPoint pos = setPanelPosition(areaPos);
  
  touchArea->setPosition(pos);
  if (cookieNum < 2) {
    pTexture = CCTextureCache::sharedTextureCache()->addImage("scorePlus.png");
    cookieCategory = 1;
  } else if (cookieNum >= 2 && cookieNum < 4) {
    pTexture = CCTextureCache::sharedTextureCache()->addImage("timePlus.png");
    cookieCategory = 2;
  } else {
    pTexture = CCTextureCache::sharedTextureCache()->addImage("cookie.png");
    cookieCategory = 0;
  }
  touchArea->setTexture(pTexture);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  //タッチした座標を取得
  CCPoint location =pTouch->getLocation();
  CCPoint pos = getPanelPosition(location);
  
  if(!isContain(pos)) {
    return false;
  }
  
  //タッチした場所と光っている場所が同じなら得点を加算し、フラグをtrueにする
  if (pos.equals(areaPos) && touchFlag == false) {
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("alpha.png");
    touchArea->setTexture(pTexture);

    int SoundID;
    if (cookieCategory == 0) {
      score += 10;
    } else if (cookieCategory == 1) {
      score += 50;
    } else if (cookieCategory == 2) {
      score += 10;
      gameTime -= 2;
    } else {
      score += 10;
    }
    combo++;
    
    if (combo % 5 == 0 && combo != 0) {
      timer -= 0.2;
      SoundID = SimpleAudioEngine::sharedEngine()->playEffect("speedUp.mp3");
    } else if (cookieCategory == 0) {
      SoundID = SimpleAudioEngine::sharedEngine()->playEffect("touch.mp3");
    } else if (cookieCategory == 1) {
      SoundID = SimpleAudioEngine::sharedEngine()->playEffect("rare.mp3");
    } else if (cookieCategory == 2) {
      SoundID = SimpleAudioEngine::sharedEngine()->playEffect("rare.mp3");
    }
    
    str = CCString::createWithFormat("Score : %7d", score);
    scoreLabel->setString(str->getCString());

    comboStr = CCString::createWithFormat("%3d HiT", combo);
    comboLabel->setString(comboStr->getCString());
    
    touchFlag = true;
  } else {
    if (score >= 10) {
      //score -= 10;
    }

    if (timer < baseTimer) {
      timer += 0.1f;
      int SoundID;
      SoundID = SimpleAudioEngine::sharedEngine()->playEffect("speedDown.mp3");
    }
    combo = 0;
    
    
    //score = max(0, score - 10);
    
    str = CCString::createWithFormat("Score : %7d", score);
    scoreLabel->setString(str->getCString());

    comboStr = CCString::createWithFormat("%3d HiT", combo);
    comboLabel->setString(comboStr->getCString());

  }

  CCPoint realPos = setPanelPosition(pos);
  highLight->setPosition(ccp(realPos.x, realPos.y));
  CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("highlight.png");
  highLight->setTexture(pTexture);
  
  return true;
}

void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("alpha.png");
    highLight->setTexture(pTexture);
}

void GameScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
}

CCPoint GameScene::getPanelPosition(CCPoint position)
{
  AppData* appData = AppData::getInstance();
  
  //ポジションからx, yを求め返戻
  float tmpX = position.x / appData->getScale();
  float tmpY = (position.y - appData->getBaseHeight()) / appData->getScale();
  int x = floor((tmpX - basePositionX) / (itemSize + itemSpace));
  int y = floor((tmpY - basePositionY) / (itemSize + itemSpace));
  CCLog("x, y : %d, %d", x, y);
  
  return ccp(x, y);
}

bool GameScene::isContain(CCPoint position)
{
    if (position.x >= 0 && position.x <= 3 && position.y >= 0 && position.y <= 3 ) {
        return true;
    }
    return false;
}

CCPoint GameScene::setPanelPosition(CCPoint position)
{
  AppData* appData = AppData::getInstance();
  
  //ポジションからx, yを求め返戻
  int x = appData->getScaleWidth((baseX + (itemSpace * (position.x)) + (itemSize * position.x)));
  int y = appData->getScaleHeight((baseY + (itemSpace * (position.y)) + (itemSize * position.y)));
  return ccp(x, y);
}
