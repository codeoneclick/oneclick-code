#pragma once
#ifndef _M3_3DSLOADER_H_
#define _M3_3DSLOADER_H_

#include <windows.h>
#include <string>
#include <vector>
//#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "m3_FileFormat.h"

class m3_3DSLoader
{
private :
	    static void _CalculateNormals(m3_VertexBufferPtr* _vertexBufferPtr);
public :
		static void Initilize();

		static PFNGLGENBUFFERSARBPROC glGenBuffersARB;					
		static PFNGLBINDBUFFERARBPROC glBindBufferARB;					
		static PFNGLBUFFERDATAARBPROC glBufferDataARB;					
		static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;

		static m3_VertexBufferPtr* LoadFileData(std::string value);
		static m3_VertexBufferID*  Load(m3_VertexBufferPtr* value);
};

#endif