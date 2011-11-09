//
//  CMatch3Level.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLevel_h
#define gEngine_CLevel_h
#include "INode.h"
#include "CShape.h"
#include "CMatch3MapParser.h"

class CMatch3Level : public INode
{
private:
    unsigned int m_uiCellCount;
    unsigned int m_uiRowCount;
    CMatch3MapParser* m_pParser;
public:
    CMatch3Level();
    ~CMatch3Level();
    unsigned int Get_CellCount() { return m_uiCellCount; }
    unsigned int Get_RowCount() { return m_uiRowCount; }
    void Load(unsigned int _uiCellCount, unsigned int _uiRowCount);
    virtual void Render();
    virtual void Update(float _fTime);
};

#endif
