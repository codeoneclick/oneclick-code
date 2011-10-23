#ifndef _DDS_H_
#define _DDS_H_
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ddraw.h> 
#include "glext.h"
#include <stdlib.h>
#include <fstream>
#include "StructExt.h"

namespace Loader
{
class CDDS
{
public :
	struct SDDSFile
	{
		int           width;
		int           height;
		int           components;
		unsigned int  format;
		int           numMipMaps;
		unsigned char *pixels;
	};

public :
	static unsigned int Commit(SDDSFile* value);
	static SDDSFile* ReadData(std::string value);
	static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
};
};

#endif

