#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.hpp"
#include "INode.h"
#include "CMTV.h"

#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"

static const float RevolutionsPerSecond = 1;

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
private:
    float RotationDirection() const;
    void ApplyOrtho(float maxX, float maxY) const;
    void ApplyRotation(float degrees) const;
    float m_desiredAngle;
    float m_currentAngle;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
};

IRenderingEngine* CreateRenderer2()
{
    return new RenderingEngine2();
}

/*struct Vertex {
    float Position[2];
    float Color[4];
};

// Define the positions and colors of two triangles.
const Vertex Vertices[] = {
    {{-0.5, -0.866}, {1, 1, 0.5f, 1}},
    {{0.5, -0.866},  {1, 1, 0.5f, 1}},
    {{0, 1},         {1, 1, 0.5f, 1}},
    {{-0.5, -0.866}, {0.5f, 0.5f, 0.5f}},
    {{0.5, -0.866},  {0.5f, 0.5f, 0.5f}},
    {{0, -0.4f},     {0.5f, 0.5f, 0.5f}},
};*/

RenderingEngine2::RenderingEngine2()
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

void RenderingEngine2::Initialize(int width, int height)
{
    // Create the framebuffer object and attach the color buffer.
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              m_renderbuffer);
    
    glViewport(0, 0, width, height);
    
    CShader *shader = new CShader(SimpleVertexShader,SimpleFragmentShader);
    
    m_simpleProgram = shader->Handle();//BuildProgram(SimpleVertexShader, SimpleFragmentShader);

    glUseProgram(m_simpleProgram);
    
    // Initialize the projection matrix.
    ApplyOrtho(4, 6);
    
    // Initialize rotation animation state.
    OnRotate(DeviceOrientationPortrait);
    m_currentAngle = m_desiredAngle;
    
    //CMTV *obj = new CMTV();
    //obj->Run();
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
{
    /*float a = 1.0f / maxX;
    float b = 1.0f / maxY;
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0, -1, 0,
        0, 0,  0, 1
    };*/
    
    Matrix4x4 mProjection = Orthographic(320.0f, 480.0f, -1.0f, 1.0f);
    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &mProjection.m[0]);
}

void RenderingEngine2::ApplyRotation(float degrees) const
{
    Matrix4x4 mRotation = Rotation(degrees);
    Matrix4x4 mTranslation = Translation(Vector2d(-1.0f, -1.0f));
    Matrix4x4 mScale = Scale(Vector2d(1.0f, 0.5f));
    Matrix4x4 mResult = mScale * mRotation * mTranslation;
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    glUniformMatrix4fv(modelviewUniform, 1, 0, &mResult.m[0]);
}

void RenderingEngine2::Render() const
{
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    static float currentAngle = 0.1f;
    currentAngle += 5.0f;
    ApplyRotation(currentAngle);
    
    //GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    //GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");
    
    CVertexBuffer *vb = new CVertexBuffer(4, sizeof(CVertexBuffer::SVertexVC), CVertexBuffer::VBD_V2FC4F);
    CVertexBuffer::SVertexVC *v_data = static_cast<CVertexBuffer::SVertexVC*>(vb->Source());    
    v_data[0].s_position = Vector2d(0.0f, 0.0f);
    v_data[1].s_position = Vector2d(0.0f, 32.0f);
    v_data[2].s_position = Vector2d(32.0f, 32.0f);
    v_data[3].s_position = Vector2d(32.0f, 0.0f);
    
    v_data[0].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    v_data[1].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    v_data[2].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    v_data[3].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    
    //GLsizei stride = sizeof(CVertexBuffer::SVertexVC);
    //const GLvoid* pCoords = &v_data[0].s_position.v[0];
    //const GLvoid* pColors = &v_data[0].s_color.v[0];
    
    //glEnableVertexAttribArray(positionSlot);
    //glEnableVertexAttribArray(colorSlot);
    
    //glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    //glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
    
    vb->Enable(m_simpleProgram);
    GLubyte indices[6] = { 0, 1, 2, 2, 3, 0}; 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) indices);
    vb->Disable(m_simpleProgram);
    //glDisableVertexAttribArray(positionSlot);
    //glDisableVertexAttribArray(colorSlot);
}

float RenderingEngine2::RotationDirection() const
{
    float delta = m_desiredAngle - m_currentAngle;
    if (delta == 0)
        return 0;
    
    bool counterclockwise = ((delta > 0 && delta <= 180) || (delta < -180));
    return counterclockwise ? +1 : -1;
}

void RenderingEngine2::UpdateAnimation(float timeStep)
{
    float direction = RotationDirection();
    if (direction == 0)
        return;
    
    float degrees = timeStep * 360 * RevolutionsPerSecond;
    m_currentAngle += degrees * direction;

    // Normalize the angle to [0, 360)
    if (m_currentAngle >= 360)
        m_currentAngle -= 360;
    else if (m_currentAngle < 0)
        m_currentAngle += 360;
    
    // If the rotation direction changed, then we overshot the desired angle.
    if (RotationDirection() != direction)
        m_currentAngle = m_desiredAngle;
}

void RenderingEngine2::OnRotate(DeviceOrientation orientation)
{
    float angle = 0;
    
    switch (orientation) {
        case DeviceOrientationLandscapeLeft:
            angle = 270;
            break;

        case DeviceOrientationPortraitUpsideDown:
            angle = 180;
            break;

        case DeviceOrientationLandscapeRight:
            angle = 90;
            break;
    }
    
    m_desiredAngle = angle;
}
