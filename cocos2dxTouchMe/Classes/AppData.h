//
//  appData.h
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/28.
//
//

#ifndef __cocos2dxTouchMe__appData__
#define __cocos2dxTouchMe__appData__

#include <iostream>
#include "ScoreData.h"

class AppData
{
public:

  enum Level {
      Easy,
      Normal,
      Hard
  };
  
  Level level;
  ScoreData data[20];
  
  static AppData* getInstance();
  float getScaleHeight(float height);
  float getScaleWidth(float width);
  void init();
  float getScale();
  float getBaseHeight();
private:
  static AppData* instance;

  float scale;
  float baseHeight;

};


#endif /* defined(__cocos2dxTouchMe__appData__) */
