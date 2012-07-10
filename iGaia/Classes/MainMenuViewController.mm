//
//  MainMenuViewController.m
//  iGaia
//
//  Created by sergey sergeev on 7/9/12.
//
//

#import "MainMenuViewController.h"
#import "GLView.h"
#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"
#include "CGameMainMenuScene.h"

@interface MainMenuViewController ()
{
    IBOutlet UIView* m_pOpenGLView;
}
@end

@implementation MainMenuViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [m_pOpenGLView addSubview:[GLView Instance]];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    m_pOpenGLView = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIDeviceOrientationLandscapeRight || interfaceOrientation == UIDeviceOrientationLandscapeLeft;
}


- (IBAction)OnTankTypeChanged:(id)sender
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene == NULL || pScene->Get_MainCharacterController() == NULL)
    {
        return;
    }
    ICharacterController* pController = pScene->Get_MainCharacterController();
    
    UISegmentedControl *pSegmentedControl = (UISegmentedControl *)sender;
    if(pSegmentedControl.selectedSegmentIndex == 0)
    {
        pController->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
        pController->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
        pController->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
    }
    else if(pSegmentedControl.selectedSegmentIndex == 1)
    {
        pController->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
        pController->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
        pController->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
    }
    else if(pSegmentedControl.selectedSegmentIndex == 2)
    {
        pController->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
        pController->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
        pController->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
    }
}

@end
