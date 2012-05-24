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
#include <vector>

class CIndexBuffer
{ 
private:
    unsigned short* m_pSourceData;
    unsigned short* m_pWorkingSourceData;
    GLuint m_iHandle;
    unsigned int m_iNumIndexes;
    unsigned int m_iNumWorkingIndexes;
    bool m_bIsInVRAM;
public:
    CIndexBuffer(unsigned int _iNumIndexes);
    ~CIndexBuffer(void);
    
    unsigned int Get_NumIndexes(void) { return m_iNumIndexes; }
    unsigned int Get_NumWorkingIndexes(void) { return m_iNumWorkingIndexes; }
    unsigned short* Get_SourceData(void);
    unsigned short* Get_SourceDataFromVRAM(void);
    void Set_WorkingSourceData(unsigned short* _pSourceData, unsigned int _iNumIndexes);
    void Enable(void);
    void Disable(void);
    void CommitFromRAMToVRAM(void);
};


#endif
