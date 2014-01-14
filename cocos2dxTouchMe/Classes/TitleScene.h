#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback();

    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(TitleScene);
    
    float scaleSize;
  float baseSize;
  
    // 背景画像用スプライト
    cocos2d::CCSprite *background;

    void easyStart();
    void nomalStart();
    void hardStart();

    
    
};

#endif