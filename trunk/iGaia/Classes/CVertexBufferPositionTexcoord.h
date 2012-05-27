//
//  CVertexBufferPositionTexcoord.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBufferPositionTexcoord_h
#define iGaia_CVertexBufferPositionTexcoord_h

#include "IVertexBuffer.h"

class CVertexBufferPositionTexcoord : public IVertexBuffer
{
public:
    CVertexBufferPositionTexcoord(unsigned int _iNumVertexes, unsigned int _eMode);
    ~CVertexBufferPositionTexcoord(void);
    
    virtual void* Lock(void);
    virtual void Enable(CShader::E_RENDER_MODE _eRenderMode);
    virtual void Disable(CShader::E_RENDER_MODE _eRenderMode);
};

#endif
