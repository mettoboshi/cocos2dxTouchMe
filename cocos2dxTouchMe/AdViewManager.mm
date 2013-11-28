//
//  AdViewManager.mm
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/26.
//
//
// AdViewManager.mm

#import "AdViewManager.h"
#import "AppController.h"

void AdViewManager::showAdView()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController showAdView];
}
