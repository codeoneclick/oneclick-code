//
//  CDataController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CDataController.h"

CDataController::CDataController()
{
    
}

CDataController::~CDataController()
{
    
}

CDataController::SSpriteData* CDataController::SpriteData(std::string _sName)
{
    CDataController::SSpriteData *data = new CDataController::SSpriteData();
    Load(_sName, data);
    return data;
}


void CDataController::Load(std::string _sName, SSpriteData* _pSprite)
{
    NSError *error = nil;
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSLog(@"[Data controller] Data load :%@",sPath);
    NSString *string = [NSString stringWithContentsOfFile:sPath encoding:NSUTF8StringEncoding error:&error];
    string = [string stringByReplacingOccurrencesOfString:@"\"" withString:@"|"];
    string = [string stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSArray *array = [string componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    NSLog(@"%@",array);
    
    std::string k_REG_EXP_X = "x=|";
    std::string k_REG_EXP_Y = "y=|";
    std::string k_REG_EXP_WIDTH = "width=|";
    std::string k_REG_EXP_HEIGHT = "height=|";
    
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
        
        sDataRegExpX = sDataRegExpX.substr(sPositionRegExpX, sDataRegExpX.find("|") - sPositionRegExpX);
        int value = atoi(sDataRegExpX.c_str());
        
    }
}