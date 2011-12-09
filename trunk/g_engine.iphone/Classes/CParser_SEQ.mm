//
//  CFXMLLoader.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_SEQ.h"

CParser_SEQ::CParser_SEQ()
{
    m_pSource = NULL;
    m_pData = NULL;
}

CParser_SEQ::~CParser_SEQ()
{
    if(m_pData != NULL)
    {
        delete m_pData;
        m_pData = NULL;
    }
}

void CParser_SEQ::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS; 
    NSError *error = nil;
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSLog(@"[Data controller] Data load :%@",sPath);
    NSString *string = [NSString stringWithContentsOfFile:sPath encoding:NSUTF8StringEncoding error:&error];
    
    m_pData = (char*)[string UTF8String];
    
    string = [string stringByReplacingOccurrencesOfString:@"\"" withString:@"|"];
    string = [string stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSArray *array = [string componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    NSLog(@"%@",array);
    
    std::string k_REG_EXP_X = "x=|";
    std::string k_REG_EXP_Y = "y=|";
    std::string k_REG_EXP_WIDTH = "width=|";
    std::string k_REG_EXP_HEIGHT = "height=|";
    
    m_pSource = new CSequence::SSource();
    
    for(unsigned int index = 0; index < [array count]; index++)
    {
        const char* cData = [[array objectAtIndex:index] UTF8String];
        std::string sData = std::string(cData);
        unsigned int sPositionRegExpX = sData.find(k_REG_EXP_X);
        unsigned int sPositionRegExpY = sData.find(k_REG_EXP_Y);
        unsigned int sPositionRegExpWidth = sData.find(k_REG_EXP_WIDTH);
        unsigned int sPositionRegExpHeight = sData.find(k_REG_EXP_HEIGHT);
        
        std::string sDataRegExpX = std::string(cData + sPositionRegExpX + k_REG_EXP_X.length());
        std::string sDataRegExpY = std::string(cData + sPositionRegExpY + k_REG_EXP_Y.length());
        std::string sDataRegExpWidth = std::string(cData + sPositionRegExpWidth + k_REG_EXP_WIDTH.length());
        std::string sDataRegExpHeight = std::string(cData + sPositionRegExpHeight + k_REG_EXP_HEIGHT.length());
        
        sDataRegExpX = sDataRegExpX.substr(0, sDataRegExpX.find("|"));
        int iValueX = atoi(sDataRegExpX.c_str());
        
        sDataRegExpY = sDataRegExpY.substr(0, sDataRegExpY.find("|"));
        int iValueY = atoi(sDataRegExpY.c_str());
        
        sDataRegExpWidth = sDataRegExpWidth.substr(0, sDataRegExpWidth.find("|"));
        int iValueWidth = atoi(sDataRegExpWidth.c_str());
        
        sDataRegExpHeight = sDataRegExpHeight.substr(0, sDataRegExpHeight.find("|"));
        int iValueHeight = atoi(sDataRegExpHeight.c_str());
        
        CSequence::SFrame* frame = new CSequence::SFrame();
        frame->m_vPosition = Vector2d(static_cast<float>(iValueX), static_cast<float>(iValueY));
        frame->m_vSize = Vector2d(static_cast<float>(iValueHeight), static_cast<float>(iValueWidth));
        m_pSource->m_lFrames.push_back(frame);
        //delete cData;
    }
    m_eStatus = E_DONE_STATUS;
}








