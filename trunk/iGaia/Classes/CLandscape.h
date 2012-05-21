//
//  CLandscape.h
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CLandscape_h
#define iGaia_CLandscape_h

#include "INode.h"
#include <map>
#include "CHeightMapSetter.h"

class CLandscape : public INode
{
protected:
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    CHeightMapSetter* m_pHeightMapSetter;
public:
    CLandscape(void);
    virtual ~CLandscape(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    CHeightMapSetter* Get_HeightMapSetter(void) { return m_pHeightMapSetter; }
    unsigned int Get_Width(void) { return m_iWidth; }
    unsigned int Get_Height(void) { return m_iHeight; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
