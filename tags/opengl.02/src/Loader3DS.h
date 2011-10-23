#ifndef _LOADER3DS_H_
#define _LOADER3DS_H_

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "StructDef.h"
#include "VB.h"

class Loader3DS
{
public :
		static VertexBufferPtr* LoadFileData(std::string value);
		static void WriteInVideoMemory(VertexBufferPtr* value);
};

#endif