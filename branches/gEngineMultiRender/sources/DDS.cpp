#include "DDS.h"

using namespace Loader;

PFNGLCOMPRESSEDTEXIMAGE2DARBPROC CDDS::glCompressedTexImage2DARB = NULL;

CDDS::SDDSFile *CDDS::ReadData(std::string value)
{
    CDDS::SDDSFile *pDDSImageData;
    DDSURFACEDESC2 ddsd;
    char header[4];
    FILE *pFile;
    int factor;
    int bufferSize;

	try
	{
		pFile = fopen( value.c_str(), "rb" );
	}
	catch(int exception)
	{
		printf("TEXTURE %s NOT FOUND. %i ERROR\n",value.c_str(), exception);
		return NULL;
	}

    fread( header, 1, 4, pFile );

    if( strncmp( header, "DDS ", 4 ) != 0 )
    {
		printf("TEXTURE %s DOESN'T VALID .DDS FILE.\n",value.c_str());
		fclose( pFile );
        return NULL;
    }

    fread( &ddsd, sizeof(ddsd), 1, pFile );

    pDDSImageData = (CDDS::SDDSFile*) malloc(sizeof(CDDS::SDDSFile));

    memset( pDDSImageData, 0, sizeof(CDDS::SDDSFile) );

    switch( ddsd.ddpfPixelFormat.dwFourCC )
    {
        case FOURCC_DXT1:
            // DXT1's compression ratio is 8:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
            break;

        case FOURCC_DXT3:
            // DXT3's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
            break;

        case FOURCC_DXT5:
            // DXT5's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
            break;

        default:
			printf("TEXTURE %s DOESN'T COMPRESS.\n",value.c_str());
			fclose( pFile );
            return NULL;
    }

    if( ddsd.dwLinearSize == 0 )
    {
		printf("TEXTURE %s READ ERROR.\n",value.c_str());
		fclose( pFile );
		return NULL;
    }

    if( ddsd.dwMipMapCount > 1 )
        bufferSize = ddsd.dwLinearSize * factor;
    else
        bufferSize = ddsd.dwLinearSize;

    pDDSImageData->pixels = (unsigned char*)malloc(bufferSize * sizeof(unsigned char));

    fread( pDDSImageData->pixels, 1, bufferSize, pFile );

    fclose( pFile );

    pDDSImageData->width      = ddsd.dwWidth;
    pDDSImageData->height     = ddsd.dwHeight;
    pDDSImageData->numMipMaps = ddsd.dwMipMapCount;

    if( ddsd.ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        pDDSImageData->components = 3;
    else
        pDDSImageData->components = 4;

    return pDDSImageData;
}


unsigned int CDDS::Commit(CDDS::SDDSFile *value)
{
	if(glCompressedTexImage2DARB == NULL)
		glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)wglGetProcAddress("glCompressedTexImage2DARB");
	GLuint textureId = -1;
    if(value != NULL)
    {
        int nBlockSize = -1;

        if( value->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
            nBlockSize = 8;
        else
            nBlockSize = 16;

        glGenTextures( 1, &textureId );
        glBindTexture( GL_TEXTURE_2D, textureId );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        int nSize = -1;
        int nOffset = 0;

		for( int i = 0; i < value->numMipMaps; ++i )
        {
			if( value->width  == 0 ) value->width  = 1;
			if( value->height == 0 ) value->height = 1;

            nSize = ((value->width + 3)/4) * ((value->height + 3)/4) * nBlockSize;

            glCompressedTexImage2DARB( GL_TEXTURE_2D,
                                       i,
                                       value->format,
                                       value->width,
                                       value->height,
                                       0,
                                       nSize,
                                       value->pixels + nOffset );

            nOffset += nSize;

            value->width  = (value->width  / 2);
            value->height = (value->height / 2);
        }
    }

    if( value != NULL )
    {
        if( value->pixels != NULL )
            free( value->pixels );

        free( value );
    }

	return textureId;
}
