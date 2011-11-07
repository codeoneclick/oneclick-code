//
//  CMatch3MapParser.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3MapParser_h
#define gEngine_CMatch3MapParser_h

#include "stdlib.h"
#include <string>
#include "CMatch3Cell.h"

class CMatch3MapParser
{
private:
    CMatch3Cell::E_STATE* m_pMapData;
    unsigned int m_uiCellCount;
    unsigned int m_uiRowCount;
public:
    CMatch3MapParser();
    ~CMatch3MapParser();
    void Parse(const char* _sName);
    CMatch3Cell::E_STATE* Get_MapData() { return m_pMapData; }
    unsigned int Get_CellCount() { return m_uiCellCount; }
    unsigned int Get_RowCount() { return m_uiRowCount; }
};



#endif
