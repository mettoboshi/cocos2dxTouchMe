//
//  sqliteUtil.cpp
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/12/13.
//
//

#include "sqlite3.h"
#include "sqliteUtil.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

bool sqliteUtil::init() {
  
  sqlite3 *testDB = NULL;
  char* errMsg = NULL;
  string sqlstr;
  int result;

  result = dbOpen(&testDB);
  CCLog("open : %d, sqlite_OK : %d", result, SQLITE_OK);
//  string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
//  dbPath.append("Test.db");
  
//  result = sqlite3_open(dbPath.c_str(),&testDB);
  if (result != SQLITE_OK){
    CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
  }else{
    CCLOG("OK! %d, %s",result,errMsg);
  }
  
  return true;
}

int sqliteUtil::dbOpen(sqlite3 **db) {
  std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
//  std::string dbname = "Test.db";
//  CCLog("%s", dbname.c_str());
  path.append("resource.db");
  return sqlite3_open(path.c_str(), db);
}

bool sqliteUtil::doSelect() {
  sqlite3 *testDB = NULL;
  char* errMsg = NULL;

  string sqlstr;
  int result;

  result = dbOpen(&testDB);

  //select
  sqlstr="select * from MyTable_1 order by id desc";
  sqlite3_stmt *stmt = NULL;
  
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

bool sqliteUtil::doInsert() {
  sqlite3 *testDB = NULL;
  char* errMsg = NULL;
  
  string sqlstr;
  int result;
  
  result = dbOpen(&testDB);

  //insert
  sqlstr="insert into MyTable_1( name ) values ( 'いちご' ) ";
  result = sqlite3_exec( testDB, sqlstr.c_str() , NULL, NULL, &errMsg );

  if(result != SQLITE_OK ) {
    CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
  }
  
  return true;
}


bool sqliteUtil::createTable() {
  //sqlite3のテスト
  sqlite3 *db = NULL;
  char* errMsg = NULL;
  string sqlstr;
  int result;
  
  string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
  dbPath.append("Test.db");
  
  result = sqlite3_open(dbPath.c_str(),&testDB);
  if (result != SQLITE_OK){
    CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
  }else{
    CCLOG("OK! %d, %s",result,errMsg);
  }
    
  // 読み書きファイルパスの表示
  CCLog("%s",dbPath.c_str());
  
  result=sqlite3_exec( testDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );
   
  if( result != SQLITE_OK ) {
    CCLog( "失敗　:%d ，原因:%s\n" , result, errMsg );
  }
    
  return true;
}

bool sqliteUtil::dbtest() {

    //sqlite3のテスト
    sqlite3 *testDB = NULL;
    char* errMsg = NULL;
    string sqlstr;
    int result;
    string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("Test.db");

    result = sqlite3_open(dbPath.c_str(),&testDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
    }else{
        CCLOG("OK! %d, %s",result,errMsg);
    }

    // 読み書きファイルパスの表示
    CCLog("%s",dbPath.c_str());

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