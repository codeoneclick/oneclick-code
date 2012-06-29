//
//  GameViewController.m
//  iGaia
//
//  Created by sergey.sergeev on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GameViewController.h"
#import "CInGameMenu.h"

@implementation GameViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)loadView
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pGLView = [[GLView alloc] initWithFrame: screenBounds];
    self.view = m_pGLView;
    [m_pGLView release];
    m_pInGameMenu = [[CInGameMenu alloc] initWithFrame:CGRectMake(0, 0, screenBounds.size.height, screenBounds.size.width)];
    m_pInGameMenu.m_pGLView = m_pGLView;
    [self.view addSubview:m_pInGameMenu];
    
    NSMethodSignature *pMethodSignature = [self methodSignatureForSelector:@selector(onTick:)];
    NSInvocation *pInvocation = [NSInvocation invocationWithMethodSignature:pMethodSignature];
    [pInvocation setTarget:self];
    [pInvocation setSelector:@selector(onTick:)];
    NSTimer *pTimer = [NSTimer timerWithTimeInterval:1.0 invocation:pInvocation repeats:YES];
    NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
    [runLoop addTimer:pTimer forMode:NSDefaultRunLoopMode];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIDeviceOrientationLandscapeRight || interfaceOrientation == UIDeviceOrientationLandscapeLeft;
}

-(void)onTick:(NSTimer *)timer
{
    [m_pInGameMenu.m_pInfoLabel setText:[NSString stringWithFormat:@"FPS : %i, Triangles : %i", CSettings::g_iTotalFramesPerSecond, CSettings::g_iTotalTriagnlesPerFrame]];
}

@end
