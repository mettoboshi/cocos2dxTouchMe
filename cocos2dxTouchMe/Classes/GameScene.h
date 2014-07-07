#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
  // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
  virtual bool init();

  // there's no 'id' in cpp, so we recommend to return the class instance pointer
  static cocos2d::CCScene* scene();
  
  // a selector callback
  void menuCloseCallback(CCObject* pSender);

  // preprocessor macro for "static create()" constructor ( node() deprecated )
  CREATE_FUNC(GameScene);
  
  const float itemSize = 70.0f;
  const float itemSpace = 10.0f;
  const float basePositionX = 5.0f;
  const float basePositionY = 35.0f;
  const float baseX = (basePositionX + (itemSize / 2));
  const float baseY = (basePositionY + (itemSize / 2));
  const float baseSize = itemSize + itemSpace;
  const int itemNum = 4;
  float scaleSize;
  bool startFlag = false;
  
  // 背景画像用スプライト
  cocos2d::CCSprite *background;

  // ハイライト用スプライト
  cocos2d::CCSprite *highLight;

  // プログレスバー用スプライト
  cocos2d::CCSprite *progressBar;
  cocos2d::CCProgressTimer *progressTimer;
  
  // タッチエリア表示用のスプライト
  cocos2d::CCSprite *touchArea;
  cocos2d::CCPoint areaPos;

  // readyエリア表示用のスプライト
  cocos2d::CCSprite *readyArea;

  // 表示用cookie種別
  int cookieCategory = 0;
  
  // タッチ可否フラグ
  bool touchFlag = false;
  
  // タッチイベント用関数の宣言
  bool ccTouchBegan(cocos2d::CCTouch* ptouch, cocos2d::CCEvent* pEvent);
  void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

  cocos2d::CCPoint getPanelPosition(cocos2d::CCPoint position);
  bool isContain(cocos2d::CCPoint location);
  cocos2d::CCPoint setPanelPosition(cocos2d::CCPoint position);

  //タイマー用
  float baseTimer = 1.0f;
  float timer = 1.0f;
  float gameTime = 0.0f;
  void gameStartTimer(float time);
  void gameTimer(float time);
  void gameEndTimer(float time);
  float nowTime = 0.0f;
  
  //得点表示用変数
  cocos2d::CCLabelTTF *scoreLabel;
  int score = 0;
  cocos2d::CCString *str;
 
  //コンボ数
  cocos2d::CCLabelTTF *comboLabel;
  cocos2d::CCString *comboStr;
  int combo = 0;
    
};

#endif