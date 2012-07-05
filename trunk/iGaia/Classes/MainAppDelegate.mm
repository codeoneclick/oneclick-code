#import "MainAppDelegate.h"
#import "GameViewController.h"

@implementation MainAppDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pWindow = [[UIWindow alloc] initWithFrame: screenBounds];
    GameViewController *vc = [[GameViewController alloc] init];
    [m_pWindow setRootViewController:vc];
    [m_pWindow makeKeyAndVisible];
}  


@end
