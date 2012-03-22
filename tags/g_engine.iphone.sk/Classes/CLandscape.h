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
#include <map>
#include "CTileSetter.h"
#include "CHeightMapSetter.h"
#include "CNavigationMesh.h"

class CLandscape : public INode
{
protected:
    static const int k_TILE_NUM_INDEXES;
    static const int k_TILE_NUM_VERTEXES;
    static const float k_TILE_SIZE;
    
    unsigned short* m_pSingleTileIB;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CMesh* m_pVisualNavigationMeshRef;
    CShader* m_pVisualNavigationMeshShader;
    
    CTileSetter* m_pTileSetter;
    CHeightMapSetter* m_pHeightMapSetter;
    CNavigationMesh* m_pNavigationMesh;
    struct STile
    {
        glm::vec3 m_vPosition;
        CBoundingBox* m_pBoundingBox;
        ICollider* m_pCollider;
    };
    std::map<unsigned int, STile*> m_lContainer;
    void LoadWithTileSet(void);
public:
    CLandscape(void);
    virtual ~CLandscape();
    virtual void Load(IResource::SResource _tResource);
    virtual void OnTouchEvent(void);
    virtual void Update(void);
    virtual void Render(void);
    CHeightMapSetter* Get_HeightMapSetter(void) { return m_pHeightMapSetter; }
    CTileSetter* Get_TileSetter(void) { return m_pTileSetter; }
    unsigned int Get_Width(void) { return m_iWidth; }
    unsigned int Get_Height(void) { return m_iHeight; }
};

#endif
