//
//  CInGameMenu.m
//  iGaia
//
//  Created by code_oneclick on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include <QuartzCore/QuartzCore.h>
#include "CInGameMenu.h"
#include "CJoystick.h"
#include "CSlider.h"
#include "CSettings.h"
#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"

@implementation CInGameMenu
@synthesize m_pInfoLabel;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        CJoystick* pJoystick = [[CJoystick alloc] initWithFrame:CGRectMake(0, frame.size.height - 128, 128, 128)];
        [self addSubview:pJoystick];
        
        CSlider* pSlider = [[CSlider alloc] initWithFrame:CGRectMake(frame.size.width - 128, frame.size.height - 128, 128, 128)];
        [self addSubview:pSlider];
        
        UIButton* pCameraButton = [[UIButton alloc] initWithFrame:CGRectMake(self.frame.size.width - 69, 5, 64, 64)];
        [pCameraButton setBackgroundColor:[UIColor clearColor]];
        [pCameraButton setImage:[UIImage imageNamed:@"camera_button.png"] forState:UIControlStateNormal];
        [pCameraButton addTarget:self action:@selector(onCameraButtonPress:) forControlEvents:UIControlEventTouchUpInside];
        pCameraButton.layer.cornerRadius = 8;
        pCameraButton.clipsToBounds = YES;
        [self addSubview:pCameraButton];
        
        UIButton* pShootButton = [[UIButton alloc] initWithFrame:CGRectMake(self.frame.size.width - 96, frame.size.height - 192, 64, 64)];
        [pShootButton setBackgroundColor:[UIColor clearColor]];
        [pShootButton setBackgroundColor:[UIColor redColor]];
        [pShootButton addTarget:self action:@selector(OnShootButtonPress:) forControlEvents:UIControlEventTouchUpInside];
        pShootButton.layer.cornerRadius = 24;
        pShootButton.clipsToBounds = YES;
        [self addSubview:pShootButton];
        
        m_pInfoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, 32)];
        [m_pInfoLabel setBackgroundColor:[UIColor blackColor]];
        [m_pInfoLabel setTextColor:[UIColor whiteColor]];
        [self addSubview:m_pInfoLabel];
    }
    return self;
}

- (void)OnMoveBtnAction:(UIButton *)sender
{
    /*switch (sender.tag)
    {
        case k_MOVE_LEFT_TRACK_INC:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_INC_MOVE);
            break;
        case k_MOVE_LEFT_TRACK_NONE:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_NONE);
            break;
        case k_MOVE_LEFT_TRACK_DEC:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_DEC_MOVE);
            break;
        case k_MOVE_RIGHT_TRACK_INC:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_INC_MOVE);
            break;
        case k_MOVE_RIGHT_TRACK_NONE:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_NONE);
            break;
        case k_MOVE_RIGHT_TRACK_DEC:
            CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_DEC_MOVE);
            break;
        default:
            break;
    }*/
}

/*- (void)drawRect:(CGRect)rect
{
    [super drawRect:rect];
    //[m_pInfoLabel setText:[NSString stringWithFormat:@"FPS : %i, Triangles : %i", CSettings::g_iFramesPerSecond, CSettings::g_iTrianglesPerFrame]];
}*/

- (void)onCameraButtonPress:(UIButton*)sender
{
    static_cast<CGameInGameScene*>(CGameSceneMgr::Instance()->Get_Scene())->SwitchCameraModeToNext();
}

- (void)OnShootButtonPress:(UIButton*)sender
{
    CGameSceneMgr::Instance()->Get_Scene()->Get_PlayerCharacterController()->Shoot();
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    /*CGFloat fOffset = scrollView.contentOffset.y;
    NSInteger iMode = round(fOffset / scrollView.bounds.size.height);
    if(scrollView.tag == k_SCROLL_LEFT_TRACK)
    {
        switch (iMode)
        {
            case 0:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_INC_MOVE);
                break;
            case 1:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_NONE);
                break;
            case 2:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_DEC_MOVE);
                break;
            default:
                break;
        }
    }
    
    if(scrollView.tag == k_SCROLL_RIGHT_TRACK)
    {
        switch (iMode)
        {
            case 0:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_INC_MOVE);
                break;
            case 1:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_NONE);
                break;
            case 2:
                CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackState(CCharacterControllerPlayer::E_CHARACTER_CONTROLLER_STATE_DEC_MOVE);
                break;
            default:
                break;
        }
    }*/
}

@end
