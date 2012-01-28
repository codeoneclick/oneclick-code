#import "MainAppDelegate.h"

@implementation MainAppDelegate


- (void) applicationDidFinishLaunching: (UIApplication*) application
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    
    m_window = [[UIWindow alloc] initWithFrame: screenBounds];
    
    customController = [[MainCustomViewController alloc] initWithFrame:screenBounds];
    NSArray* samplesArray = [[NSArray alloc] initWithObjects:@"SOLID MODEL",@"TEXTURE MODEL",@"LAMBERT MODEL",@"PHONG MODEL",@"CELL SHADING MODEL",@"GOOCH MODEL",@"RIM LIGHT MODEL",nil];
    [customController initWithSamples:samplesArray];
    NSArray* modelsArray = [[NSArray alloc] initWithObjects:@"MESH ZEALOT",@"MESH HYDRALISK",@"MESH SCV", nil];
    [customController initWithModels:modelsArray];

    customController.delegate = self;
    [m_window addSubview:customController];
    [m_window makeKeyAndVisible];
}

- (void) onSampleTouch:(NSInteger)index
{

}

- (void) dealloc
{
    [m_window release];
    [super dealloc];
}

@end
