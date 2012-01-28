//
//  CLandscape.h
//  gEngine
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLandscape_h
#define gEngine_CLandscape_h

#include "INode.h"
#include "CTileSetterMgr.h"
#include <map>

class CLandscape : public INode
{
public:
    enum E_HEIGHT_LEVEL { E_HEIGHT_LEVEL_UP = 0, E_HEIGHT_LEVEL_DOWN };
protected:
    static const int k_TILE_NUM_INDEXES;
    static const int k_TILE_NUM_VERTEXES;
    static const float k_TILE_SIZE;
    
    unsigned short* m_pSingleTileIB;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    float** m_pHeihtmapSource;
    unsigned char* m_pTilesetSource;
    CTileSetterMgr::STileTexCoords* m_pTilesetData;
    
    struct STile
    {
        CVector3d m_vPosition;
        CBoundingBox* m_pBoundingBox;
        ICollider* m_pCollider;
    };
    std::map<unsigned int, STile*> m_lContainer;
public:
    CLandscape(void);
    virtual ~CLandscape();
    virtual void Load(IResource::SResource _tResource);
    virtual void OnMouseTouchEvent(void);
    virtual void Update(void);
    virtual void Render(void);
    void EditTilesetData(int _iX, int _iY, CTileSetterMgr::E_TILE_LEVEL _eLevel);
    void EditHeightmapData(int _iX, int _iY, E_HEIGHT_LEVEL _eLevel);
};

#endif
