//
//  CTileSetterMgr.h
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTileSetterMgr_h
#define gEngine_CTileSetterMgr_h
#include "CVector.h"

class CTileSetterMgr 
{
public:
    enum E_TILE_LEVEL { LEVEL_01 = 0, LEVEL_02, LEVEL_03, LEVEL_MAX };
    enum E_TILE_NODE  { T_C_02 = 0, T_LD, T_RD, T_LU, T_RU, T_L, T_D, T_DIAG_01, T_DIAG_02, T_U, T_R, T_RD_EXT, T_LD_EXT, T_RU_EXT, T_LU_EXT, T_C_01 };
    
    struct STileTexCoords
    {
        CVector2d m_vTexCoord[4];
    };
    
    struct STileTableValue
    {
        char m_iTileType;
        char m_iTilesetType;
    };
    
protected:
    void CreateTileTable();
    void CreateTileMap();
    
    static const int k_TILES_TYPE_COUNT;
    static const int k_TILESETS_TYPE_COUNT;
    static const float k_TILE_TEXTURE_OFFSET;
    
    static CTileSetterMgr* m_pInstance;
    STileTexCoords** m_pTilesTable;
    STileTexCoords* m_pData;
    unsigned char* m_pSource;
    STileTableValue* m_pTempData;
    int m_iWidth;
    int m_iHeight;
    
    void Set_Tile(int _iX, int _iY, E_TILE_LEVEL _eLevel);
    void Set_Tile(int _iX, int _iY, E_TILE_LEVEL _eLevel, E_TILE_NODE _eNode);
    void Set_Tileset(int _iX, int _iY, E_TILE_LEVEL _eLevel);

public :
	CTileSetterMgr();
	~CTileSetterMgr();
    static CTileSetterMgr* Instance(void);
    void Set_Data(unsigned char* _pSource, int _iWidth, int _iHeight);
    STileTexCoords* Get_Data() { return m_pData; }
    void Edit(int _iX, int _iY, E_TILE_LEVEL _eLevel);
};

#endif
