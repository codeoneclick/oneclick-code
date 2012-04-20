//
//  CCharacterControllerEnemy.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCharacterControllerEnemy.h"
#include "CWorld.h"

CCharacterControllerEnemy::CCharacterControllerEnemy(void)
{
    m_pBodyModel = NULL;
    m_pTowerModel = NULL;
    m_pLeftTrackModel = NULL;
    m_pRightTrackModel = NULL;
    
    m_fMaxMoveSpeed = 0.05f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.0f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 1.0f;
}

CCharacterControllerEnemy::~CCharacterControllerEnemy(void)
{
    
}

void CCharacterControllerEnemy::Load(void)
{
    m_pBodyModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("base_model.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pBodyModel->Set_Texture("model_01.pvr");
    m_pBodyModel->Set_Scale(glm::vec3(0.01f, 0.01f, 0.01f));
    m_pBodyModel->Set_Shader(IResource::E_SHADER_UNIT);
    m_pBodyModel->Create_BoundingBox();
    m_pBodyModel->Set_NormalDepth(true);
    
    m_pTowerModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("tower_model.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pTowerModel->Set_Texture("model_01.pvr");
    m_pTowerModel->Set_Scale(glm::vec3(0.01f, 0.01f, 0.01f));
    m_pTowerModel->Set_Shader(IResource::E_SHADER_UNIT);
    m_pTowerModel->Create_BoundingBox();
    m_pTowerModel->Set_NormalDepth(true);
    
    
    m_pLeftTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("left_track_model.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pLeftTrackModel->Set_Texture("model_01.pvr");
    m_pLeftTrackModel->Set_Scale(glm::vec3(0.01f, 0.01f, 0.01f));
    m_pLeftTrackModel->Set_Shader(IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pLeftTrackModel->Create_BoundingBox();
    m_pLeftTrackModel->Set_NormalDepth(true);
    
    m_pRightTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("right_track_model.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pRightTrackModel->Set_Texture("model_01.pvr");
    m_pRightTrackModel->Set_Scale(glm::vec3(0.01f, 0.01f, 0.01f));
    m_pRightTrackModel->Set_Shader(IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pRightTrackModel->Create_BoundingBox();
    m_pRightTrackModel->Set_NormalDepth(true);
    
    CSceneMgr::Instance()->AddEventListener(m_pBodyModel, CEventMgr::E_EVENT_TOUCH);
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_CollisionModelAsVehicle(m_pBodyModel, 2000, glm::vec3(2.0f, 2.0f, 2.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3(-1.0f, 1.0f,  1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3(-1.0f, 1.0f, -1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3( 1.0f, 1.0f, -1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3( 1.0f, 1.0f,  1.0f));
    m_pBodyModel->Set_DelegateTarget(this);
    m_pBodyModel->Add_Delegate(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_Delegate(this);
}

void CCharacterControllerEnemy::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Position(_vPosition);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Position(_vPosition);
    }
    if(m_pLeftTrackModel != NULL)
    {
        m_pLeftTrackModel->Set_Position(_vPosition);
    }
    if(m_pRightTrackModel != NULL)
    {
        m_pRightTrackModel->Set_Position(_vPosition);
    }
    m_vPosition = _vPosition;
}

void CCharacterControllerEnemy::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Rotation(_vRotation);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Rotation(_vRotation);
    }
    if(m_pLeftTrackModel != NULL)
    {
        m_pLeftTrackModel->Set_Rotation(_vRotation);
    }
    if(m_pRightTrackModel != NULL)
    {
        m_pRightTrackModel->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}

void CCharacterControllerEnemy::Set_Light(ILight *_pLight)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Light(_pLight);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Light(_pLight);
    }
    if(m_pLeftTrackModel != NULL)
    {
        m_pLeftTrackModel->Set_Light(_pLight);
    }
    if(m_pRightTrackModel != NULL)
    {
        m_pRightTrackModel->Set_Light(_pLight);
    }
}

void CCharacterControllerEnemy::OnTouchEvent(IDelegate* _pDelegateOwner)
{

}

void CCharacterControllerEnemy::OnPhysicEvent(INode* _pNode, glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale)
{

}

void CCharacterControllerEnemy::Update(void)
{
    static float fOffsetValue = 0.0f;
    fOffsetValue += 0.1f;
    glm::vec2 vTexCoordOffset = glm::vec2(0.0, fOffsetValue);
    m_pLeftTrackModel->Set_TexCoordOffset(vTexCoordOffset);
    m_pRightTrackModel->Set_TexCoordOffset(vTexCoordOffset);
    
    switch (m_eLeftTrackState)
    {
        case E_CHARACTER_CONTROLLER_STATE_NONE:
        {
            if(m_fLeftTrackMoveSpeed > 0.0f)
            {
                m_fLeftTrackMoveSpeed -= m_fMoveAcceleration;
            }
            else if(m_fLeftTrackMoveSpeed < 0.0f)
            {
                m_fLeftTrackMoveSpeed += m_fMoveAcceleration;
            }
        }
            break;
        case E_CHARACTER_CONTROLLER_STATE_INC_MOVE:
            if(m_fLeftTrackMoveSpeed < m_fMaxMoveSpeed)
            {
                m_fLeftTrackMoveSpeed += m_fMoveAcceleration;
            }
            break;
        case E_CHARACTER_CONTROLLER_STATE_DEC_MOVE:
            if(m_fLeftTrackMoveSpeed > -m_fMaxMoveSpeed)
            {
                m_fLeftTrackMoveSpeed -= m_fMoveAcceleration;
            }
            break;
        default:
            break;
    }
    
    switch (m_eRightTrackState)
    {
        case E_CHARACTER_CONTROLLER_STATE_NONE:
        {
            if(m_fRightTrackMoveSpeed > 0.0f)
            {
                m_fRightTrackMoveSpeed -= m_fMoveAcceleration;
            }
            else if(m_fRightTrackMoveSpeed < 0.0f)
            {
                m_fRightTrackMoveSpeed += m_fMoveAcceleration;
            }
        }
            break;
        case E_CHARACTER_CONTROLLER_STATE_INC_MOVE:
            if(m_fRightTrackMoveSpeed < m_fMaxMoveSpeed)
            {
                m_fRightTrackMoveSpeed += m_fMoveAcceleration;
            }
            break;
        case E_CHARACTER_CONTROLLER_STATE_DEC_MOVE:
            if(m_fRightTrackMoveSpeed > -m_fMaxMoveSpeed)
            {
                m_fRightTrackMoveSpeed -= m_fMoveAcceleration;
            }
            break;
        default:
            break;
    }
    
    m_fMoveSpeed = m_fLeftTrackMoveSpeed + m_fRightTrackMoveSpeed;
    
    if(m_fMoveSpeed > 0.0f)
    {
        MoveForward();
    }
    else if (m_fMoveSpeed < 0.0f)
    {
        MoveBackward();
    }
    
    if(m_fLeftTrackMoveSpeed > m_fRightTrackMoveSpeed)
    {
        SteerLeft();
    }
    else if(m_fRightTrackMoveSpeed > m_fLeftTrackMoveSpeed)
    {
        SteerRight();
    }
    
    m_vPosition.y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValueAtPoint(m_vPosition.x, m_vPosition.z);
    Set_Position(m_vPosition);
    glm::vec2 vRotationOnHeightMap = _Get_RotationOnHeightmap(m_vPosition);
    m_vRotation.x = -glm::degrees(vRotationOnHeightMap.x);
    m_vRotation.z = glm::degrees(vRotationOnHeightMap.y);
    Set_Rotation(m_vRotation);
    
    m_pTowerModel->Set_Rotation(glm::vec3(0.0f, fOffsetValue, 0.0f));
}




