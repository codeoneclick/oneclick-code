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
#include "CSkyBox.h"
#include "ITouchDelegate.h"

class CLevel : public ITouchDelegate
{
private:
    CLandscape* m_pLandscape;
    CGrass* m_pGrass;
    CWater* m_pWater;
    CSkyBox* m_pSkyBox;
public:
    CLevel(void);
    ~CLevel(void);
    void Load(void);
    void Update(void);
    INode* Get_Model(void) { return m_pLandscape; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif
