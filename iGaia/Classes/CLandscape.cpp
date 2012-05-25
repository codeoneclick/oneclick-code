//
//  CLandscape.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLandscape.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"

CLandscape::CLandscape(void)
{
    m_iWidth = 64;
    m_iHeight = 64;
    m_pHeightMapSetter = NULL;
}

CLandscape::~CLandscape(void)
{
    
}

void CLandscape::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pMesh = m_pHeightMapSetter->Load_DataSource(_sName, m_iWidth, m_iHeight);
    
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    glm::u8vec4* pColorData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_ColorData();
    unsigned char iUniqueColorId = CSceneMgr::Instance()->Get_UniqueColorId(this);
    for(unsigned int i = 0; i < m_pMesh->Get_NumVertexes(); ++i)
    {
        pColorData[i] = glm::u8vec4(iUniqueColorId, iUniqueColorId, iUniqueColorId, 255);
    }
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->Set_Mode(GL_STREAM_DRAW);
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
    
    unsigned short* pIndexBufferData = m_pMesh->Get_IndexBufferRef()->Get_SourceData();
    unsigned int iNumIndexes = m_pMesh->Get_IndexBufferRef()->Get_NumIndexes();
    
    m_pWorkingIndexesSourceDataRef = m_pMesh->Get_IndexBufferRef()->Get_WorkingSourceDataRef();
    m_iWorkingNumIndexes = 0;
    
    m_pQuadTree = new SQuadTreeNode();
    m_pQuadTree->m_pParent = NULL;
    m_pQuadTree->m_vMaxBound = glm::vec3(m_iWidth, 64.0f, m_iHeight);
    m_pQuadTree->m_vMinBound = glm::vec3(0.0f, -64.0f, 0.0f);
    m_pQuadTree->m_iNumIndexes = iNumIndexes;
    m_pQuadTree->m_pIndexes = static_cast<unsigned short*>(malloc(m_pQuadTree->m_iNumIndexes * sizeof(unsigned short)));
    m_pQuadTree->m_pIndexesId = static_cast<unsigned short*>(malloc(m_pQuadTree->m_iNumIndexes * sizeof(unsigned short)));
    memcpy(m_pQuadTree->m_pIndexes , pIndexBufferData, m_pQuadTree->m_iNumIndexes * sizeof(unsigned short));
    memset(m_pQuadTree->m_pIndexesId, 0x0, m_pQuadTree->m_iNumIndexes * sizeof(unsigned short));
    _CreateQuadTreeNode(m_iWidth, m_pQuadTree);
}

void CLandscape::_CreateQuadTreeNode(int _iSize, CLandscape::SQuadTreeNode *_pParentNode)
{
    static int iRecurseCount = 0;
    iRecurseCount++;
    std::cout<<"[CLandscape::_CreateQuadTreeNode] Recurse Count : "<<iRecurseCount<<std::endl;
    if(_iSize <= 2)
    {
        return;
    }
    
    _pParentNode->m_pChilds = new SQuadTreeNode*[k_MAX_QUADTREE_CHILDREN];
    
    _pParentNode->m_pChilds[0] = new SQuadTreeNode();
    _pParentNode->m_pChilds[0]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[0]->m_vMinBound = glm::vec3(_pParentNode->m_vMinBound.x, _pParentNode->m_vMinBound.y, _pParentNode->m_vMinBound.z );
    _pParentNode->m_pChilds[0]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[0]);
    
    _pParentNode->m_pChilds[1] = new SQuadTreeNode();
    _pParentNode->m_pChilds[1]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[1]->m_vMinBound = glm::vec3(_pParentNode->m_vMinBound.x, _pParentNode->m_vMinBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _pParentNode->m_pChilds[1]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[1]);
    
    _pParentNode->m_pChilds[2] = new SQuadTreeNode();
    _pParentNode->m_pChilds[2]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[2]->m_vMinBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMinBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _pParentNode->m_pChilds[2]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[2]);
    
    _pParentNode->m_pChilds[3] = new SQuadTreeNode();
    _pParentNode->m_pChilds[3]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[3]->m_vMinBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMinBound.y, _pParentNode->m_vMinBound.z);
    _pParentNode->m_pChilds[3]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[3]);
    
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[0]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[1]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[2]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[3]);
}

