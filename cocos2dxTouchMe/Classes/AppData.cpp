//
//  appData.cpp
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/28.
//
//

#include "AppData.h"

AppData* AppData::instance = NULL;

AppData* AppData::getInstance() {

    if(instance) {
        return instance;
    }
    
    instance = new AppData();
    
    return instance;

}