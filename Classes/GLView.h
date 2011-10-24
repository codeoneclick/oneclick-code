#import "IRenderingEngine.hpp"
#import <QuartzCore/QuartzCore.h>
#import "CRenderEngine.h"

@interface GLView : UIView {
@private
    EAGLContext* m_context;
    IRenderingEngine* m_renderingEngine;
    float m_timestamp;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@end
