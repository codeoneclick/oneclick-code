#import "GLView.h"
#import <OpenGLES/ES2/gl.h> // <-- for GL_RENDERBUFFER only
#include "CInput.h"

const bool ForceES1 = false;

@implementation GLView

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect) frame
{
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;

        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];

        if (!m_context || ForceES1) {
            api = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:api];
        }

        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }

        if (api == kEAGLRenderingAPIOpenGLES1) {
            NSLog(@"Using OpenGL ES 1.1");
        } 
        else 
        {
            NSLog(@"Using OpenGL ES 2.0");
            CGame::Instance()->Load(CGRectGetWidth(frame), CGRectGetHeight(frame));
        }

        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable: eaglLayer];
        
        
        [self drawView: nil];
        m_fTime = CACurrentMediaTime();

        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                     selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                     forMode:NSDefaultRunLoopMode];

        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter]
            addObserver:self
            selector:@selector(didRotate:)
            name:UIDeviceOrientationDidChangeNotification
            object:nil];
    }
    return self;
}

- (void) didRotate: (NSNotification*) notification
{ 
    [self drawView: nil];
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_fTime;
        m_fTime = displayLink.timestamp;
        CGame::Instance()->Update(elapsedSeconds);
    }
    CGame::Instance()->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event 
{
    NSLog(@"touchesBegan");
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_State(CInput::E_TOUCH);
        CInput::Instance()->Set_Coord(TouchLocation.x, TouchLocation.y);
        NSLog(@"position : %f, %f", TouchLocation.x, TouchLocation.y);
    }
}
- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    NSLog(@"touchesMoved");
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_Coord(TouchLocation.x, TouchLocation.y);
    }
}
- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event 
{
    NSLog(@"touchesEnded");
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_State(CInput::E_UNTOUCH);
        CInput::Instance()->Set_Coord(TouchLocation.x, TouchLocation.y);
    }
}
- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event 
{
    NSLog(@"touchesCancelled");
}

@end
