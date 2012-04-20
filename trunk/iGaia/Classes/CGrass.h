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
    //CVertexBuffer::SVertex m_pSingleElementVertexBuffer;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CHeightMapSetter* m_pHeightMapSetter;
public:
    CGrass(void);
    virtual ~CGrass(void);
    virtual void Load(IResource::SResource _tResource);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType,IResource* pResource);
    virtual void OnTouchEvent(void);
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
};

#endif
