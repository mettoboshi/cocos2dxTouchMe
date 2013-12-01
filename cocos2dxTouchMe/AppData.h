//
//  appData.h
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/28.
//
//

#ifndef __cocos2dxTouchMe__appData__
#define __cocos2dxTouchMe__appData__

#include <iostream>

class AppData
{
public:

    enum Level {
        Easy,
        Normal,
        Hard
    };
    
    Level level;

    static AppData* getInstance();
    
private:
    static AppData* instance;
};


#endif /* defined(__cocos2dxTouchMe__appData__) */
