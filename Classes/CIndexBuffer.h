//
//  CIndexBuffer.h
//  gEngine
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CIndexBuffer_h
#define gEngine_CIndexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdlib.h>
#include <string.h>

class CIndexBuffer
{ 
private:
    unsigned short* m_pData;
    GLuint m_hIBHandle;
    unsigned int m_iNumIndexes;
    bool m_bVRAM;
public:
    CIndexBuffer(unsigned int _iNumIndexes);
    ~CIndexBuffer();
    
    unsigned int Get_NumIndexes(void) { return m_iNumIndexes; }
    unsigned short* Get_Data(void) { return m_pData; }
    void Enable(void);
    void Disable(void);
    void Commit(void);
};


#endif
