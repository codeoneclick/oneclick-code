//
//  CTankHeavyBody.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTankHeavyBody.h"
#include "CSceneMgr.h"

CTankHeavyBody::CTankHeavyBody(void)
{
    m_vLeftExhaustEmitterOffset = glm::vec3(0.25f, 0.75f, -1.1f);
    m_vRightExhaustEmitterOffset = glm::vec3(-0.25f, 0.75f, -1.1f);
}

CTankHeavyBody::~CTankHeavyBody(void)
{
    
}

void CTankHeavyBody::Load(void)
{
    m_pBody = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_heavy_body.mdl", IResource::E_THREAD_BACKGROUND);
    m_pBody->Set_Texture("tank_heavy.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pBody->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pBody->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pBody->Set_Shader(CShader::E_RENDER_MODE_REFLECTION, IResource::E_SHADER_MODEL);
    m_pBody->Set_Shader(CShader::E_RENDER_MODE_REFRACTION, IResource::E_SHADER_MODEL);
    m_pBody->Create_BoundingBox();
    m_pBody->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    m_pBody->Set_RenderMode(CShader::E_RENDER_MODE_REFLECTION, true);
    m_pBody->Set_RenderMode(CShader::E_RENDER_MODE_REFRACTION, true);
    
    
    
    m_pLeftExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 1000, true);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pRightExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 1000, true);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
}

void CTankHeavyBody::Update(void)
{
    ITankBody::Update();
}