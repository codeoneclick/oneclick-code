//
//  CWater.h
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CWater_h
#define iGaia_CWater_h

#include "INode.h"

class CWater: public INode
{
protected:
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
public:
    CWater(void);
    virtual ~CWater(void);
    virtual void Load(IResource::SResource _tResource);
    virtual void OnTouchEvent(void); 
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
};

#endif
