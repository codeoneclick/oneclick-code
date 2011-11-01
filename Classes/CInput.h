//
//  CInput.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CInput_h
#define gEngine_CInput_h

class CInput
{
private:
    static CInput* m_instance;
public:
    CInput();
    ~CInput();
    static CInput* Instance();
};

#endif
