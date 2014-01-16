//
//  appData.cpp
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/28.
//
//

#include "AppData.h"
#include "cocos2d.h"

AppData* AppData::instance = NULL;

AppData* AppData::getInstance() {

    if(instance) {
        return instance;
    }
    instance = new AppData();
  
    return instance;
}

float AppData::getScaleHeight(float height) {
  return (height * scale) + baseHeight;
}

float AppData::getScaleWidth(float width) {
  return (width * scale);
}

float AppData::getScale() {
  return scale;
}

void AppData::init() {
  cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
  float screenWidth = pEGLView->getDesignResolutionSize().width;
  float screenHeight = pEGLView->getDesignResolutionSize().height;
  this->scale = pEGLView->getDesignResolutionSize().width / 320;
  if (screenHeight / screenWidth > 1.5) {
    this->baseHeight = 1136.0f - 960.0f;
  } else {
    baseHeight = 0;
  }
}