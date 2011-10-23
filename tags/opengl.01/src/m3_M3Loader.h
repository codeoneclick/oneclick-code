#pragma once
#ifndef _M3_M3LOADER_H_
#define _M3_M3LOADER_H_

#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "m3_FileFormat.h"
#include "m3_VBO.h"


class m3_M3Loader
{
	private :
					
	public :
		static m3_VertexBufferPtr* LoadFileData(std::string value);
		static m3_VertexBufferID*  Load(m3_VertexBufferPtr* value);
};

#endif