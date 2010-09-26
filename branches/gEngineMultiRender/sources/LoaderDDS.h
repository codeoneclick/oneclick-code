#ifndef _LOADERDDS_H_
#define _LOADERDDS_H_
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ddraw.h> 
#include "glext.h"
#include <stdlib.h>
#include <fstream>
#include "StructExt.h"

namespace loader
{
class LoaderDDS
{
private :

public :
	static unsigned int Load(type::DDSImageData* value);
	static type::DDSImageData* LoadImageData(std::string value);
	static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
};
};

#endif

