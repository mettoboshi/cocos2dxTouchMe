#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ScoreData.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ScoreScene : public CCLayer,
public cocos2d::extension::CCTableViewDataSource,
public cocos2d::extension::CCTableViewDelegate
{
public:
    
  virtual bool init();
  static CCScene* scene();
  
  virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
  
  virtual CCSize cellSizeForTable(CCTableView* table);
  virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
  virtual unsigned int numberOfCellsInTableView(CCTableView* table);
  
  virtual void scrollViewDidScroll(CCScrollView* view){};
  virtual void scrollViewDidZoom(CCScrollView* view){};
  
  CREATE_FUNC(ScoreScene);
  
  float scaleSize;
  float baseSize;
  
  ScoreData data[20];
  int count;
  // 背景画像用スプライト
  cocos2d::CCSprite *background;

  // メソッド定義
  void forTitle();
  void forRetry();
    
};

#endif