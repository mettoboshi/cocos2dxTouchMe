#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "AdViewManager.h"
#include "AppData.h"
#include "sqlite3.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
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
    
    // 背景画像の表示
    background = CCSprite::create("background.png");
    background->setPosition(ccp(160 * scaleSize,240 * scaleSize));
    this->addChild(background);

    // CCMenu
    CCMenuItemImage *easyStartItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(TitleScene::easyStart));
    CCMenuItemImage *normalStartItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(TitleScene::nomalStart));
    CCMenuItemImage *hardStartItem = CCMenuItemImage::create("start.png", "start.png",this,menu_selector(TitleScene::hardStart));

    CCMenu* menu = CCMenu::create(easyStartItem, normalStartItem, hardStartItem, NULL);
    menu->alignItemsVerticallyWithPadding(20.0f * scaleSize);
    menu->setPosition(ccp(160.0f * scaleSize, 180.0f * scaleSize));
    
    this->addChild(menu);
    AdViewManager::showAdView();
    
    
    //sqlite3のテスト
    sqlite3 *testDB = NULL;
    char* errMsg = NULL;
    std::string sqlstr;
    int result;
    std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("Test.db");
    
    result = sqlite3_open(dbPath.c_str(),&testDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
    }else{
        CCLOG("OK! %d, %s",result,errMsg);
    }
    
    // 読み書きファイルパスの表示
    CCLog("%s",dbPath.c_str());

/*
    result=sqlite3_exec( testDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );
    
    if( result != SQLITE_OK ) {
        CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
    }

    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'いちご' ) ";
    result = sqlite3_exec( testDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'ぶどう' ) ";
    result = sqlite3_exec( testDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'ばなな' ) ";
    result = sqlite3_exec( testDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
*/
    //select
    sqlstr=" select * from MyTable_1 order by id desc";
    sqlite3_stmt *stmt=NULL;

    result = sqlite3_prepare_v2(testDB, sqlstr.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = (int)sqlite3_column_int(stmt, 0);
        const char* name = (char*)sqlite3_column_text(stmt, 1);

        //        int lastNodeId = (int)sqlite3_column_int(stmt, 1);
//        char* test = (char *)sqlite3_column_text(stmt, 2);
        
        CCLog("%d, %s",id, name);
        
    }
    
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(testDB);
    
    
    return true;
}

void TitleScene::easyStart() {

    // Levelの設定
    AppData* appData = AppData::getInstance();
    appData->level = AppData::Easy;

    // Transitionの設定
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);

    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}


void TitleScene::nomalStart() {

    // Levelの設定
    AppData* appData = AppData::getInstance();
    appData->level = AppData::Normal;
    
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);

    return;
}

void TitleScene::hardStart() {

    // Levelの設定
    AppData* appData = AppData::getInstance();
    appData->level = AppData::Hard;
    
    float duration = 0.5f;
    CCScene* pScene = CCTransitionPageTurn::create(duration, GameScene::scene(), false);
    
    // GameSceneへ画面遷移
    CCDirector::sharedDirector()->replaceScene(pScene);
    
    return;
}


