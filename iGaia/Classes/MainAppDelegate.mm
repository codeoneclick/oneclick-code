
#import "MainAppDelegate.h"
#import "MainMenuViewController.h"
#import "GameViewController.h"

@implementation MainAppDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pWindow = [[UIWindow alloc] initWithFrame: screenBounds];
    GameViewController *vc = [GameViewController new];
    [m_pWindow setRootViewController:vc];
    [m_pWindow makeKeyAndVisible];
}  


@end
