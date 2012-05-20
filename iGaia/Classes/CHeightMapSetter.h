//
//  CHeightMapSetter.h
//  iGaia
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CHeightMapSetter_h
#define iGaia_CHeightMapSetter_h


#include "CTileSetter.h"
#include "CMesh.h"

class CHeightMapSetter
{
protected:
    std::vector<glm::vec2> m_lContainerShadowDecal;
    std::vector<glm::vec2> m_lContainerExplosionDecal;
    
    float* m_pDataSource;
    
    int m_iWidth;
    int m_iHeight;
    
    float m_fXThreshold;
    float m_fZThreshold;
    
    GLuint m_hTextureSplatting;
    GLuint m_hTextureDecal;
    
    unsigned short* m_pTextureSplattingDataSource;
    unsigned short* m_pTextureDecalDataSource;
    
    void _Create_TextureSplatting(void);
    void _Create_TextureDecal(void);
    void _Update_TextureDecal(void);
    
public:
    CHeightMapSetter(void);
    ~CHeightMapSetter(void);
    
    CMesh* Load_DataSource(const std::string _sName, int _iWidth, int _iHeight);
    float* Get_DataSource(void) { return m_pDataSource; }
    
    float Get_HeightValue(float _x, float _z);
    float Get_HeightValue(glm::vec2 _vPosition);
    float Get_HeightValue(glm::vec3 _vPosition);
    
    GLuint Get_TextureSplatting(void) { return m_hTextureSplatting; }
    GLuint Get_TextureDecal(void) { return m_hTextureDecal; }
    
    void Add_ShadowDecal(glm::vec2 _vPosition) { m_lContainerShadowDecal.push_back(_vPosition); }
    void Add_ExplosionDecal(glm::vec2 _vPosition) { m_lContainerExplosionDecal.push_back(_vPosition); }
    
    void Update(void);
};

#endif
