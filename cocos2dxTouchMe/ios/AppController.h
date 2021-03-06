//
//  cocos2dxTouchMeAppController.h
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/09.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import "NADView.h"

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate, NADViewDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    NADView *nadView;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

- (void)showAdView;

@end