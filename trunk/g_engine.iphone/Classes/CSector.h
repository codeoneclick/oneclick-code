//
//  CSector.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSector_h
#define gEngine_CSector_h

#include "IGameObject.h"
#include "CModel.h"

class CSector : public IGameObject
{
protected:
    INode* m_pModel;
public:
    CSector();
    virtual ~CSector();
    virtual void Load(std::vector<IResource::SResource> _lResource);
    virtual void Update(float _fTime);
    virtual bool IsPicker();
    void Set_Path(bool _bValue);
};

#endif
