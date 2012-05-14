//
//  CInGameMenu.m
//  iGaia
//
//  Created by code_oneclick on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "CInGameMenu.h"
#include "CWorld.h"
#include "CJoystick.h"

@implementation CInGameMenu
@synthesize m_pGLView;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        NSInteger iBtnWidth = 64;
        NSInteger iBtnHeight = 32;
        NSInteger iBtnXOffset = 8;
        NSInteger iBtnYOffset = 8;
        NSInteger iBtnBetweenOffset = 16;
        
        NSInteger iScrollViewHeight = 128;
        
        /*UIImage* btnImage = [UIImage imageNamed:@"btn.png"];
        UIButton* btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.origin.x + iBtnXOffset, frame.origin.y + iBtnYOffset, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_LEFT_TRACK_INC];
        [self addSubview:btn];
        
        btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.origin.x + iBtnXOffset, frame.origin.y + iBtnYOffset + iBtnBetweenOffset * 1 + iBtnHeight, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_LEFT_TRACK_NONE];
        [self addSubview:btn];
        
        btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.origin.x + iBtnXOffset, frame.origin.y + iBtnYOffset + iBtnBetweenOffset * 2 + iBtnHeight * 2, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_LEFT_TRACK_DEC];
        [self addSubview:btn];
        
        btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.size.width - iBtnXOffset - iBtnWidth, frame.origin.y + iBtnYOffset, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_RIGHT_TRACK_INC];
        [self addSubview:btn];
        
        btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.size.width - iBtnXOffset - iBtnWidth, frame.origin.y + iBtnYOffset + iBtnBetweenOffset * 1 + iBtnHeight, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_RIGHT_TRACK_NONE];
        [self addSubview:btn];
        
        btn = [[UIButton alloc] initWithFrame:CGRectMake(frame.size.width - iBtnXOffset - iBtnWidth, frame.origin.y + iBtnYOffset + iBtnBetweenOffset * 2 + iBtnHeight * 2, iBtnWidth, iBtnHeight)];
        [btn setBackgroundImage:btnImage forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(OnMoveBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [btn setTitle:@"" forState:UIControlStateNormal];
        [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
        [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:12]];
        [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [btn.titleLabel setTextAlignment:UITextAlignmentCenter];
        [btn setTag:k_MOVE_RIGHT_TRACK_DEC];
        [self addSubview:btn];*/
        
        CJoystick* pJoystick = [[CJoystick alloc] initWithFrame:CGRectMake(0, frame.size.height - 128, 128, 128)];
        [self addSubview:pJoystick];
        
        /*UIScrollView* leftTrackScroll = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 64, iScrollViewHeight)];
        [leftTrackScroll setPagingEnabled:YES];
        [leftTrackScroll setShowsHorizontalScrollIndicator:NO];
        [leftTrackScroll setShowsVerticalScrollIndicator:NO];
        [leftTrackScroll setBackgroundColor:[UIColor clearColor]];
        leftTrackScroll.delegate = self;
        [leftTrackScroll setTag:k_SCROLL_LEFT_TRACK];
        [leftTrackScroll setContentSize:CGSizeMake(64, iScrollViewHeight * 3)];
        [leftTrackScroll setContentOffset:CGPointMake(0, iScrollViewHeight)];
        [self addSubview:leftTrackScroll];
        
        UIButton* pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"INC" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [leftTrackScroll addSubview:pElement];
        
        pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, iScrollViewHeight, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"NULL" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [leftTrackScroll addSubview:pElement];
        
        pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, iScrollViewHeight * 2, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"DEC" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [leftTrackScroll addSubview:pElement];
        
        UIScrollView* rightTrackScroll = [[UIScrollView alloc] initWithFrame:CGRectMake(frame.size.width - 64, 0, 64, iScrollViewHeight)];
        [rightTrackScroll setPagingEnabled:YES];
        [rightTrackScroll setShowsHorizontalScrollIndicator:NO];
        [rightTrackScroll setShowsVerticalScrollIndicator:NO];
        [rightTrackScroll setBackgroundColor:[UIColor redColor]];
        rightTrackScroll.delegate = self;
        [rightTrackScroll setTag:k_SCROLL_RIGHT_TRACK];
        [rightTrackScroll setContentSize:CGSizeMake(64, iScrollViewHeight * 3)];
        [rightTrackScroll setContentOffset:CGPointMake(0, iScrollViewHeight)];
        [self addSubview:rightTrackScroll];
        
        pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"INC" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [rightTrackScroll addSubview:pElement];
        
        pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, iScrollViewHeight, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"NULL" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [rightTrackScroll addSubview:pElement];
        
        pElement = [[UIButton alloc] initWithFrame:CGRectMake(0, iScrollViewHeight * 2, 64, iScrollViewHeight)];
        [pElement.titleLabel setFont:[UIFont boldSystemFontOfSize:18]];
        [pElement.titleLabel setTextColor:[UIColor whiteColor]];
        [pElement setTitle:@"DEC" forState:UIControlStateNormal];
        [pElement setBackgroundColor:[UIColor clearColor]];
        [pElement.titleLabel setTextAlignment:UITextAlignmentCenter];
        [pElement setBackgroundImage:[UIImage imageNamed:@"Treads.png"] forState:UIControlStateNormal];
        [rightTrackScroll addSubview:pElement];*/
    }
    return self;
}

- (void)OnMoveBtnAction:(UIButton *)sender
{
    switch (sender.tag)
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
    }
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    /*float fTrackOffset = (scrollView.contentOffset.y / 256.0f) - 0.5f;
    NSLog(@"[scrollViewDidEndDecelerating:(UIScrollView *)scrollView] OFFSET : %f", fTrackOffset);
    
    if(scrollView.tag == k_SCROLL_LEFT_TRACK)
    {
        CWorld::Instance()->Get_PlayerCharacterController()->Set_LeftTrackMoveOffset(fTrackOffset);
    }
    else if(scrollView.tag == k_SCROLL_RIGHT_TRACK)
    {
        CWorld::Instance()->Get_PlayerCharacterController()->Set_RightTrackMoveOffset(fTrackOffset);
    }*/
    
    if(m_pGLView != nil)
    {
        [m_pGLView drawView:nil];
    }
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    CGFloat fOffset = scrollView.contentOffset.y;
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
    }
}

@end
