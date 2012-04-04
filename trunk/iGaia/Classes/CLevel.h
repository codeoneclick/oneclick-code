//
//  CLevel.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CLevel_h
#define iGaia_CLevel_h

#include "CLandscape.h"
#include "CGrass.h"
#include "CWater.h"
#include "IDelegate.h"

class CLevel : public IDelegate
{
private:
    CLandscape* m_pLandscape;
    CGrass* m_pGrass;
    CWater* m_pWater;
public:
    CLevel(void);
    ~CLevel(void);
    void Load(void);
    void Update(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner);
    INode* Get_Model(void) { return m_pLandscape; }
};

#endif
