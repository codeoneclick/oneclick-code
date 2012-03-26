//
//  CIndexBuffer.h
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CIndexBuffer_h
#define iGaia_CIndexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdlib.h>
#include <string.h>

class CIndexBuffer
{ 
private:
    unsigned short* m_pData;
    GLuint m_iHandle;
    unsigned int m_iNumIndexes;
    bool m_bIsInVRAM;
public:
    CIndexBuffer(unsigned int _iNumIndexes);
    ~CIndexBuffer();
    
    unsigned int Get_NumIndexes(void) { return m_iNumIndexes; }
    unsigned short* Get_Data(void);
    unsigned short* Get_DataFromVRAM(void);
    void Enable(void);
    void Disable(void);
    void CommitFromRAMToVRAM(void);
};


#endif
