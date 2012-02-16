//
//  CHeightMapSetter.h
//  gEngine
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CHeightMapSetter_h
#define gEngine_CHeightMapSetter_h


#include "CTileSetter.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CHeightMapSetter
{
private:
    static const float k_HEIGHT_DIV_FACTOR;
    float* m_pSource;
    int m_iWidth;
    int m_iHeight;
public:
    CHeightMapSetter(void);
    ~CHeightMapSetter(void);
    
    void Load_SourceData(const std::string& _sName, int _iWidth, int _iHeight);
    void Set_SourceData(float* _pSource, int _iWidth, int _iHeight) { m_pSource = _pSource; m_iWidth = _iWidth; m_iHeight = _iHeight; }
    float* Get_HeightMapData(void) { return m_pSource; }
    void Calculate_Normals(CVertexBuffer* _pVB, CIndexBuffer* _pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode);
};

#endif
