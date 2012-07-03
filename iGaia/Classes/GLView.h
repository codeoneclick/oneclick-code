//#import "IRenderiniGaia.hpp"
#import <QuartzCore/QuartzCore.h>
#include "CGame.h"

@interface GLView : UIView {
@private
    CAEAGLLayer* m_pEAGlLayer;
    EAGLContext* m_pContext;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@end
