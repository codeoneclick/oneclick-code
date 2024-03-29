//
//  CBullet.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#include "CBullet.h"
#include "CGameSceneMgr.h"

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
    CSceneMgr::Instance()->Remove_Model(m_pModel);
}   

void CBullet::Load(void)
{
    m_pFireEmmiter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFireTrail(36, glm::vec2(0.05f), glm::vec2(0.75f), 1000, false);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pFireEmmiter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
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
    
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene != NULL)
    {
        unsigned int iNumCharacterControllers = pScene->Get_GameCharaterControllerMgr()->Get_NumCharacterControllers();
        for(unsigned int i = 0; i < iNumCharacterControllers; ++i)
        {
            ICharacterController* pCharacterController = pScene->Get_GameCharaterControllerMgr()->Get_CharacterController(i);
        }
    }
}

void CBullet::Update(void)
{
    if(!m_bIsDead)
    {
        _MoveForward();
    }
}


