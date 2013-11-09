#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

    // 座標を表示するテキストフィールwド
    cocos2d::CCLabelTTF* descriptionLabel;
    cocos2d::CCLabelTTF* ccTouchBeganLabel;
    cocos2d::CCLabelTTF* ccTouchMovedLabel;
    cocos2d::CCLabelTTF* ccTouchEndedLabel;
    cocos2d::CCLabelTTF* ccTouchCancelledLabel;

    
    // タッチイベント用関数の宣言
    bool ccTouchBegan(cocos2d::CCTouch* ptouch, cocos2d::CCEvent* pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};


#endif // __HELLOWORLD_SCENE_H__
