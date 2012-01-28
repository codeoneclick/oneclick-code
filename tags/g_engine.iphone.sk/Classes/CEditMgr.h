//
//  CEditMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 1/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CEditMgr_h
#define gEngine_CEditMgr_h

#include "CTileSetterMgr.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CEditMgr
{
private:
    static const float k_HEIGHT_DIV_FACTOR;
    
    static CEditMgr* m_pInstance;
public:
    CEditMgr(void);
    ~CEditMgr(void);
    static CEditMgr* Instance();
    
    float** LoadHeightmapData(const std::string& _sName, unsigned int _iWidth, unsigned int _iHeight);
    unsigned char* LoadTilesetData(const std::string& _sName, unsigned int _iWidth, unsigned int _iHeight);
    CTileSetterMgr::STileTexCoords* Get_TilesetData(const std::string& _sName, unsigned int _iWidth, unsigned int _iHeight, unsigned char* _pSource);
    void CalculateNormals(CVertexBuffer* _pVB, CIndexBuffer* _pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode);
    void EditTilesetData(const std::string& _sName, int _iX, int _iY, unsigned int _iWidth, unsigned int _iHeight, CTileSetterMgr::E_TILE_LEVEL _eLevel, CVertexBuffer* _pVB, CTileSetterMgr::STileTexCoords* _pData, unsigned char* _pSource);
};

#endif
