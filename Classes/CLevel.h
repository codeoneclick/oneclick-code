//
//  CLevel.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLevel_h
#define gEngine_CLevel_h
#include "INode.h"
#include "CShape.h"

class CLevel : public INode
{
private:
    unsigned int m_uiCellCount;
    unsigned int m_uiRowCount;
public:
    CLevel();
    ~CLevel();
    void Load(unsigned int _uiCellCount, unsigned int _uiRowCount);
    virtual void Render();
};

#endif
