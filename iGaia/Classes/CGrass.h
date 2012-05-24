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
    static const float k_ELEMENT_SIZE;
    static const float k_ELEMENT_HEIGHT;
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    
    unsigned short* m_pSingleElementIndexBuffer;
    CVertexBuffer*  m_pSingleElementVertexBuffer;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CHeightMapSetter* m_pHeightMapSetter;
    
    std::vector<glm::vec3> m_lGrassElementsPosition;
public:
    CGrass(void);
    virtual ~CGrass(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
