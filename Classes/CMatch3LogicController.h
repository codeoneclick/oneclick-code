//
//  CMatch3LogicController.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3LogicController_h
#define gEngine_CMatch3LogicController_h

class CMatch3LogicController
{
private:
    static CMatch3LogicController* m_pInsatnce;
public:
    CMatch3LogicController();
    ~CMatch3LogicController();
    CMatch3LogicController *Instnace();
};

#endif
