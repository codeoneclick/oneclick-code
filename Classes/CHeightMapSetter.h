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
#include "CMesh.h"

class CHeightMapSetter
{
private:
    float* m_pSource;
    int** m_pPathFindSource;
    int m_iWidth;
    int m_iHeight;
    GLuint m_hTextureSplatting;
    void Create_SplattingTexture(void);
public:
    CHeightMapSetter(void);
    ~CHeightMapSetter(void);
    
    CMesh* Load_SourceData(const std::string _sName, int _iWidth, int _iHeight);
    
    void Set_SourceData(float* _pSource, int _iWidth, int _iHeight) { m_pSource = _pSource; m_iWidth = _iWidth; m_iHeight = _iHeight; }
    float* Get_HeightMapData(void) { return m_pSource; }
    int** Get_PathFindData(void) { return m_pPathFindSource; }
    void Calculate_Normals(CVertexBuffer* _pVB, CIndexBuffer* _pIB);
    float Get_HeightValueAtPoint(float _fX, float _fZ);
    GLuint Get_SplattingTexture(void) { return m_hTextureSplatting; }
};

#endif
