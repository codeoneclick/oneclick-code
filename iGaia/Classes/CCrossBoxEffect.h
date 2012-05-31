//
//  CCrossBoxEffect.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CCrossBoxEffect__
#define __iGaia__CCrossBoxEffect__

#include <iostream>
#include "INode.h"

class CCrossBoxEffect : public INode
{
protected:
    struct SFrame
    {
        glm::vec2 m_vTexcoord[4];
    };
    unsigned int m_iNumTextureChunks;
    glm::vec2 m_vSizeTextureChunk;
    glm::vec2 m_vSizeTextureAtlas;
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    glm::vec2 m_vSize;
    unsigned int m_iTotalFrames;
    unsigned int m_iCurrentFrame;
    SFrame* m_pFrames;
public:
    CCrossBoxEffect(void);
    ~CCrossBoxEffect(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
    
    inline void Set_NumTextureChunks(unsigned int _iNumTextureChunks) { m_iNumTextureChunks = _iNumTextureChunks; }
    inline void Set_SizeTextureChunk(glm::vec2 _vSizeTextureChunk) { m_vSizeTextureChunk = _vSizeTextureChunk; }
    inline void Set_SizeTextureAtlas(glm::vec2 _vSizeTextureAtlas) { m_vSizeTextureAtlas = _vSizeTextureAtlas; }
};


#endif /* defined(__iGaia__CCrossBoxEffect__) */
