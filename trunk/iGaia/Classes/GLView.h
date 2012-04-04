//#import "IRenderiniGaia.hpp"
#import <QuartzCore/QuartzCore.h>
#include "CGame.h"

@interface GLView : UIView {
@private
    EAGLContext* m_context;
    float m_fTime;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@end
