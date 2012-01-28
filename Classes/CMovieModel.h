//
//  CMovieModel.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMovieModel_h
#define gEngine_CMovieModel_h
#include "CModel.h"

class CMovieModel : public CModel
{
protected:

public:
    CMovieModel(void);
    virtual ~CMovieModel();
    virtual void Load(IResource::SResource _tResource);
    virtual void Update(void);
    virtual void Render(void);
};


#endif
