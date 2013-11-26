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
    
    // 背景画像用スプライト
    cocos2d::CCSprite *background;
    // ボタン用スプライト
    cocos2d::CCSprite *startBtn;
    cocos2d::CCSprite *preferenceBtn;

    
    // タッチイベント用関数の宣言
/*
    bool ccTouchBegan(cocos2d::CCTouch* ptouch, cocos2d::CCEvent* pEvent);
    void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
    cocos2d::CCPoint getPanelPosition(cocos2d::CCPoint position);
    cocos2d::CCPoint setPanelPosition(cocos2d::CCPoint position);
*/
    void screenChange();
    void modalPush();

    
};


#endif