#include "m3_M3Loader.h"

PFNGLGENBUFFERSARBPROC m3_M3Loader::glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC m3_M3Loader::glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC m3_M3Loader::glBufferDataARB = NULL;
PFNGLDELETEBUFFERSARBPROC m3_M3Loader::glDeleteBuffersARB = NULL;
PFNGLMAPBUFFERARBPROC     m3_M3Loader::glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC   m3_M3Loader::glUnmapBufferARB = NULL;


void m3_M3Loader::Initilize()
{
	if(glGenBuffersARB == NULL)
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	if(glBindBufferARB == NULL)
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	if(glBufferDataARB == NULL)
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	if(glDeleteBuffersARB == NULL)
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
	if(glMapBufferARB == NULL)
		glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
	if(glUnmapBufferARB == NULL)
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
}

m3_VertexBufferPtr* m3_M3Loader::LoadFileData(std::string value)
{
	std::ifstream inStream;
	inStream.open(value.c_str(),std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();

	m3_Header *header = (m3_Header*)fileData;
	m3_Tag *tags =(m3_Tag*)(fileData + header->tagsOffset);

	m3_Version _vertexBlockVersion = M3_UNKNOWN;
	m3_VertexBlock_v01 *_vertexBlock_v01;
	m3_VertexBlock_v02 *_vertexBlock_v02;
	m3_VertexBlock_v03 *_vertexBlock_v03;

	uint16 *indexBlock;

	m3_IndexRegionBlock *_indexRegionBlock;
	m3_RegionBlock *_regionBlock;

	m3_VertexBufferPtr *vertexBufferPtr = new m3_VertexBufferPtr();
	

	bool firstIndexBlockFlag = false;
	unsigned int _blockSize = 0;
	std::string _tagNameStr = "none";

	//int a = sizeof(BONE);
	//int b = sizeof(BONE_02);

	//int c = sizeof(m3_TagReference);

	for(unsigned int i = 0; i < header->nTags; ++i)
	{
		_tagNameStr = tags[i].tagName;
		_tagNameStr.resize(4);

		if(_tagNameStr == "LDOM") // Read global indeces for bones.
		{
			m3_TagsCutoffs *_tagsCuttoffs = (m3_TagsCutoffs*)(fileData + tags[i].blockOffset);			
			uint16 *_globalBonesIndecesList = (uint16*)(fileData + tags[_tagsCuttoffs->globalBonesIndecesList.reference].blockOffset);
			vertexBufferPtr->globalBonesIndecesList = new uint16[_tagsCuttoffs->globalBonesIndecesList.nEntries];
			for(uint32 index = 0; index < _tagsCuttoffs->globalBonesIndecesList.nEntries; ++index)
				vertexBufferPtr->globalBonesIndecesList[index] = _globalBonesIndecesList[index];
		}

		if(_tagNameStr == "FERI") // Read static matrix transform for bones.
		{
			Matrix4x4* _saticBonesMatrices = (Matrix4x4*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->staticBonesMatrices = new Matrix4x4[tags[i].blockSize];
			for(uint32 index = 0; index < tags[i].blockSize; ++index)
				vertexBufferPtr->staticBonesMatrices[index] = _saticBonesMatrices[index];
		}

		if(_tagNameStr == "_GTS") // Read animation sequence names.
		{
			m3_TagReference *_animationSequencesNames = (m3_TagReference*)(fileData + tags[i].blockOffset);
			m3_string *_names = (m3_string*)(fileData + tags[_animationSequencesNames->reference].blockOffset);
			//vertexBufferPtr->animationSequencesNames = new std::string[tags[i].blockSize];
			//for(uint32 index = 0; index < tags[i].blockSize; ++index)
			//{		
			//	vertexBufferPtr->animationSequencesNames[index] = _names[index];
			//}
			

			int a = 0;
			//m3_Tags2 *ref = (m3_Tags2*)(fileData + tags[i].blockOffset);
			//uint8 *temp = (uint8*)(fileData + tags[ref[0].a.reference].blockOffset);
			//uint32 *temp2 = (uint32*)(fileData + tags[ref[0].b.reference].blockOffset);
		}

		if(_tagNameStr == "_CTS")
		{
			SeqData* _seqData = (SeqData*)(fileData + tags[i].blockOffset);

			// Transform Id's.
			uint32 *tranfomationId = (uint32*)(fileData + tags[_seqData[0].animid.reference].blockOffset);
			vertexBufferPtr->_sequenceBlock.nTransformationIds = _seqData[0].animid.nEntries;
			vertexBufferPtr->_sequenceBlock.transformationId = new uint32[vertexBufferPtr->_sequenceBlock.nTransformationIds];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock.nTransformationIds; ++index)
				vertexBufferPtr->_sequenceBlock.transformationId[index] = tranfomationId[index];

			// Transform Indece's.
			_m3_TransformationIndex *transformtionIndex = (_m3_TransformationIndex*)(fileData + tags[_seqData[0].animindex.reference].blockOffset);
			vertexBufferPtr->_sequenceBlock.nTransformationIndeces = _seqData[0].animindex.nEntries;
			vertexBufferPtr->_sequenceBlock.transformationIndex = new _m3_TransformationIndex[vertexBufferPtr->_sequenceBlock.nTransformationIndeces];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock.nTransformationIndeces; ++index)
				vertexBufferPtr->_sequenceBlock.transformationIndex[index] = transformtionIndex[index];

			// Sequence Data's.

				// Translation data's.
			m3_AnimationData *translationDataPtr = (m3_AnimationData*)(fileData + tags[_seqData->_seqData[2].reference].blockOffset);
			vertexBufferPtr->_sequenceBlock.nTSequenceData = _seqData->_seqData[2].nEntries;
			vertexBufferPtr->_sequenceBlock.tSequenceData = new _m3_TranslationDataPtr[vertexBufferPtr->_sequenceBlock.nTSequenceData];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock.nTSequenceData; ++index)
			{
				Vector3d *vTranslationData = (Vector3d*)(fileData + tags[translationDataPtr[index].keys.reference].blockOffset);
				vertexBufferPtr->_sequenceBlock.tSequenceData[index].nFrames = translationDataPtr[index].frames.nEntries;
				vertexBufferPtr->_sequenceBlock.tSequenceData[index].keys = new Vector3d[vertexBufferPtr->_sequenceBlock.tSequenceData[index].nFrames];
				for(uint32 index_02 = 0; index_02 < vertexBufferPtr->_sequenceBlock.tSequenceData[index].nFrames; ++index_02)
					vertexBufferPtr->_sequenceBlock.tSequenceData[index].keys[index_02] = vTranslationData[index_02];
			}
				// Rotation data's.
			m3_AnimationData *rotationDataPtr = (m3_AnimationData*)(fileData + tags[_seqData->_seqData[3].reference].blockOffset);
			vertexBufferPtr->_sequenceBlock.nRSequenceData = _seqData->_seqData[3].nEntries;
			vertexBufferPtr->_sequenceBlock.rSequenceData = new _m3_RotationDataPtr[vertexBufferPtr->_sequenceBlock.nRSequenceData];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock.nRSequenceData; ++index)
			{
				QuaternionStruct *qRotationData = (QuaternionStruct*)(fileData + tags[rotationDataPtr[index].keys.reference].blockOffset);
				vertexBufferPtr->_sequenceBlock.rSequenceData[index].nFrames = rotationDataPtr[index].frames.nEntries;
				vertexBufferPtr->_sequenceBlock.rSequenceData[index].keys = new QuaternionStruct[vertexBufferPtr->_sequenceBlock.rSequenceData[index].nFrames];
				for(uint32 index_02 = 0; index_02 < vertexBufferPtr->_sequenceBlock.rSequenceData[index].nFrames; ++index_02)
					vertexBufferPtr->_sequenceBlock.rSequenceData[index].keys[index_02] = qRotationData[index_02];
			}
		}

		if(_tagNameStr == "ENOB")
		{
			BONE* _boneblock = (BONE*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->nBones = tags[i].blockSize;
			vertexBufferPtr->boneDataPtr = new m3_BoneData[vertexBufferPtr->nBones];
			for( uint32 i = 0; i < vertexBufferPtr->nBones; ++i)
			{
				vertexBufferPtr->boneDataPtr[i].rotationId = _boneblock[i].rotationId;
				vertexBufferPtr->boneDataPtr[i].translationId = _boneblock[i].translationId;

				vertexBufferPtr->boneDataPtr[i]._startPosition = _boneblock[i].position;
				vertexBufferPtr->boneDataPtr[i]._startRotation[0] = _boneblock[i].rotation[0];
				vertexBufferPtr->boneDataPtr[i]._startRotation[1] = _boneblock[i].rotation[1];
				vertexBufferPtr->boneDataPtr[i]._startRotation[2] = _boneblock[i].rotation[2];
				vertexBufferPtr->boneDataPtr[i]._startRotation[3] = _boneblock[i].rotation[3];
				vertexBufferPtr->boneDataPtr[i]._startScale = _boneblock[i].scale;

				vertexBufferPtr->boneDataPtr[i].parent = _boneblock[i].parent;

				vertexBufferPtr->boneDataPtr[i].parentPtr = NULL;
			}
		
			//for( uint32 j = 0; j < vertexBufferPtr->nBones; ++j)
			for( uint32 i = 0; i < vertexBufferPtr->nBones; ++i)
			{
				if(vertexBufferPtr->boneDataPtr[i].parent != -1)
				{
					vertexBufferPtr->boneDataPtr[i].parentPtr = &vertexBufferPtr->boneDataPtr[vertexBufferPtr->boneDataPtr[i].parent];
					//vertexBufferPtr->boneDataPtr[i]._startPosition += vertexBufferPtr->boneDataPtr[vertexBufferPtr->boneDataPtr[i].parent]._startPosition;
				}
			}
			int test01 = 0;
		}

		if(_tagNameStr == "Q4DS")
		{
			m3_AnimationData* _animblock = (m3_AnimationData*)(fileData + tags[i].blockOffset);
			int test01 = 0;
		}
		
		if(_tagNameStr == "V3DS")
		{
			m3_AnimationData* _animblock = (m3_AnimationData*)(fileData + tags[i].blockOffset);
			Vector3d *_vec = (Vector3d*)(fileData + tags[_animblock->keys.reference].blockOffset);
			int test01 = 0;
		}

		if(_tagNameStr == "3RDS")
		{
			m3_AnimationData* _animblock = (m3_AnimationData*)(fileData + tags[i].blockOffset);
			int test01 = 0;
		}

		if(_tagNameStr == "SQES")
		{
			SEQS* seqs = (SEQS*)(fileData + tags[i].blockOffset);
			int test01 = 0;
		}
		
		if(_tagNameStr == "RYAL")
		{
			LAYR* layr = (LAYR*)(fileData + tags[i].blockOffset);
			std::string _textureInFileName = (std::string)(fileData + tags[layr->name.reference].blockOffset);
		}

		if(_tagNameStr == "_VID")
		{
			_indexRegionBlock = (m3_IndexRegionBlock*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->nIndeces = _indexRegionBlock->faces.nEntries;
			indexBlock = (uint16*)(fileData + tags[_indexRegionBlock->faces.reference].blockOffset);
			_regionBlock = (m3_RegionBlock*)(fileData + tags[_indexRegionBlock->regions.reference].blockOffset);
			
			uint16 *bonelookup =  (uint16*)(fileData + tags[i + 1].blockOffset);
			int c = 0;
		}

		if(_tagNameStr == "__8U")
		{
			_blockSize = tags[i].blockSize % sizeof(m3_VertexBlock_v01);
			_vertexBlock_v01 = (m3_VertexBlock_v01*)(fileData + tags[i].blockOffset);
			if((_blockSize == 0) && (_vertexBlock_v01[0].tangent[3] == 255))
			{
				vertexBufferPtr->nVerteces = (tags[i].blockSize)/sizeof(m3_VertexBlock_v01);
			    _vertexBlock_v01 = (m3_VertexBlock_v01*)(fileData + tags[i].blockOffset);
				_vertexBlockVersion = M3_01;
			}

			_blockSize = tags[i].blockSize % sizeof(m3_VertexBlock_v02);
			_vertexBlock_v02 = (m3_VertexBlock_v02*)(fileData + tags[i].blockOffset);
			if((_blockSize == 0) && (_vertexBlock_v02[0].tangent[3] == 255))
			{
				vertexBufferPtr->nVerteces = (tags[i].blockSize)/sizeof(m3_VertexBlock_v02);
			    _vertexBlock_v02 = (m3_VertexBlock_v02*)(fileData + tags[i].blockOffset);
				_vertexBlockVersion = M3_02;
			}

			_blockSize = tags[i].blockSize % sizeof(m3_VertexBlock_v03);
			if(_blockSize == 0 && _vertexBlockVersion != M3_02)
			{
				vertexBufferPtr->nVerteces = (tags[i].blockSize)/sizeof(m3_VertexBlock_v03);
			    _vertexBlock_v03 = (m3_VertexBlock_v03*)(fileData + tags[i].blockOffset);
				_vertexBlockVersion = M3_03;
			}
		}
	}

	vertexBufferPtr->vertexDataPtr = new m3_VertexData[vertexBufferPtr->nVerteces];
	vertexBufferPtr->normalDataPtr = new m3_NormalData[vertexBufferPtr->nVerteces];
	vertexBufferPtr->textureCoordPtr = new m3_TextureCoordData[vertexBufferPtr->nVerteces];
	vertexBufferPtr->boneVertexDataPtr = new m3_BoneVertexData[vertexBufferPtr->nVerteces];

	float wNormal = 0.0f; 

	for(unsigned int i = 0; i < vertexBufferPtr->nVerteces; ++i)
	{
		switch(_vertexBlockVersion)
		{
			case M3_01:
				vertexBufferPtr->vertexDataPtr[i].x = _vertexBlock_v01[i].position[0];
				vertexBufferPtr->vertexDataPtr[i].y = _vertexBlock_v01[i].position[1];
				vertexBufferPtr->vertexDataPtr[i].z = _vertexBlock_v01[i].position[2];

				vertexBufferPtr->normalDataPtr[i].x = ((float)2*_vertexBlock_v01[i].normal[0]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].y = ((float)2*_vertexBlock_v01[i].normal[1]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].z = ((float)2*_vertexBlock_v01[i].normal[2]/255.0f - 1.0f);
				wNormal = (float) _vertexBlock_v01[i].normal[3]/255.0f;
				if(wNormal)
				{
					vertexBufferPtr->normalDataPtr[i].x /= wNormal;
					vertexBufferPtr->normalDataPtr[i].y /= wNormal; 
					vertexBufferPtr->normalDataPtr[i].z /= wNormal;
				}
				vertexBufferPtr->textureCoordPtr[i].u = (float)_vertexBlock_v01[i].uv[0]/2048.0f;
				vertexBufferPtr->textureCoordPtr[i].v = (float)_vertexBlock_v01[i].uv[1]/2048.0f;

				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[0] = _vertexBlock_v01[i].boneIndex[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[1] = _vertexBlock_v01[i].boneIndex[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[2] = _vertexBlock_v01[i].boneIndex[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[3] = _vertexBlock_v01[i].boneIndex[3];

				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[0] = _vertexBlock_v01[i].boneWeight[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[1] = _vertexBlock_v01[i].boneWeight[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[2] = _vertexBlock_v01[i].boneWeight[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[3] = _vertexBlock_v01[i].boneWeight[3];

				//printf("%i     ,",_vertexBlock_v03[i].boneWeight[0]);

			break;
			case M3_02:
				vertexBufferPtr->vertexDataPtr[i].x = _vertexBlock_v02[i].position[0];
				vertexBufferPtr->vertexDataPtr[i].y = _vertexBlock_v02[i].position[1];
				vertexBufferPtr->vertexDataPtr[i].z = _vertexBlock_v02[i].position[2];

				vertexBufferPtr->normalDataPtr[i].x = ((float)2*_vertexBlock_v02[i].normal[0]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].y = ((float)2*_vertexBlock_v02[i].normal[1]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].z = ((float)2*_vertexBlock_v02[i].normal[2]/255.0f - 1.0f);
				wNormal = (float) _vertexBlock_v02[i].normal[3]/255.0f;
				if(wNormal)
				{
					vertexBufferPtr->normalDataPtr[i].x /= wNormal;
					vertexBufferPtr->normalDataPtr[i].y /= wNormal; 
					vertexBufferPtr->normalDataPtr[i].z /= wNormal;
				}
				vertexBufferPtr->textureCoordPtr[i].u = (float)_vertexBlock_v02[i].uv[0]/2048.0f;
				vertexBufferPtr->textureCoordPtr[i].v = (float)_vertexBlock_v02[i].uv[1]/2048.0f;

				//if(_vertexBlock_v02[i].boneIndex[0] >= 12)
				//	int aaa = 0;
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[0] = _vertexBlock_v02[i].boneIndex[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[1] = _vertexBlock_v02[i].boneIndex[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[2] = _vertexBlock_v02[i].boneIndex[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[3] = _vertexBlock_v02[i].boneIndex[3];

				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[0] = _vertexBlock_v02[i].boneWeight[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[1] = _vertexBlock_v02[i].boneWeight[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[2] = _vertexBlock_v02[i].boneWeight[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[3] = _vertexBlock_v02[i].boneWeight[3];

				//printf("%i     ,",_vertexBlock_v01[i].boneWeight[0]);

			break;
			case M3_03:
				vertexBufferPtr->vertexDataPtr[i].x = _vertexBlock_v03[i].position[0];
				vertexBufferPtr->vertexDataPtr[i].y = _vertexBlock_v03[i].position[1];
				vertexBufferPtr->vertexDataPtr[i].z = _vertexBlock_v03[i].position[2];

				vertexBufferPtr->normalDataPtr[i].x = ((float)2*_vertexBlock_v03[i].normal[0]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].y = ((float)2*_vertexBlock_v03[i].normal[1]/255.0f - 1.0f);
				vertexBufferPtr->normalDataPtr[i].z = ((float)2*_vertexBlock_v03[i].normal[2]/255.0f - 1.0f);
				wNormal = (float) _vertexBlock_v03[i].normal[3]/255.0f;
				if(wNormal)
				{
					vertexBufferPtr->normalDataPtr[i].x /= wNormal;
					vertexBufferPtr->normalDataPtr[i].y /= wNormal; 
					vertexBufferPtr->normalDataPtr[i].z /= wNormal;
				}
				vertexBufferPtr->textureCoordPtr[i].u = (float)_vertexBlock_v03[i].uv[0]/2048.0f;
				vertexBufferPtr->textureCoordPtr[i].v = (float)_vertexBlock_v03[i].uv[1]/2048.0f;

				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[0] = _vertexBlock_v03[i].boneIndex[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[1] = _vertexBlock_v03[i].boneIndex[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[2] = _vertexBlock_v03[i].boneIndex[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[3] = _vertexBlock_v03[i].boneIndex[3];

				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[0] = _vertexBlock_v03[i].boneWeight[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[1] = _vertexBlock_v03[i].boneWeight[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[2] = _vertexBlock_v03[i].boneWeight[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[3] = _vertexBlock_v03[i].boneWeight[3];

				//printf("%i     ,",_vertexBlock_v03[i].boneWeight[0]);
			break;
		}
	}

	vertexBufferPtr->indecesPtr = new unsigned int[vertexBufferPtr->nIndeces];

	for(unsigned int i = 0; i < vertexBufferPtr->nIndeces; ++i)
		vertexBufferPtr->indecesPtr[i] = indexBlock[i];

	vertexBufferPtr->nRegions = _indexRegionBlock->regions.nEntries;
	vertexBufferPtr->regionDataPtr = new m3_RegionData[vertexBufferPtr->nRegions];

	for(unsigned int i = 0; i < vertexBufferPtr->nRegions; ++i)
	{
		vertexBufferPtr->regionDataPtr[i].nIndices = _regionBlock[i].nIndices;
		vertexBufferPtr->regionDataPtr[i].nVertices = _regionBlock[i].nVertices;
		vertexBufferPtr->regionDataPtr[i].ofsIndices = _regionBlock[i].ofsIndices;
		vertexBufferPtr->regionDataPtr[i].ofsVertices = _regionBlock[i].ofsVertices;
	}

	//delete[] fileData;
	return vertexBufferPtr;
}

m3_VertexBufferID*  m3_M3Loader::Load(m3_VertexBufferPtr* value)
{
	if(glGenBuffersARB == NULL)
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	if(glBindBufferARB == NULL)
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	if(glBufferDataARB == NULL)
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	if(glDeleteBuffersARB == NULL)
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
	if(glMapBufferARB == NULL)
		glMapBufferARB = (PFNGLMAPBUFFERARBPROC)wglGetProcAddress("glMapBufferARB");
	if(glUnmapBufferARB == NULL)
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");

	m3_VertexBufferID* vertexBufferId = new m3_VertexBufferID();

	glGenBuffersARB( 1, &vertexBufferId->vertexId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->vertexId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->vertexDataPtr, GL_STREAM_DRAW_ARB );

	glGenBuffersARB( 1, &vertexBufferId->textureCoordId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->textureCoordId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*2*sizeof(float), value->textureCoordPtr, GL_STREAM_DRAW_ARB );

	glGenBuffersARB( 1, &vertexBufferId->normalId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->normalId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->normalDataPtr, GL_STREAM_DRAW_ARB );

	return vertexBufferId;
}