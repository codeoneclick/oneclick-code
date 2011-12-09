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
private:
    static int m_iWidth;
    static int m_iHeight;
public:
    static int Get_Width()  { return m_iWidth;  }
    static int Get_Height() { return m_iHeight; }
    static void Set_Width(int _iWidth)   { m_iWidth  = _iWidth;  }
    static void Set_Height(int _iHeight) { m_iHeight = _iHeight; } 
};

#endif
