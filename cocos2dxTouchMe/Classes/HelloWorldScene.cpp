#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    // 座標を表示するラベルを作成
    descriptionLabel = CCLabelTTF::create("Touch Me!", "arial", 50);
    descriptionLabel->setPosition(ccp(150, 520));
    this->addChild(descriptionLabel);
    
    //タッチ開始座標を表示するラベル
    ccTouchBeganLabel = CCLabelTTF::create("[ccTouchBegan] (x, y) ", "arial", 30);
    ccTouchBeganLabel ->setPosition(ccp(400, 450));
    this->addChild(ccTouchBeganLabel);

    //スワイプ時の座標を表示するラベル
    ccTouchMovedLabel = CCLabelTTF::create("[ccTouchMoved] (x, y) ", "arial", 30);
    ccTouchMovedLabel ->setPosition(ccp(400, 400));
    this->addChild(ccTouchMovedLabel);

    //タッチ終了時の座標を表示するラベル
    ccTouchEndedLabel = CCLabelTTF::create("[ccTouchEnded] (x, y) ", "arial", 30);
    ccTouchEndedLabel ->setPosition(ccp(400, 350));
    this->addChild(ccTouchEndedLabel);

    //タッチキャンセル時の座標を表示するラベル
    ccTouchCancelledLabel = CCLabelTTF::create("[ccTouchCancelled] (x, y) ", "arial", 30);
    ccTouchCancelledLabel ->setPosition(ccp(400, 300));
    this->addChild(ccTouchCancelledLabel);
    
    // タッチモードを設定する
    this->setTouchMode(kCCTouchesOneByOne);
    
    
    // タッチを有効にする
    this->setTouchEnabled(true);
    
    return true;
}


// タッチ用メソッド
bool HelloWorld::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
    //タッチした座標を取得
    CCPoint location =pTouch->getLocation();

    //ログ出力
    CCLog("[ccTouchBegan] (%f,%f)", location.x, location.y);

    //画面出力
    CCString *str = CCString::createWithFormat("[ccTouchBegan] (%f,%f)", location.x, location.y);
    ccTouchBeganLabel->setString(str->getCString());
    
    return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

    //タッチした座標を取得
    CCPoint location =pTouch->getLocation();

    //ログ出力
    CCLog("[ccTouchMoved] (%f,%f)", location.x, location.y);
    
    //画面出力
    CCString *str = CCString::createWithFormat("[ccTouchMoved] (%f,%f)", location.x, location.y);
    ccTouchMovedLabel->setString(str->getCString());


}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

    //タッチした座標を取得
    CCPoint location =pTouch->getLocation();

    //ログ出力
    CCLog("[ccTouchEnded] (%f,%f)", location.x, location.y);
    
    //画面出力
    CCString *str = CCString::createWithFormat("[ccTouchEnded] (%f,%f)", location.x, location.y);
    ccTouchEndedLabel->setString(str->getCString());

}

void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

    //タッチした座標を取得
    CCPoint location =pTouch->getLocation();

    //ログ出力
    CCLog("[ccTouchCancelled] (%f,%f)", location.x, location.y);
    
    //画面出力
    CCString *str = CCString::createWithFormat("[ccTouchCancelled] (%f,%f)", location.x, location.y);
    ccTouchCancelledLabel->setString(str->getCString());
    

}

