//
//  CPathFinderAstar.h
//  gEngine
//
//  Created by sergey.sergeev on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CPathFinderAstar_h
#define gEngine_CPathFinderAstar_h

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "CVector.h"

#define k_DIRECTION_8 8
#define k_DIRECTION_4 4

class CPathFinderAstar
{
public:
    class CPathNode
    {
        int m_iXPosition;
        int m_iYPosition;
        int m_iLevel;
        int m_iPriority;
        int m_iDirectionNum;
        
    public:
        CPathNode(int _iXPositon, int _iYPosition, int _iLevel, int _iPriority, int _iDirectionNum) 
        {m_iXPosition = _iXPositon; m_iYPosition = _iYPosition; m_iLevel = _iLevel; m_iPriority = _iPriority; m_iDirectionNum = _iDirectionNum; }
        
        int Get_PositionX(void) const {return m_iXPosition;}
        int Get_PositionY(void) const {return m_iYPosition;}
        int Get_Level(void) const {return m_iLevel;}
        int Get_Priority(void) const {return m_iPriority;}
        
        void UpdatePriority(const int& _iXDest, const int& _iYDest)
        {
            m_iPriority = m_iLevel + Estimate(_iXDest, _iYDest) * 10; 
        }
        
        void NextLevel(const int & _iDirection) 
        {
            m_iLevel += (m_iDirectionNum == 8 ? ( _iDirection % 2 == 0 ? 10:14 ): 10);
        }
        
        const int& Estimate(const int& _iXDest, const int& _iYDest) const
        {
            static int iXDistance, iYDistance, iMainDistance;
            iXDistance = _iXDest - m_iXPosition;
            iYDistance = _iYDest - m_iYPosition;         
            
            iMainDistance = static_cast<int>(sqrt(iXDistance * iXDistance + iYDistance * iYDistance));
            return iMainDistance;
        }
    };
    
private:
    int m_iWidth; 
    int m_iHeight;
    int **m_pMapData;
    int **m_pClosedMapData;
    int **m_pOpenMapData; 
    int **m_pDirectionMapData;
    int m_iDirectionNum;
    
    static int m_pDirection_8_X[k_DIRECTION_8];
    static int m_pDirection_8_Y[k_DIRECTION_8];
    
    static CPathFinderAstar* m_pInstance;
    
    std::vector<glm::vec2> m_lPath;
    
    void Clear(void);
    //static int m_pDirection_4_X[k_DIRECTION_4];
    //static int m_pDirection_4_Y[k_DIRECTION_4];
public:
    CPathFinderAstar(void);
    ~CPathFinderAstar(void);
    static CPathFinderAstar* Instance(void);
    std::string FindPath(int** _pMapSource, int _iWidth, int _iHeight, glm::vec2 vStartNode, glm::vec2 vEndNode);
    std::vector<glm::vec2> Get_Path() { return m_lPath; }
};


#endif
