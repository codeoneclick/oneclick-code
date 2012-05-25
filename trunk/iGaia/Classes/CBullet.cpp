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
    m_pExplosionEmitter = NULL;
    m_pShadowDecal = NULL;
    m_bIsDestroyed = false;
    m_fMoveSpeed = 0.1f;
}

CBullet::~CBullet(void)
{
    
}

void CBullet::Load(void)
{
    m_pExplosionEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitter();
    m_pExplosionEmitter->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pExplosionEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pExplosionEmitter->Set_Position(glm::vec3(0.0f, 0.33f, 0.0f));
    
    m_pShadowDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pShadowDecal->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
}

void CBullet::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Position(_vPosition);
    }
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
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

void CBullet::Update(void)
{
    if(!m_bIsDestroyed)
    {
        _MoveForward();
    }
}