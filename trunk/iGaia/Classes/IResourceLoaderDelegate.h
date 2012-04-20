//
//  IResourceLoaderDelegate.h
//  iGaia
//
//  Created by code_oneclick on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IResourceLoaderDelegate_h
#define iGaia_IResourceLoaderDelegate_h

class IResource;
class IResourceLoaderDelegate
{
public:
    enum E_RESOURCE_TYPE { E_RESOURCE_TYPE_TEXTURE = 0, E_RESOURCE_TYPE_MESH, E_RESOURCE_TYPE_SHADER };
public:
    IResourceLoaderDelegate(void);
    virtual ~IResourceLoaderDelegate(void);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource) = 0;
};


#endif
