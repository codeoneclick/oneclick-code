#import "MainCustomViewController.h"
@interface MainAppDelegate : NSObject <UIApplicationDelegate, MainCustomViewControllerDelegate> {
@private
    UIWindow* m_window;
    MainCustomViewController* customController;
}

@end

