//
//  CMatch3MapParser.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3MapParser.h"

CMatch3MapParser::CMatch3MapParser()
{
    m_pMapData = NULL;
}

CMatch3MapParser::~CMatch3MapParser()
{
    
}

void CMatch3MapParser::Parse(const char* _sName)
{
    NSError *error = nil;
    NSString* sName = [NSString stringWithUTF8String:_sName];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSLog(@"[Data controller] Data load :%@",sPath);
    NSString *sData = [NSString stringWithContentsOfFile:sPath encoding:NSUTF8StringEncoding error:&error];
    NSArray *array = [sData componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    NSLog(@"%@",array);
    
    char* pData = (char*)[sData UTF8String];
    unsigned int count = [sData length];
    
    m_uiCellCount = [array count];
    m_uiRowCount = [((NSString*)[array objectAtIndex:0]) length];
    
    m_pMapData = new CMatch3Cell::E_STATE[m_uiCellCount * m_uiRowCount];
    
    unsigned int mapIndex = 0;
    
    for( unsigned int index = 0; index < count; ++index)
    {
        switch (pData[index])
        {
            case 'A':
                m_pMapData[mapIndex] = CMatch3Cell::E_EMPTY;
                mapIndex++;
                break;
            case 'B':
                m_pMapData[mapIndex] = CMatch3Cell::E_NONE;
                mapIndex++;
                break;
            case 'C':
                m_pMapData[mapIndex] = CMatch3Cell::E_CELL_01;
                mapIndex++;
                break;
            case 'D':
                m_pMapData[mapIndex] = CMatch3Cell::E_CELL_02;
                mapIndex++;
                break;
            case 'E':
                m_pMapData[mapIndex] = CMatch3Cell::E_CELL_03;
                mapIndex++;
                break;
            case 'F':
                m_pMapData[mapIndex] = CMatch3Cell::E_BONUS_01;
                mapIndex++;
                break;
            case 'G':
                m_pMapData[mapIndex] = CMatch3Cell::E_BONUS_02;
                mapIndex++;
                break;
            case 'H':
                m_pMapData[mapIndex] = CMatch3Cell::E_BONUS_03;
                mapIndex++;
                break;
            case '\n':
                break;
            default:
                std::cout<<"[CMatch3MapParser] Critical warning map is corrupted.";
                break;
        }
    }

    delete pData;
}
