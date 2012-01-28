//#import "IRenderingEngine.hpp"
#import <QuartzCore/QuartzCore.h>
#include "CGame.h"

@interface GLView : UIView {
@private
    EAGLContext* m_context;
    float m_fTime;
}

- (void) Set_Effect:(NSInteger)index;
- (void) Set_Model:(NSInteger)index;
- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@end
