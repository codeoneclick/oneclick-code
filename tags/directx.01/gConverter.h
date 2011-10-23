#pragma once
#ifndef _G_CONVERTER_H_
#define _G_CONVERTER_H_

#include <fstream>
#include <string>
#include "gM3FileFormat.h"
#include "gM2FileFormat.h"

class gConverter
{
private :
	static char* _readVertexData(const char* fileName);
	static char* _readIndexData(const char* fileName);
	static void _writeToGSMFile(const char* fileName, gM3VertexBlock *vertexBlock, short *indexBlock,unsigned int nVerteces, unsigned int nIndeces);
	static void _writeToGSMFile(const char* fileName, gM2VertexBlock *vertexBlock, short *indexBlock,unsigned int nVerteces, unsigned int nIndeces);
	static void _writeGSMHeader(FILE *file,unsigned int nVerteces, unsigned int nIndeces);

public :
	gConverter() { };
	static void ConvertM2(const char* fileName);
	static void ConvertM3(const char* fileName);
};
#endif
