#ifndef _LOADER3DS_H_
#define _LOADER3DS_H_

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "StructExt.h"
#include "VBExtension.h"

namespace loader
{
class Loader3DS
{
public :
	static type::VertexBufferData* LoadFileData(std::string value);
	static void WriteInVideoMemory(type::VertexBufferData* value);
};
};

#endif