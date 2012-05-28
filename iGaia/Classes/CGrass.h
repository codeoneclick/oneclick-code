//
//  CGrass.h
//  iGaia
//
//  Created by sergey.sergeev on 3/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGrass_h
#define iGaia_CGrass_h

#include "INode.h"
#include <map>
#include "CHeightMapSetter.h"

class CGrass: public INode
{
protected:
    struct SQuadTreeNode
    {
        SQuadTreeNode* m_pParent;
        SQuadTreeNode** m_pChilds;
        glm::vec3 m_vMaxBound;
        glm::vec3 m_vMinBound;
        unsigned short* m_pIndexes;
        unsigned short* m_pIndexesId;
        unsigned int m_iNumIndexes;
        SQuadTreeNode(void)
        {
            m_pParent = NULL;
            m_pChilds = NULL;
            m_pIndexes = NULL;
            m_iNumIndexes = 0;
        }
    };

    static const float k_ELEMENT_SIZE;
    static const float k_ELEMENT_HEIGHT;
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    
    unsigned short* m_pSingleElementIndexBuffer;
    IVertexBuffer*  m_pSingleElementVertexBuffer;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CHeightMapSetter* m_pHeightMapSetter;
    
    std::vector<glm::vec3> m_lGrassElementsPosition;

    unsigned short* m_pWorkingIndexesSourceDataRef;
    unsigned int m_iWorkingNumIndexes;

    SQuadTreeNode* m_pQuadTree;
    void _CreateQuadTreeNode(int _iSize, SQuadTreeNode* _pParentNode);
    void _CreateIndexBufferRefForQuadTreeNode(SQuadTreeNode* _pNode);
    bool _IsPointInBoundBox(glm::vec3 _vPoint, glm::vec3 _vMinBound, glm::vec3 _vMaxBound);
    void _CheckVisibleQuadTreeNode(SQuadTreeNode* _pNode);

public:
    CGrass(void);
    ~CGrass(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(CShader::E_RENDER_MODE _eMode);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
