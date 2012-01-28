//
//  CWindow.h
//  gEngine
//
//  Created by sergey.sergeev on 12/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CWindow_h
#define gEngine_CWindow_h

class CWindow
{
public:
    struct SViewport
    {
        union 
        {
            struct 
            {
                int m_iX;
                int m_iY;
                int m_iWidth;
                int m_iHeight;
            };
            int v[4];
        }; 
    };
private:
    static int m_iWidth;
    static int m_iHeight;
    static SViewport m_tViewport;
public:
    static int Get_Width()  { return m_iWidth;  }
    static int Get_Height() { return m_iHeight; }
    static void Set_Width(int _iWidth)   { m_iWidth  = _iWidth;  }
    static void Set_Height(int _iHeight) { m_iHeight = _iHeight; } 
    static void Set_Viewport(int _iX, int _iY, int _iWidth, int _iHeight) { m_tViewport.m_iX = _iX; m_tViewport.m_iY = _iY;
        m_tViewport.m_iWidth = _iWidth; m_tViewport.m_iHeight = _iHeight; }
    static SViewport Get_Viewport(void) { return m_tViewport; }
};

#endif
