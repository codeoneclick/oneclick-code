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
    m_bIsDestroyed = false;
    m_fMoveSpeed = 0.1f;
}

CBullet::~CBullet(void)
{
    
}

void CBullet::Load(void)
{
    m_pFireEmmiter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitter();
    m_pFireEmmiter->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pFireEmmiter->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pFireEmmiter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pFireEmmiter->Set_Position(glm::vec3(0.0f, 0.33f, 0.0f));
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

void CBullet::_MoveForward(void)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed, m_vPosition.z + cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed);
    int iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    if(/*fHeight > m_vPosition.y && */(m_vPosition.x < 0.0f || m_vPosition.z > iWidth || m_vPosition.z < 0.0f || m_vPosition.z > iHeight))
    {
        m_bIsDestroyed = true;
    }
    m_vPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
}

void CBullet::_SelfDestroy(void)
{
    
}

void CBullet::Update(void)
{
    if(!m_bIsDestroyed)
    {
        _MoveForward();
    }
}








