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
#define STANDART_MODEL "STANDART_MODEL"
    enum E_STANDART_MODEL { E_STANDART_MODEL_NONE = 0, E_STANDART_MODEL_PLANE, E_STANDART_MODEL_CUBE }; 
    enum E_MGR { E_MGR_TEXTURE = 0,  E_MGR_MESH };
    enum E_THREAD { E_THREAD_MAIN = 0, E_THREAD_BACKGROUND };
    enum E_SHADER { E_SHADER_COLOR = 0, E_SHADER_TEXTURE, E_SHADER_LAMBERT, E_SHADER_PHONG, E_SHADER_CELL_SHADING, E_SHADER_GOOCH, E_SHADER_RIM_LIGHT };
    
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
};


#endif
