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
    void _CalculateNormals(CVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer);
    void _CalculateTangentsAndBinormals(CVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer);
    void _CalculateTriangleBasis(const glm::vec3& E, const glm::vec3& F, const glm::vec3& G, float sE,
                                 float tE, float sF, float tF, float sG, float tG, glm::vec3& tangentX,
                                 glm::vec3& tangentY);
    glm::vec3 _ClosestPointOnLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
    glm::vec3 _Ortogonalize(const glm::vec3& v1, const glm::vec3& v2);
    
public:
    CHeightMapSetter(void);
    ~CHeightMapSetter(void);
    
    CMesh* Load_DataSource(const std::string _sName, int _iWidth, int _iHeight);
    float* Get_SourceData(void) { return m_pDataSource; }
    
    int Get_Width(void) { return m_iWidth; }
    int Get_Height(void) { return m_iHeight; }
    
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
