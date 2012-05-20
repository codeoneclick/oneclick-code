//
//  IResource.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IResource_h
#define iGaia_IResource_h
#include "stdlib.h"
#include <string>
#include <vector>
#include "IResourceLoaderDelegate.h"

class IResource
{
public:
#define STANDART_MODEL "STANDART_MODEL"
    enum E_STANDART_MODEL { E_STANDART_MODEL_NONE = 0, E_STANDART_MODEL_PLANE, E_STANDART_MODEL_CUBE }; 
    enum E_MGR { E_MGR_TEXTURE = 0,  E_MGR_MESH };
    enum E_THREAD { E_THREAD_MAIN = 0, E_THREAD_BACKGROUND };
    enum E_SHADER { E_SHADER_COLOR = 0, E_SHADER_TEXTURE, E_SHADER_LAMBERT, E_SHADER_PHONG, E_SHADER_CELL_SHADING, E_SHADER_GOOCH, E_SHADER_RIM_LIGHT, E_SHADER_BLOOM_EXTRACT, E_SHADER_BLUR, E_SHADER_BLOOM_COMBINE, E_SHADER_PARALLAX, E_SHADER_EDGE_DETECT, E_SHADER_LANDSCAPE,  E_SHADER_UNIT, E_SHADER_NORMAL_DEPTH, E_SHADER_PROJECT_TEXTURE, E_SHADER_WATER, E_SHADER_PRE_NORMAL_DEPTH_UNIT, E_SHADER_ANIM_TEXCOORD_UNIT, E_SHADER_SHADOW_MAP, E_SHADER_TEXTURE_CUBE, E_SHADER_SHADOW_PLANE };
    
    struct SResource
    {
        std::string m_sName;
        E_STANDART_MODEL m_eModel;
        E_THREAD m_eThread;
        bool m_bIsBatching;
    };
    
protected:
    int m_iRefCount;
    std::string m_sName;
    IResourceLoaderDelegate* m_pResourceLoaderDelegate;
IResourceLoaderDelegate::E_RESOURCE_TYPE m_eResourceType;
public:
    IResource();
    virtual ~IResource();
    virtual void Release();
    inline void IncRefCount() { m_iRefCount++; }
    inline void DecRefCount() { m_iRefCount--; }
    inline int Get_RefCount() { return m_iRefCount; }
    inline void Set_Name(const std::string& _sName) { m_sName = _sName; }
    inline std::string Get_Name() { return m_sName; }
    virtual void Set_Source(void* _pSource) = 0;
    inline void Set_ResourceLoaderDelegate(IResourceLoaderDelegate* _pResourceLoaderDelegate) { m_pResourceLoaderDelegate = _pResourceLoaderDelegate; }
    inline IResourceLoaderDelegate* Get_ResourceLoaderDelegate(void) { return m_pResourceLoaderDelegate; }
    inline void Set_ResourceType(IResourceLoaderDelegate::E_RESOURCE_TYPE _eResourceType) { m_eResourceType = _eResourceType; }
    inline IResourceLoaderDelegate::E_RESOURCE_TYPE Get_ResourceType(void) { return m_eResourceType; }
};


#endif
