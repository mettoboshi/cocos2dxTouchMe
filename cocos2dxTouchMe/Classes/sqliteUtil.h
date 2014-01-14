//
//  sqliteUtil.h
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/12/13.
//
//

#ifndef __cocos2dxTouchMe__sqliteUtil__
#define __cocos2dxTouchMe__sqliteUtil__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "sqlite3.h"

class sqliteUtil {
public:
  bool init();
  bool doSelect();
  bool doInsert();

  bool createTable();
  bool dbtest();
  sqlite3 *testDB = NULL;
  char* errMsg = NULL;
private:
  int dbOpen(sqlite3** db);
};

#endif /* defined(__cocos2dxTouchMe__sqliteUtil__) */
