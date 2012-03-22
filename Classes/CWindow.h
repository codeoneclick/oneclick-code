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
    static int m_iScreenWidth;
    static int m_iScreenHeight;
    static int m_iOffScreenWidth;
    static int m_iOffScreenHeight;
public:
    static int Get_ScreenWidth()  { return m_iScreenWidth;  }
    static int Get_ScreenHeight() { return m_iScreenHeight; }
    static void Set_ScreenWidth(int _iWidth)   { m_iScreenWidth  = _iWidth;  }
    static void Set_ScreenHeight(int _iHeight) { m_iScreenHeight = _iHeight; } 
    
    static int Get_OffScreenWidth()  { return m_iOffScreenWidth;  }
    static int Get_OffScreenHeight() { return m_iOffScreenHeight; }
    static void Set_OffScreenWidth(int _iWidth)   { m_iOffScreenWidth  = _iWidth;  }
    static void Set_OffScreenHeight(int _iHeight) { m_iOffScreenHeight = _iHeight; } 
};

#endif
