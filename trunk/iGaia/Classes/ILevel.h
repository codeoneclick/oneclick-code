//
//  ILevel.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__ILevel__
#define __iGaia__ILevel__

#include "CLandscape.h"
#include "CGrass.h"
#include "CWater.h"
#include "CSkyBox.h"
#include "ITouchDelegate.h"

class ILevel : public ITouchDelegate
{
protected:
    CLandscape* m_pLandscape;
    CGrass* m_pGrass;
    CWater* m_pOcean;
    CSkyBox* m_pSkyBox;
public:
    ILevel(void);
    ~ILevel(void);
    CLandscape* Get_Landscape(void) { return m_pLandscape; }
    CGrass* Get_Grass(void) { return m_pGrass; }
    CWater* Get_Ocean(void) { return m_pOcean; }
    CSkyBox* Get_SkyBox(void) { return m_pSkyBox; }
    
    virtual void Load(void);
    virtual void Unload(void);
    virtual void Update(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__ILevel__) */