void CLandscape::_CreateIndexBufferRefForQuadTreeNode(CLandscape::SQuadTreeNode *_pNode)
{
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    unsigned int iParentNumIndexes = _pNode->m_pParent->m_iNumIndexes;
    _pNode->m_pIndexes = static_cast<unsigned short*>(malloc(sizeof(unsigned short)));
    float fMaxY = -4096.0f;
    float fMinY =  4096.0f;
    
    unsigned int iQuadTreeNodeId = 0;
    CLandscape::SQuadTreeNode* pParentNode = _pNode->m_pParent;
    while (pParentNode != NULL)
    {
        iQuadTreeNodeId++;
        pParentNode = pParentNode->m_pParent;
    }
    
    for(unsigned int i = 0; i < iParentNumIndexes; i += 3)
    {
        if(_IsPointInBoundBox(pPositionData[_pNode->m_pParent->m_pIndexes[i + 0]], _pNode->m_vMinBound, _pNode->m_vMaxBound) ||
           _IsPointInBoundBox(pPositionData[_pNode->m_pParent->m_pIndexes[i + 1]], _pNode->m_vMinBound, _pNode->m_vMaxBound) ||
           _IsPointInBoundBox(pPositionData[_pNode->m_pParent->m_pIndexes[i + 2]], _pNode->m_vMinBound, _pNode->m_vMaxBound))
        {
            
            if(_pNode->m_pParent->m_pIndexesId[i + 0] == iQuadTreeNodeId ||
               _pNode->m_pParent->m_pIndexesId[i + 1] == iQuadTreeNodeId ||
               _pNode->m_pParent->m_pIndexesId[i + 2] == iQuadTreeNodeId)
            {
                continue;
            }
            
            _pNode->m_iNumIndexes += 3;
            _pNode->m_pIndexes = static_cast<unsigned short*>(realloc(_pNode->m_pIndexes, sizeof(unsigned short) * _pNode->m_iNumIndexes));
            
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 3] = _pNode->m_pParent->m_pIndexes[i + 0];
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 2] = _pNode->m_pParent->m_pIndexes[i + 1];
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 1] = _pNode->m_pParent->m_pIndexes[i + 2];
            
            _pNode->m_pParent->m_pIndexesId[i + 0] = iQuadTreeNodeId;
            _pNode->m_pParent->m_pIndexesId[i + 1] = iQuadTreeNodeId;
            _pNode->m_pParent->m_pIndexesId[i + 2] = iQuadTreeNodeId;
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 0]].y > fMaxY)
            {
                fMaxY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 0]].y;
            }
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 1]].y > fMaxY)
            {
                fMaxY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 1]].y;
            }
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 2]].y > fMaxY)
            {
                fMaxY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 2]].y;
            }
            
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 0]].y < fMinY)
            {
                fMinY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 0]].y;
            }
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 1]].y < fMinY)
            {
                fMinY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 1]].y;
            }
            
            if(pPositionData[_pNode->m_pParent->m_pIndexes[i + 2]].y < fMinY)
            {
                fMinY = pPositionData[_pNode->m_pParent->m_pIndexes[i + 2]].y;
            }
        }
    }
    _pNode->m_pIndexesId = static_cast<unsigned short*>(malloc(_pNode->m_iNumIndexes * sizeof(unsigned short)));
    memset(_pNode->m_pIndexesId, 0x0, _pNode->m_iNumIndexes * sizeof(unsigned short));
    _pNode->m_vMaxBound.y = fMaxY;
    _pNode->m_vMinBound.y = fMinY;
}

