//
//  CBillboardEffect.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CBillboardEffect__
#define __iGaia__CBillboardEffect__

#include <iostream>
#include "INode.h"

class CBillboardEffect : public INode
{
protected:
    unsigned int m_iNumTextureChunks;
    glm::vec2 m_vSizeTextureChunk;
public:
    CBillboardEffect(void);
    ~CBillboardEffect(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
    
    inline void Set_NumTextureChunks(unsigned int _iNumTextureChunks) { m_iNumTextureChunks = _iNumTextureChunks; }
    inline void Set_SizeTextureChunk(glm::vec2 _vSizeTextureChunk) { m_vSizeTextureChunk = _vSizeTextureChunk; }
};

#endif /* defined(__iGaia__CBillboardEffect__) */
