#include "GameScene.h"
#include "SimpleAudioEngine.h"

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

    // 画面サイズを取得。縦の場合画面サイズの幅は320px か 640pxしかないので、ここから拡大幅を求める。
    cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
    scaleSize = pEGLView->getDesignResolutionSize().width / 320;

    background = CCSprite::create("background.png");
    background->setPosition(ccp(160 * scaleSize,240 * scaleSize));
    this->addChild(background);
    
    // 1マス分のスプライトを生成
    highLight = CCSprite::create("alpha.png");
    highLight->setPosition(ccp(baseX * scaleSize, baseY * scaleSize));
    this->addChild(highLight);

    // 1マス分のスプライトを生成
    touchArea = CCSprite::create("alpha.png");
    touchArea->setPosition(ccp(baseX * scaleSize, baseY * scaleSize));
    this->addChild(touchArea);

    // 得点表示用のラベルを用意
    score = 0;
    str = CCString::createWithFormat("Score : %7d", score);
    scoreLabel = CCLabelTTF::create(str->getCString() , "arial", 40);
    scoreLabel->setColor(ccc3(0,0,0));
    scoreLabel->setPosition(ccp(230 * scaleSize, 430 * scaleSize));
    this->addChild(scoreLabel);
    
    gameTime = 0;
    
    // タッチモードを設定する
	this->setTouchMode(kCCTouchesOneByOne);

	// タッチを有効にする
	this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(GameScene::gameTimer), 3);
    return true;
}


void GameScene::gameTimer(float time)
{
    gameTime += time;
//    CCString* timeString = CCString::createWithFormat("%2.0f秒", gameTime);
//    CCLog("%s",timeString->getCString());

    //初期化
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("alpha.png");
    touchArea->setTexture(pTexture);
    touchFlag = false;
    
    // 0-15の乱数を求める
    int randNum = arc4random() % 16;
    
    // マスに当てはめる
    areaPos = ccp(floor(randNum / 4), randNum % 4);
    CCPoint pos = setPanelPosition(areaPos);
    
    touchArea->setPosition(pos);
    pTexture = CCTextureCache::sharedTextureCache()->addImage("touchArea.png");
    touchArea->setTexture(pTexture);
    
//    if(gameTime > 5) {
//        this->pauseSchedulerAndActions();
//        this->resumeSchedulerAndActions();
//    }
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //タッチした座標を取得
    CCPoint location =pTouch->getLocation();
    CCPoint pos = getPanelPosition(location);
    
    //タッチした場所と光っている場所が同じなら得点を加算し、フラグをtrueにする
    if (pos.equals(areaPos) && touchFlag == false) {
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("alpha.png");
        touchArea->setTexture(pTexture);
        score += 10;
        str = CCString::createWithFormat("Score : %7d", score);
        scoreLabel->setString(str->getCString());
        touchFlag = true;
    } else {
        if (score >= 10)
        score -= 10;
        str = CCString::createWithFormat("Score : %7d", score);
        scoreLabel->setString(str->getCString());
    }

    CCPoint realPos = setPanelPosition(pos);
    highLight->setPosition(ccp(realPos.x, realPos.y));
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("highLight.png");
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
    //ポジションからx, yを求め返戻
    float tmpX = position.x / scaleSize;
    float tmpY = position.y / scaleSize;
    int x = floor((tmpX - basePositionX + itemSpace) / (itemSize + itemSpace));
    int y = floor((tmpY - basePositionY + itemSpace) / (itemSize + itemSpace));

    if (tmpX < basePositionX ||
        tmpX > basePositionX + (itemSpace * 3) + (itemSize * 4)) {
        return ccp(-1, -1);
    }
    if (tmpY < basePositionY ||
        tmpY > basePositionY + (itemSpace * 3) + (itemSize * 4)) {
        return ccp(-1, -1);
    }

    for (int i = 0; i < itemNum; i++) {
        float spaceX = basePositionX + (itemSize * (i + 1)) + (itemSpace * i);
        float spaceY = basePositionY + (itemSize * (i + 1)) + (itemSpace * i);
        if (tmpX > spaceX && tmpX < spaceX + itemSpace) {
            return ccp(-1, -1);
        }

        if (tmpY > spaceY && tmpY < spaceY + itemSpace) {
            return ccp(-1, -1);
        }
    }
    return ccp(x, y);
}

CCPoint GameScene::setPanelPosition(CCPoint position)
{
    //ポジションからx, yを求め返戻
    int x = (baseX + (itemSpace * (position.x)) + (itemSize * position.x)) * scaleSize;
    int y = (baseY + (itemSpace * (position.y)) + (itemSize * position.y)) * scaleSize;
    CCLog("pos : %d, %d", x, y);

    return ccp(x, y);
}
