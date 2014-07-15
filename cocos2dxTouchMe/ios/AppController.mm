//
//  cocos2dxTouchMeAppController.mm
//  cocos2dxTouchMe
//
//  Created by FUJITA YASUO on 2013/11/09.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "sqlite3.h"

#import "RootViewController.h"

@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

   /* Add 20140113 */
   sqlite3* db;
  
   NSString* work_path;
   NSString* database_filename;
   
   NSString* database_path;
   NSString* template_path;
   
   // データベース名
   database_filename = @"resource.db";
   
   NSArray* paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
   work_path = [paths objectAtIndex:0];
  
  NSLog(@"work_path = %@", work_path);
  
   // データベースファイルのパスを取得します。
   database_path = [NSString stringWithFormat:@"%@/%@", work_path, database_filename];
   
   // 文書フォルダーにデータベースファイルが存在しているかを確認します。
   NSFileManager* manager = [NSFileManager defaultManager];
   
   if (![manager fileExistsAtPath:database_path]){
   NSError* error = nil;
   
   // 文書フォルダーに存在しない場合は、データベースの複製元をバンドルから取得します。
   template_path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:database_filename];
   
   // バンドルから取得したデータベースファイルを文書フォルダーにコピーします。
   if (![manager copyItemAtPath:template_path toPath:database_path error:&error])
   {
   // データベースファイルのコピーに失敗した場合の処理です。
   }
   }
   
   // 文書フォルダーに用意されたデータベースファイルを開きます。
   if (sqlite3_open([database_path UTF8String], &db) == SQLITE_OK){
   // データベースファイルを SQLite で開くことに成功しました。
   }
   /* add end */
  
    cocos2d::CCApplication::sharedApplication()->run();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

// AppController.mm

- (void)showAdView
{
    if (!nadView) {
        
        CGRect frame = CGRectMake(0.f, 518.f, NAD_ADVIEW_SIZE_320x50.width, NAD_ADVIEW_SIZE_320x50.height);
        
        // NADView の作成
        nadView = [[NADView alloc] initWithFrame:frame];
        [nadView setNendID:@"a6eca9dd074372c898dd1df549301f277c53f2b9" spotID:@"3172"];
        [nadView setDelegate:self];
        
        [viewController.view addSubview:nadView];
        [nadView load];
    }
}

// 広告のロードが完了した時に実行される
- (void)nadViewDidFinishLoad:(NADView *)adView
{
    NSLog(@"%s", __FUNCTION__);
}

- (void)dealloc
{
    [window release];
    [nadView setDelegate:nil];
    [nadView release];
    
    [super dealloc];
}

@end

