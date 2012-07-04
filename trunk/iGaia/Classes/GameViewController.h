//
//  GameViewController.h
//  iGaia
//
//  Created by sergey.sergeev on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "CGameInGameUI.h"

@interface GameViewController : UIViewController
{
    GLView* m_pGLView;
    CGameInGameUI* m_pGameInGameUI;
}
@end
