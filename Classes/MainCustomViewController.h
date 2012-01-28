//
//  MainCustomViewController.h
//  gEngine
//
//  Created by sergey.sergeev on 1/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "GLView.h"

@protocol MainCustomViewControllerDelegate <NSObject>
- (void)onSampleTouch:(NSInteger)index;

@end

@interface MainCustomViewController : UIView
@property(nonatomic, retain) GLView* mainOpenGLView;
@property(nonatomic, retain) UIScrollView*   samplesScrollView;
@property(nonatomic, retain) NSMutableArray* samplesArray;
@property(nonatomic, retain) UIScrollView*   modelsScrollView;
@property(nonatomic, retain) NSMutableArray* modelsArray;
@property(nonatomic, retain) id<MainCustomViewControllerDelegate> delegate;
@property(nonatomic, assign) NSInteger selectedSample;
@property(nonatomic, assign) NSInteger selectedModel;
@property(nonatomic, assign) NSInteger switchType;

- (void)initWithSamples:(NSArray*)elements;
- (void)initWithModels:(NSArray*)elements;

- (void)startFadeOut;
- (void)endFadeOut;
@end
