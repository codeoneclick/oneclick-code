//
//  CPathFinderAstar.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CPathFinderAstar.h"

int CPathFinderAstar::m_pDirection_8_X[k_DIRECTION_8] = {1, 1, 0, -1, -1, -1, 0, 1};
int CPathFinderAstar::m_pDirection_8_Y[k_DIRECTION_8] = {0, 1, 1, 1, 0, -1, -1, -1};
CPathFinderAstar* CPathFinderAstar::m_pInstance = NULL;

CPathFinderAstar::CPathFinderAstar(void)
{
    
}

CPathFinderAstar::~CPathFinderAstar(void)
{
    
}

CPathFinderAstar* CPathFinderAstar::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CPathFinderAstar();
    }
    return m_pInstance;
}

/*#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

const int n=60; // horizontal size of the map
const int m=60; // vertical size size of the map
static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority
    
public:
    node(int xp, int yp, int d, int p) 
    {xPos=xp; yPos=yp; level=d; priority=p;}
    
    int getxPos() const {return xPos;}
    int getyPos() const {return yPos;}
    int getLevel() const {return level;}
    int getPriority() const {return priority;}
    
    void updatePriority(const int & xDest, const int & yDest)
    {
        priority=level+estimate(xDest, yDest)*10; //A*
    }
    
    // give better priority to going strait instead of diagonally
    void nextLevel(const int & i) // i: direction
    {
        level+=(dir==8?(i%2==0?10:14):10);
    }
    
    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const
    {
        static int xd, yd, d;
        xd=xDest-xPos;
        yd=yDest-yPos;         
        
        // Euclidian Distance
        d=static_cast<int>(sqrt(xd*xd+yd*yd));
        
        // Manhattan distance
        //d=abs(xd)+abs(yd);
        
        // Chebyshev distance
        //d=max(abs(xd), abs(yd));
        
        return(d);
    }
};*/

bool operator<(const CPathFinderAstar::CPathNode& _pNode_01, const CPathFinderAstar::CPathNode& _pNode_02)
{
    return _pNode_01.Get_Priority() > _pNode_02.Get_Priority();
}

// Determine priority (in the priority queue)
/*bool operator<(const node & a, const node & b)
{
    return a.getPriority() > b.getPriority();
}*/

void CPathFinderAstar::Clear(void)
{
    for(unsigned int i = 0; i < m_iWidth; i++)
    {
        delete m_pClosedMapData[i];
        delete m_pOpenMapData[i];
        delete m_pMapData[i];
        delete m_pDirectionMapData[i];
    }
    
    delete m_pClosedMapData;
    delete m_pOpenMapData;
    delete m_pMapData;
    delete m_pDirectionMapData;
}

// A-star algorithm.
// The route returned is a string of direction digits.
std::string CPathFinderAstar::FindPath(int** _pMapSource, int _iWidth, int _iHeight, CVector2d vStartNode, CVector2d vEndNode)
{
    int xStart = vStartNode.x; 
    int yStart = vStartNode.y; 
    int xFinish = vEndNode.x;
    int yFinish = vEndNode.y;
    
    m_lPath.clear();
    m_lPath.push_back(vEndNode);
    
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    std::priority_queue<CPathFinderAstar::CPathNode> pq[2]; 
    int pqi;
    CPathFinderAstar::CPathNode* n0;
    CPathFinderAstar::CPathNode* m0;
    int i, j, x, y, xdx, ydy;
    char c;
    pqi = 0;
    m_iDirectionNum = 8;
    
    m_pClosedMapData = new int*[m_iWidth];
    m_pOpenMapData = new int*[m_iWidth];
    m_pMapData = new int*[m_iWidth];
    m_pDirectionMapData = new int*[m_iWidth];
    
    for(x=0; x < m_iWidth; x++)
    {
        m_pClosedMapData[x] = new int[m_iHeight];
        m_pOpenMapData[x] = new int[m_iHeight];
        m_pMapData[x] = new int[m_iHeight];
        m_pDirectionMapData[x] = new int[m_iHeight];
        for(y=0; y < m_iHeight; y++)
        {
            m_pClosedMapData[x][y] = 0;
            m_pOpenMapData[x][y] = 0;
            m_pDirectionMapData[x][y] = 0;
            m_pMapData[x][y] = _pMapSource[x][y];
        }
    }
    
    n0 = new CPathFinderAstar::CPathNode(xStart, yStart, 0, 0, m_iDirectionNum);
    n0->UpdatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    m_pOpenMapData[0][0] = n0->Get_Priority(); 
    
    while(!pq[pqi].empty())
    {
        n0 = new CPathFinderAstar::CPathNode( pq[pqi].top().Get_PositionX(), pq[pqi].top().Get_PositionY(), 
                    pq[pqi].top().Get_Level(), pq[pqi].top().Get_Priority(), m_iDirectionNum);
        
        x= n0->Get_PositionX(); y=n0->Get_PositionY();
        
        pq[pqi].pop(); 
        m_pOpenMapData[x][y] = 0;
        m_pClosedMapData[x][y] = 1;
        
        if(x == xFinish && y == yFinish) 
        {
            std::string path = "";
            while(!(x==xStart && y==yStart))
            {
                j= m_pDirectionMapData[x][y];
                c ='0' + ( j + m_iDirectionNum / 2) % m_iDirectionNum;
                path= c + path;
                x += m_pDirection_8_X[j];
                y += m_pDirection_8_Y[j];
                std::cout<<"Path :"<<x<<","<<y<<"\n";
                m_lPath.push_back(CVector2d(x, y));
            }
            
            delete n0;
            while(!pq[pqi].empty()) pq[pqi].pop();  
            Clear();
            return path;
        }
        
        // generate moves (child nodes) in all possible directions
        for(i=0; i <m_iDirectionNum; i++)
        {
            xdx=x+m_pDirection_8_X[i]; ydy=y+m_pDirection_8_Y[i];
            
            if(!(xdx<0 || xdx> m_iHeight-1 || ydy<0 || ydy>m_iWidth-1 || m_pMapData[xdx][ydy]==1 
                 || m_pClosedMapData[xdx][ydy]==1))
            {
                // generate a child node
                m0=new CPathFinderAstar::CPathNode( xdx, ydy, n0->Get_Level(), 
                            n0->Get_Priority(), m_iDirectionNum);
                m0->NextLevel(i);
                m0->UpdatePriority(xFinish, yFinish);
                
                // if it is not in the open list then add into that
                if(m_pOpenMapData[xdx][ydy]==0)
                {
                    m_pOpenMapData[xdx][ydy] = m0->Get_Priority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    m_pDirectionMapData[xdx][ydy]=(i+m_iDirectionNum/2)%m_iDirectionNum;
                }
                else if(m_pOpenMapData[xdx][ydy]>m0->Get_Priority())
                {
                    // update the priority info
                    m_pOpenMapData[xdx][ydy]=m0->Get_Priority();
                    // update the parent direction info
                    m_pDirectionMapData[xdx][ydy]=(i+m_iDirectionNum/2)%m_iDirectionNum;
                    
                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().Get_PositionX()==xdx && 
                            pq[pqi].top().Get_PositionY()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    Clear();
    return ""; // no route found
}
