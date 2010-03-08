#include "m3_DDSLoader.h"


DDS_IMAGE_DATA *m3_DDSLoader::_LoadImageData( const char *fileName )
{
    DDS_IMAGE_DATA *pDDSImageData;
    DDSURFACEDESC2 ddsd;
    char filecode[4];
    FILE *pFile;
    int factor;
    int bufferSize;

    // Open the file
    pFile = fopen( fileName, "rb" );

    if( pFile == NULL )
    {
        char str[255];
        sprintf( str, "loadDDSTextureFile couldn't find, or failed to load \"%s\"", fileName );
        MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
        return NULL;
    }

    // Verify the file is a true .dds file
    fread( filecode, 1, 4, pFile );

    if( strncmp( filecode, "DDS ", 4 ) != 0 )
    {
        char str[255];
        sprintf( str, "The file \"%s\" doesn't appear to be a valid .dds file!", fileName );
        MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
        fclose( pFile );
        return NULL;
    }

    // Get the surface descriptor
    fread( &ddsd, sizeof(ddsd), 1, pFile );

    pDDSImageData = (DDS_IMAGE_DATA*) malloc(sizeof(DDS_IMAGE_DATA));

    memset( pDDSImageData, 0, sizeof(DDS_IMAGE_DATA) );

    //
    // This .dds loader supports the loading of compressed formats DXT1, DXT3 
    // and DXT5.
    //

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
            char str[255];
            sprintf( str, "The file \"%s\" doesn't appear to be compressed "
                "using DXT1, DXT3, or DXT5!", fileName );
            MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
            return NULL;
    }

    //
    // How big will the buffer need to be to load all of the pixel data 
    // including mip-maps?
    //

    if( ddsd.dwLinearSize == 0 )
    {
        MessageBox( NULL, "dwLinearSize is 0!","ERROR",
            MB_OK|MB_ICONEXCLAMATION);
    }

    if( ddsd.dwMipMapCount > 1 )
        bufferSize = ddsd.dwLinearSize * factor;
    else
        bufferSize = ddsd.dwLinearSize;

    pDDSImageData->pixels = (unsigned char*)malloc(bufferSize * sizeof(unsigned char));

    fread( pDDSImageData->pixels, 1, bufferSize, pFile );

    // Close the file
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


void m3_DDSLoader::Load( const char* fileName,GLuint *textureId)
{
    DDS_IMAGE_DATA *pDDSImageData = _LoadImageData(fileName);

    if( pDDSImageData != NULL )
    {
        int nHeight     = pDDSImageData->height;
        int nWidth      = pDDSImageData->width;
        int nNumMipMaps = pDDSImageData->numMipMaps;

        int nBlockSize;

        if( pDDSImageData->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
            nBlockSize = 8;
        else
            nBlockSize = 16;

        glGenTextures( 1, textureId );
        glBindTexture( GL_TEXTURE_2D, *textureId );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        int nSize;
        int nOffset = 0;

        // Load the mip-map levels

        for( int i = 0; i < nNumMipMaps; ++i )
        {
            if( nWidth  == 0 ) nWidth  = 1;
            if( nHeight == 0 ) nHeight = 1;

            nSize = ((nWidth+3)/4) * ((nHeight+3)/4) * nBlockSize;

			PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)wglGetProcAddress("glCompressedTexImage2DARB");
            glCompressedTexImage2DARB( GL_TEXTURE_2D,
                                       i,
                                       pDDSImageData->format,
                                       nWidth,
                                       nHeight,
                                       0,
                                       nSize,
                                       pDDSImageData->pixels + nOffset );

            nOffset += nSize;

            // Half the image size for the next mip-map level...
            nWidth  = (nWidth  / 2);
            nHeight = (nHeight / 2);
        }
    }

    if( pDDSImageData != NULL )
    {
        if( pDDSImageData->pixels != NULL )
            free( pDDSImageData->pixels );

        free( pDDSImageData );
    }
}
