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
#include "string.h"

class IResource
{
public:
    enum E_MGR { E_TEXTURE_MGR, E_SEQUENCE_MGR };
    enum E_PARSER { E_PVR_PARSER, E_SEQ_PARSER };
    enum E_THREAD { E_MAIN_THREAD, E_BACKGROUND_THREAD };
protected:
    E_PARSER m_eParser;
    unsigned int m_uiRefCount;
    std::string m_sName;
public:
    IResource();
    virtual ~IResource();
    virtual void Release();
    inline void IncRefCount() { m_uiRefCount++; }
    inline void DecRefCount() { m_uiRefCount--; }
    inline unsigned int Get_RefCount() { return m_uiRefCount; }
    inline void Set_Name(std::string _sName) { m_sName = _sName; }
    inline std::string Get_Name() { return m_sName; }
    inline E_PARSER Get_Parser() { return m_eParser; }
    virtual void Set_Source(void* _pSource) = 0;
};


#endif
