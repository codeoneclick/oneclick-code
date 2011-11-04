//
//  CWindow.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CWindow_h
#define gEngine_CWindow_h

class CWindow
{
private:
    int m_uiWidth;
    int m_uiHeight;
    static CWindow* m_instance;
public:
    CWindow();
    ~CWindow();
    static CWindow* Instance();
    void Init(int _uiWidth, int _uiHeight);
    inline int Get_Width() { return m_uiWidth; }
    inline int Get_Height() { return m_uiHeight; }
};

#endif
