//
//  MainMenuViewController.m
//  iGaia
//
//  Created by sergey sergeev on 7/9/12.
//
//

#import "MainMenuViewController.h"
#import "GameLoadingViewController.h"
#import "GLView.h"
#include "CGameSceneMgr.h"
#include "CGameMainMenuScene.h"

@interface MainMenuViewController ()
{
    IBOutlet UIView* m_pOpenGLView;
    IBOutlet UISegmentedControl* m_pSegmentedColor;
    IBOutlet UIButton* m_pSingleGameButton;
    IBOutlet UIButton* m_pMultiGameButton;
    IBOutlet UIButton* m_pSettingsButton;
    IBOutlet UIButton* m_pScoresButton;
}
@end

//0.501961 0.501961 0 1

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
    
    m_pSingleGameButton.hidden = YES;
    m_pMultiGameButton.hidden = YES;
    m_pSettingsButton.hidden = YES;
    m_pScoresButton.hidden = YES;
    
    NSLog(@"%@", m_pSegmentedColor.tintColor);
    
    UISegmentedControl *singleGame = [[UISegmentedControl alloc] initWithItems:[NSArray arrayWithObject:@"Tutorial"]];
    singleGame.frame = m_pSingleGameButton.frame;
    [singleGame setSegmentedControlStyle:UISegmentedControlStyleBar];
    [singleGame setTintColor:[UIColor colorWithRed:0.501961 green:0.501961 blue:0.0 alpha:1.0]];
    [singleGame setMomentary:YES];
    [singleGame addTarget:self action:@selector(onSingleGamePress:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:singleGame];
    
    UISegmentedControl *multiGame = [[UISegmentedControl alloc] initWithItems:[NSArray arrayWithObject:@"Multiplayer"]];
    multiGame.frame = m_pMultiGameButton.frame;
    [multiGame setSegmentedControlStyle:UISegmentedControlStyleBar];
    [multiGame setTintColor:[UIColor colorWithRed:0.501961 green:0.501961 blue:0.0 alpha:1.0]];
    [multiGame setMomentary:YES];
    [multiGame addTarget:self action:@selector(onMultiGamePress:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:multiGame];
    
    UISegmentedControl *settingsGame = [[UISegmentedControl alloc] initWithItems:[NSArray arrayWithObject:@"Settings"]];
    settingsGame.frame = m_pSettingsButton.frame;
    [settingsGame setSegmentedControlStyle:UISegmentedControlStyleBar];
    [settingsGame setTintColor:[UIColor colorWithRed:0.501961 green:0.501961 blue:0.0 alpha:1.0]];
    [settingsGame setMomentary:YES];
    [settingsGame addTarget:self action:@selector(onSettingsPress:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:settingsGame];
    
    UISegmentedControl *scoresGame = [[UISegmentedControl alloc] initWithItems:[NSArray arrayWithObject:@"Scores"]];
    scoresGame.frame = m_pScoresButton.frame;
    [scoresGame setSegmentedControlStyle:UISegmentedControlStyleBar];
    [scoresGame setTintColor:[UIColor colorWithRed:0.501961 green:0.501961 blue:0.0 alpha:1.0]];
    [scoresGame setMomentary:YES];
    [scoresGame addTarget:self action:@selector(onScoresPress:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:scoresGame];
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

- (void)onSingleGamePress:(UISegmentedControl*)sender
{
    GameLoadingViewController* vc = [[GameLoadingViewController alloc] init];
    [self pushViewController:vc];
}

- (void)onMultiGamePress:(UISegmentedControl*)sender
{
    
}

- (void)onSettingsPress:(UISegmentedControl*)sender
{
    
}

- (void)onScoresPress:(UISegmentedControl*)sender
{
    
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
