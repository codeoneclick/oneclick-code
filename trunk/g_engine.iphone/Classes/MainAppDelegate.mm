#import "MainAppDelegate.h"
#import "GameViewController.h"

@implementation MainAppDelegate

/*- (void) applicationDidFinishLaunching: (UIApplication*) application
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_window = [[UIWindow alloc] initWithFrame: screenBounds];
    [m_window makeKeyAndVisible];
}*/

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pWindow = [[UIWindow alloc] initWithFrame: screenBounds];
    GameViewController *vc = [[GameViewController alloc] init];
    [m_pWindow setRootViewController:vc];
    [vc release];
    [m_pWindow makeKeyAndVisible];
}  

- (void) dealloc
{
    [m_pWindow release];
    [super dealloc];
}

@end
