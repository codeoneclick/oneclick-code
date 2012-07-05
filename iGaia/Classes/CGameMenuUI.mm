//
//  CGameMenuUI.m
//  iGaia
//
//  Created by sergey sergeev on 7/5/12.
//
//

#include <QuartzCore/QuartzCore.h>
#import "CGameMenuUI.h"
#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"
#include "CGameMainMenuScene.h"

@implementation CGameMenuUI

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        UIButton* pUnloadButton = [[UIButton alloc] initWithFrame:CGRectMake(8, 8, 128, 32)];
        [pUnloadButton setBackgroundColor:[UIColor blackColor]];
        [pUnloadButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pUnloadButton addTarget:self action:@selector(OnUnloadScenePress:) forControlEvents:UIControlEventTouchUpInside];
        pUnloadButton.layer.cornerRadius = 8;
        pUnloadButton.clipsToBounds = YES;
        [pUnloadButton setTitle:@"UNLOAD" forState:UIControlStateNormal];
        [self addSubview:pUnloadButton];
        
        UIButton* pLoadButton = [[UIButton alloc] initWithFrame:CGRectMake(8, 48, 128, 32)];
        [pLoadButton setBackgroundColor:[UIColor blackColor]];
        [pLoadButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pLoadButton addTarget:self action:@selector(OnLoadScenePress:) forControlEvents:UIControlEventTouchUpInside];
        pLoadButton.layer.cornerRadius = 8;
        pLoadButton.clipsToBounds = YES;
        [pLoadButton setTitle:@"LOAD" forState:UIControlStateNormal];
        [self addSubview:pLoadButton];
    }
    return self;
}

- (void)OnUnloadScenePress:(UIButton*)sender
{
    CGameMainMenuScene* pScene = static_cast<CGameMainMenuScene*>(CGameSceneMgr::Instance()->Get_Scene());
    pScene->Unload();
}

- (void)OnLoadScenePress:(UIButton*)sender
{
    
}


@end
