#pragma once
#ifndef _M3_HEIGHTMAP_H_
#define _M3_HEIGHTMAP_H_

#include <windows.h>
#include <stdlib.h>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
//#include <fstream>
#include "glext.h"
#include "m3_FileFormat.h"
#include "m3_Core.h"

class m3_Heightmap
{
	private :
		unsigned int _width;
		unsigned int _height;
		float **_heightmap;

		PFNGLGENBUFFERSARBPROC glGenBuffersARB;					
		PFNGLBINDBUFFERARBPROC glBindBufferARB;					
		PFNGLBUFFERDATAARBPROC glBufferDataARB;					
		PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;

		m3_VertexBufferPtr* _vertexBufferPtr;
		m3_VertexBufferID*  _vertexBufferId;

	public :
		m3_Heightmap();
		void Load(std::string value);
		void Update();
		void Render();
};

#endif