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
#include "CNavigationMesh.h"

class CLandscape : public INode
{
protected:
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    
    CMesh* m_pVisualNavigationMeshRef;
    CShader* m_pVisualNavigationMeshShader;
    
    CHeightMapSetter* m_pHeightMapSetter;
    CNavigationMesh* m_pNavigationMesh;
    
    bool m_bIsNavigationMeshDebug;
    
    CShader* m_pShaderPreEdgeDetect;
    CShader* m_pShaderNormalDepth;
public:
    CLandscape(void);
    virtual ~CLandscape();
    virtual void Load(IResource::SResource _tResource);
    virtual void OnTouchEvent(void);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    CHeightMapSetter* Get_HeightMapSetter(void) { return m_pHeightMapSetter; }
    unsigned int Get_Width(void) { return m_iWidth; }
    unsigned int Get_Height(void) { return m_iHeight; }
};

#endif
