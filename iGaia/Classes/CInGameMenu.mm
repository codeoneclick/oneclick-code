//
//  CInGameMenu.m
//  iGaia
//
//  Created by code_oneclick on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CInGameMenu.h"
#include "CWorld.h"
#include "CJoystick.h"
#include "CSlider.h"
#include <QuartzCore/QuartzCore.h>

@implementation CInGameMenu
@synthesize m_pGLView;

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

- (void)onCameraButtonPress:(UIButton*)sender
{
    CWorld::Instance()->SwitchCameraModeToNext();
}

- (void)OnShootButtonPress:(UIButton*)sender
{
    CWorld::Instance()->Get_PlayerCharacterController()->Shoot();
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    if(m_pGLView != nil)
    {
        [m_pGLView drawView:nil];
    }
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
