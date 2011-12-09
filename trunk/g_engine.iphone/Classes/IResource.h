//
//  IResource.h
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IResource_h
#define gEngine_IResource_h
#include "stdlib.h"
#include <string>
#include <vector>

class IResource
{
public:
    enum E_PRIMITIVE { E_PRIMITIVE_PLANE, E_PRIMITIVE_CUBE };
    enum E_MGR { E_TEXTURE_MGR = 0, E_SEQUENCE_MGR, E_MESH_MGR };
    enum E_PARSER { E_PVR_PARSER = 0, E_SEQ_PARSER, E_M3_PARSER, E_MD2_PARSER, E_GMESH_PARSER };
    enum E_THREAD { E_MAIN_THREAD = 0, E_BACKGROUND_THREAD };
    enum E_MESH { E_MESH_PRIMITIVE = 0, E_MESH_STATIC, E_MESH_MOVIE };
    enum E_INTERSECTOR { E_INTERSECTOR_NONE = 0, E_INTERSECTOR_ONLY, E_INTERSECTOR_WITH_MODEL }; 
    enum E_SHADER { E_COLOR = 0, E_TEXTURE, E_COLOR_VERTEX_DIFFUSE, E_TEXTURE_VERTEX_DIFFUSE, E_TEXTURE_PIXEL_DIFFUSE, E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_COLOR, E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_TEXTURE };
    
    struct SResource
    {
        std::string m_sMesh;
        std::vector<std::string> m_lTextures;
        E_MESH m_eMesh;
        E_PRIMITIVE m_ePrimitive;
        E_INTERSECTOR m_eIntersector;
        E_SHADER m_eShader;
        bool m_bBatch;
    };
    
protected:
    E_PARSER m_eParser;
    int m_iRefCount;
    std::string m_sName;
public:
    IResource();
    virtual ~IResource();
    virtual void Release();
    inline void IncRefCount() { m_iRefCount++; }
    inline void DecRefCount() { m_iRefCount--; }
    inline int Get_RefCount() { return m_iRefCount; }
    inline void Set_Name(const std::string& _sName) { m_sName = _sName; }
    inline std::string Get_Name() { return m_sName; }
    inline E_PARSER Get_Parser() { return m_eParser; }
    inline void Set_Parser(E_PARSER _eParser) { m_eParser = _eParser; } 
    virtual void Set_Source(void* _pSource) = 0;
};


#endif
