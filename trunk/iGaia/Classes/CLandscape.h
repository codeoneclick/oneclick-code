//
//  CLandscape.h
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CLandscape_h
#define iGaia_CLandscape_h

#include "INode.h"
#include <map>
#include <vector>
#include "CHeightMapSetter.h"

#define k_MAX_QUADTREE_CHILDREN 4

class CLandscape : public INode
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
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    CHeightMapSetter* m_pHeightMapSetter;
    unsigned short* m_pWorkingIndexesSourceDataRef;
    unsigned int m_iWorkingNumIndexes;
    SQuadTreeNode* m_pQuadTree;
    void _CreateQuadTreeNode(int _iSize, SQuadTreeNode* _pParentNode);
    void _CreateIndexBufferRefForQuadTreeNode(SQuadTreeNode* _pNode);
    bool _IsPointInBoundBox(glm::vec3 _vPoint, glm::vec3 _vMinBound, glm::vec3 _vMaxBound);
    void _CheckVisibleQuadTreeNode(SQuadTreeNode* _pNode);
public:
    CLandscape(void);
    ~CLandscape(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    CHeightMapSetter* Get_HeightMapSetter(void) { return m_pHeightMapSetter; }
    unsigned int Get_Width(void) { return m_iWidth; }
    unsigned int Get_Height(void) { return m_iHeight; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