bool CLandscape::_IsPointInBoundBox(glm::vec3 _vPoint, glm::vec3 _vMinBound, glm::vec3 _vMaxBound)
{
    if(_vPoint.x >= _vMinBound.x &&
       _vPoint.x <= _vMaxBound.x &&
       _vPoint.y >= _vMinBound.y &&
       _vPoint.y <= _vMaxBound.y &&
       _vPoint.z >= _vMinBound.z &&
       _vPoint.z <= _vMaxBound.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CLandscape::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CLandscape::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pMesh->Get_VertexBufferRef(), m_pMesh->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CLandscape::OnTouchEvent] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Set_Touch3DPoint(vCollisionPoint);
    
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index]->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_TOUCH)
        {
            dynamic_cast<ITouchDelegate*>(m_lDelegateOwners[index])->OnTouchEvent(this);
        }
    }
}

void CLandscape::_CheckVisibleQuadTreeNode(CLandscape::SQuadTreeNode *_pNode)
{
    CFrustum* pFrustum = CSceneMgr::Instance()->Get_Frustum();
    if(_pNode->m_pChilds == NULL)
    {
        return;
    }
    
    for(unsigned int i = 0; i < k_MAX_QUADTREE_CHILDREN; i++)
    {
        int iResult = pFrustum->IsBoxInFrustum(_pNode->m_pChilds[i]->m_vMaxBound, _pNode->m_pChilds[i]->m_vMinBound);
        if(iResult == CFrustum::E_FRUSTUM_RESULT_INSIDE)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_INSIDE"<<std::endl;
            memcpy(&m_pWorkingIndexesSourceDataRef[m_iWorkingNumIndexes], _pNode->m_pChilds[i]->m_pIndexes, sizeof(unsigned short) * _pNode->m_pChilds[i]->m_iNumIndexes);
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] Indexes Nun += "<<_pNode->m_pChilds[i]->m_iNumIndexes<<std::endl;
            m_iWorkingNumIndexes += _pNode->m_pChilds[i]->m_iNumIndexes;
        }
        else if(iResult == CFrustum::E_FRUSTUM_RESULT_INTERSECT)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_INTERSECT"<<std::endl;
            if(_pNode->m_pChilds[i]->m_pChilds == NULL)
            {
                memcpy(&m_pWorkingIndexesSourceDataRef[m_iWorkingNumIndexes], _pNode->m_pChilds[i]->m_pIndexes, sizeof(unsigned short) * _pNode->m_pChilds[i]->m_iNumIndexes);
                //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] Indexes Nun += "<<_pNode->m_pChilds[i]->m_iNumIndexes<<std::endl;
                m_iWorkingNumIndexes += _pNode->m_pChilds[i]->m_iNumIndexes;
            }
            else
            {
                _CheckVisibleQuadTreeNode(_pNode->m_pChilds[i]);
            }
        }
        else if(iResult == CFrustum::E_FRUSTUM_RESULT_OUTSIDE)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_OUTSIDE"<<std::endl;
        }
    }
}

void CLandscape::Update(void)
{
    INode::Update();
    m_iWorkingNumIndexes = 0;
    _CheckVisibleQuadTreeNode(m_pQuadTree);
    m_pMesh->Get_IndexBufferRef()->Set_NumWorkingIndexes(m_iWorkingNumIndexes);
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
}

void CLandscape::Render(INode::E_RENDER_MODE _eMode)
{
    glDisable(GL_BLEND);
    INode::Render(_eMode);
    glCullFace(GL_BACK);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    ILight* pLight = CSceneMgr::Instance()->Get_GlobalLight();
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            m_pShaders[_eMode]->SetVector3(pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }

            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        case INode::E_RENDER_MODE_REFLECTION:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFLECTION is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            m_pShaders[_eMode]->SetVector3(pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
            
            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        case INode::E_RENDER_MODE_REFRACTION:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFRACTION is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            m_pShaders[_eMode]->SetVector3(pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
            
            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, -1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        case INode::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    unsigned int iNumIndexes = m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes();
    glDrawElements(GL_TRIANGLES, iNumIndexes, GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    glCullFace(GL_FRONT);
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
    glEnable(GL_BLEND);
}




