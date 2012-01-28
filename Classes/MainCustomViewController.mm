//
//  MainCustomViewController.m
//  gEngine
//
//  Created by sergey.sergeev on 1/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MainCustomViewController.h"

@implementation MainCustomViewController
@synthesize samplesScrollView;
@synthesize samplesArray;
@synthesize modelsScrollView;
@synthesize modelsArray;
@synthesize delegate;
@synthesize selectedSample;
@synthesize selectedModel;
@synthesize mainOpenGLView;
@synthesize switchType;

- (void)dealloc
{
    [super dealloc];
    [samplesScrollView release];
    [samplesArray release];
}

- (void) initCommon:(CGRect)frame 
{
    self.mainOpenGLView = [[GLView alloc] initWithFrame: frame];
    [self addSubview: self.mainOpenGLView];
    
    self.samplesScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, 48.0)];
    [self.samplesScrollView setShowsHorizontalScrollIndicator:NO];
    [self.samplesScrollView setShowsVerticalScrollIndicator:NO];
    self.samplesScrollView.backgroundColor = [UIColor blackColor];
    [self addSubview:self.samplesScrollView]; 
    self.samplesArray = [[NSMutableArray alloc] init];
    
    self.modelsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 48, frame.size.width, 48.0)];
    [self.modelsScrollView setShowsHorizontalScrollIndicator:NO];
    [self.modelsScrollView setShowsVerticalScrollIndicator:NO];
    self.modelsScrollView.backgroundColor = [UIColor blackColor];
    [self addSubview:self.modelsScrollView]; 
    self.modelsArray = [[NSMutableArray alloc] init];
}

- (id) initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self initCommon:frame];
    }
    return self;
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void) initWithSamples:(NSArray *)elements
{
    NSInteger iSamplesCount = [self.samplesArray count];
    for(NSInteger index = 0; index < iSamplesCount; ++index)
    {
        UIButton* pElement = [self.samplesArray objectAtIndex:index];
        [pElement removeFromSuperview];
    }
    [self.samplesArray removeAllObjects];
    
    NSInteger iElementsCount = [elements count];
    CGFloat fScrollOffset = 0.0;
    for(NSInteger index = 0; index < iElementsCount; index++)
    {
        NSString* pElementTitle = [[elements objectAtIndex:index] uppercaseString]; 
        CGSize stringSize = [pElementTitle sizeWithFont:[UIFont boldSystemFontOfSize:18]];
        UIButton* pButton = [[UIButton alloc] initWithFrame:CGRectMake(fScrollOffset, 0, stringSize.width + 20.0, self.samplesScrollView.frame.size.height)];
        [pButton setBackgroundColor:[UIColor blackColor]];
        [pButton setTitle:pElementTitle forState:UIControlStateNormal];
        [pButton.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pButton.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pButton addTarget:self action:@selector(onSampleTouch:) forControlEvents:UIControlEventTouchUpInside];
        [self.samplesArray addObject:pButton];
        [self.samplesScrollView addSubview:pButton];
        fScrollOffset += pButton.frame.size.width;
        [pButton release];
    }
    [self.samplesScrollView setContentSize:CGSizeMake(fScrollOffset, self.samplesScrollView.frame.size.height)];
}

- (void)onSampleTouch:(UIButton*)button
{
    NSInteger index = [self.samplesArray indexOfObject:button];
    NSInteger iSamplesCount = [self.samplesArray count];
    for(NSInteger index = 0; index < iSamplesCount; ++index)
    {
        UIButton* pElement = [self.samplesArray objectAtIndex:index];
        pElement.enabled = YES;
        [pElement setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
    button.enabled = NO;
    [button setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
    [self.delegate onSampleTouch:index];
    self.selectedSample = index;
    self.switchType = 0;
    [self startFadeOut];
}

- (void) initWithModels:(NSArray *)elements
{
    NSInteger iModelsCount = [self.modelsArray count];
    for(NSInteger index = 0; index < iModelsCount; ++index)
    {
        UIButton* pElement = [self.modelsArray objectAtIndex:index];
        [pElement removeFromSuperview];
    }
    [self.modelsArray removeAllObjects];
    
    NSInteger iElementsCount = [elements count];
    CGFloat fScrollOffset = 0.0;
    for(NSInteger index = 0; index < iElementsCount; index++)
    {
        NSString* pElementTitle = [[elements objectAtIndex:index] uppercaseString]; 
        CGSize stringSize = [pElementTitle sizeWithFont:[UIFont boldSystemFontOfSize:18]];
        UIButton* pButton = [[UIButton alloc] initWithFrame:CGRectMake(fScrollOffset, 0, stringSize.width + 20.0, self.modelsScrollView.frame.size.height)];
        [pButton setBackgroundColor:[UIColor blackColor]];
        [pButton setTitle:pElementTitle forState:UIControlStateNormal];
        [pButton.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pButton.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pButton addTarget:self action:@selector(onModelTouch:) forControlEvents:UIControlEventTouchUpInside];
        [self.modelsArray addObject:pButton];
        [self.modelsScrollView addSubview:pButton];
        fScrollOffset += pButton.frame.size.width;
        [pButton release];
    }
    [self.modelsScrollView setContentSize:CGSizeMake(fScrollOffset, self.modelsScrollView.frame.size.height)];
}

- (void)onModelTouch:(UIButton*)button
{
    NSInteger index = [self.modelsArray indexOfObject:button];
    NSInteger iModelsCount = [self.modelsArray count];
    for(NSInteger index = 0; index < iModelsCount; ++index)
    {
        UIButton* pElement = [self.modelsArray objectAtIndex:index];
        pElement.enabled = YES;
        [pElement setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
    button.enabled = NO;
    [button setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
    self.selectedModel = index;
    self.switchType = 1;
    [self startFadeOut];
}

- (void)startFadeOut
{
    [UIView beginAnimations:NULL context:NULL];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(endFadeOut)];
    [self.mainOpenGLView setAlpha:0];
    [UIView commitAnimations]; 
}


- (void)endFadeOut
{
    [UIView beginAnimations:NULL context:NULL];
    [UIView setAnimationDuration:0.5];
    [self.mainOpenGLView setAlpha:1];
    if(self.switchType == 0)
    {
        [self.mainOpenGLView Set_Effect:self.selectedSample];
    }
    else
    {
        [self.mainOpenGLView Set_Model:self.selectedModel];
    }
    [UIView commitAnimations]; 
}



@end
