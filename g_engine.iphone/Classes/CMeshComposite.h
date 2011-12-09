//
//  CMeshComposite.h
//  gEngine
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMeshComposite_h
#define gEngine_CMeshComposite_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CMesh.h"

class CMeshComposite
{
private:
    static CMeshComposite* m_pInstance;
protected:
    std::map<IResource::E_PRIMITIVE, CMesh*> m_lContainer;
public:
    CMeshComposite();
    ~CMeshComposite();
    static CMeshComposite* Instance();
    CMesh* Get_Mesh(IResource::E_PRIMITIVE _eMesh);
};

#endif
