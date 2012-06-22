//
//  CBullet.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#include "CBullet.h"

CBullet::CBullet(void)
{
    m_pFireEmmiter = NULL;
    m_pExplosionEmitter = NULL;
    m_pModel = NULL;
    m_bIsDead = false;
    m_fMoveSpeed = 0.33f;
}

CBullet::~CBullet(void)
{
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pFireEmmiter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pExplosionEmitter);
}   

void CBullet::Load(void)
{
    m_pFireEmmiter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFireTrail(32, glm::vec2(0.05f), glm::vec2(0.5f), 2000, false);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pFireEmmiter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pFireEmmiter->Set_Batching(true, "fire-emitter");
}

void CBullet::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Position(_vPosition);
    }
    if(m_pFireEmmiter != NULL)
    {
        m_pFireEmmiter->Set_Position(_vPosition);
    }
    if(m_pModel != NULL)
    {
        m_pModel->Set_Position(_vPosition);
    }
    std::cout<<"[CBullet::Set_Position] Position : "<<_vPosition.x<<","<<_vPosition.y<<","<<_vPosition.z<<std::endl;
    m_vPosition = _vPosition;
}

void CBullet::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Rotation(_vRotation);
    }
    if(m_pFireEmmiter != NULL)
    {
        m_pFireEmmiter->Set_Rotation(_vRotation);
    }
    if(m_pModel != NULL)
    {
        m_pModel->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}

void CBullet::_MoveForward(void)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed, m_vPosition.z + cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed);
    int iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    if((m_vPosition.x < 0.0f || m_vPosition.x > iWidth || m_vPosition.z < 0.0f || m_vPosition.z > iHeight))
    {
        m_bIsDead = true;
    }
    m_vPosition.y = fHeight + k_BULLET_HEIGHT_OFFSET;
    m_vPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
}

void CBullet::Update(void)
{
    if(!m_bIsDead)
    {
        _MoveForward();
    }
}


