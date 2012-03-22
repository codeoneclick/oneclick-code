//
//  CGrass.h
//  gEngine
//
//  Created by sergey.sergeev on 3/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGrass_h
#define gEngine_CGrass_h

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
    CVertexBuffer::SVertex m_pSingleElementVertexBuffer;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CHeightMapSetter* m_pHeightMapSetter;
public:
    CGrass(void);
    virtual ~CGrass(void);
    virtual void Load(IResource::SResource _tResource);
    virtual void OnTouchEvent(void);
    virtual void Update(void);
    virtual void Render(void);
};

#endif
