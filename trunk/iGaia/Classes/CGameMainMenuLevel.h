//
//  CGameMainMenuLevel.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__CGameMainMenuLevel__
#define __iGaia__CGameMainMenuLevel__

#include "ILevel.h"

class CGameMainMenuLevel : public ILevel
{
public:
    CGameMainMenuLevel(void);
    ~CGameMainMenuLevel(void);
    void Load(void);
    void Unload(void);
    void Update(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CGameMainMenuLevel__) */
