#include "m3_M3Loader.h"


m3_VertexBufferPtr* m3_M3Loader::LoadFileData(std::string value)
{
	/*std::ifstream inStream;
	inStream.open(value.c_str(),std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();

	/*inStream.open("Content\\models\\test.mdx",std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize2 = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData2 = new char[fileSize2];
	inStream.read(fileData2,fileSize2);
	inStream.close();

	std::string fileStrData = "";
	for(uint32 ind =0; ind < fileSize2; ++ind)
		fileStrData += fileData2[ind];
	//new std::string( fileData2,0,fileSize2);
	//memcpy(&fileStrData,fileData2,fileSize2);
	//strcpy(fileStrData.,fileData2);

	std::vector<int> vertexDataPtrInFile;
	uint32 foundPositionInFile = 0;
	while(foundPositionInFile != std::string::npos)
	{
		foundPositionInFile = fileStrData.find("VRTX" + (foundPositionInFile + 1));
		vertexDataPtrInFile.push_back(foundPositionInFile);
	}

	int nnn = fileStrData.length();

	//size_t nnn = fileStrData.length();
	nnn = fileStrData.find("VRTX");
	
	uint32 *verSize = (uint32*)(fileData2 + nnn + 4);
	Vector3d *verValue = (Vector3d*)(fileData2 + nnn + 8);

	nnn = fileStrData.find("NRMS");
	verSize = (uint32*)(fileData2 + nnn + 4);
	Vector3d *nrmValue = (Vector3d*)(fileData2 + nnn + 8);

	nnn = fileStrData.find("UVBS");
	verSize = (uint32*)(fileData2 + nnn + 4);
	

	char* nameTag = (char*)(fileData2 + sizeof(uint32)*4);
	uint32 *modlSize = (uint32*)(fileData2 + sizeof(uint32)*5);*/

	/*m3_Header *header = (m3_Header*)fileData;
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
		}

		if(_tagNameStr == "_CTS")
		{
			SeqData* _seqData = (SeqData*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->nSequences = tags[i].blockSize;
			vertexBufferPtr->_sequenceBlock = new _m3_SequenceBlock[vertexBufferPtr->nSequences];
			for(uint32 indexSeq = 0; indexSeq < vertexBufferPtr->nSequences; ++indexSeq)
			{
			// Transform Id's.
			uint32 *tranfomationId = (uint32*)(fileData + tags[_seqData[indexSeq].animid.reference].blockOffset);
			vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIds = _seqData[indexSeq].animid.nEntries;
			vertexBufferPtr->_sequenceBlock[indexSeq].transformationId = new uint32[vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIds];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIds; ++index)
				vertexBufferPtr->_sequenceBlock[indexSeq].transformationId[index] = tranfomationId[index];

			// Transform Indece's.
			_m3_TransformationIndex *transformtionIndex = (_m3_TransformationIndex*)(fileData + tags[_seqData[indexSeq].animindex.reference].blockOffset);
			vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIndeces = _seqData[indexSeq].animindex.nEntries;
			vertexBufferPtr->_sequenceBlock[indexSeq].transformationIndex = new _m3_TransformationIndex[vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIndeces];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock[indexSeq].nTransformationIndeces; ++index)
				vertexBufferPtr->_sequenceBlock[indexSeq].transformationIndex[index] = transformtionIndex[index];

			// Sequence Data's.

				// Translation data's.
			m3_AnimationData *translationDataPtr = (m3_AnimationData*)(fileData + tags[_seqData[indexSeq]._seqData[2].reference].blockOffset);
			vertexBufferPtr->_sequenceBlock[indexSeq].nTSequenceData = _seqData[indexSeq]._seqData[2].nEntries;
			vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData = new _m3_TranslationDataPtr[vertexBufferPtr->_sequenceBlock[indexSeq].nTSequenceData];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock[indexSeq].nTSequenceData; ++index)
			{
				Vector3d *vTranslationData = (Vector3d*)(fileData + tags[translationDataPtr[index].keys.reference].blockOffset);
				vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData[index].nFrames = translationDataPtr[index].frames.nEntries;
				vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData[index].keys = new Vector3d[vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData[index].nFrames];
				for(uint32 index_02 = 0; index_02 < vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData[index].nFrames; ++index_02)
					vertexBufferPtr->_sequenceBlock[indexSeq].tSequenceData[index].keys[index_02] = vTranslationData[index_02];
			}
				// Rotation data's.
			m3_AnimationData *rotationDataPtr = (m3_AnimationData*)(fileData + tags[_seqData[indexSeq]._seqData[3].reference].blockOffset);
			vertexBufferPtr->_sequenceBlock[indexSeq].nRSequenceData = _seqData[indexSeq]._seqData[3].nEntries;
			vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData = new _m3_RotationDataPtr[vertexBufferPtr->_sequenceBlock[indexSeq].nRSequenceData];
			for(uint32 index = 0; index < vertexBufferPtr->_sequenceBlock[indexSeq].nRSequenceData; ++index)
			{
				QuaternionStruct *qRotationData = (QuaternionStruct*)(fileData + tags[rotationDataPtr[index].keys.reference].blockOffset);
				vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData[index].nFrames = rotationDataPtr[index].frames.nEntries;
				vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData[index].keys = new QuaternionStruct[vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData[index].nFrames];
				for(uint32 index_02 = 0; index_02 < vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData[index].nFrames; ++index_02)
					vertexBufferPtr->_sequenceBlock[indexSeq].rSequenceData[index].keys[index_02] = qRotationData[index_02];
			}
			}
		}

		if(_tagNameStr == "ENOB")
		{
			BONE* _boneblock = (BONE*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->nBones = tags[i].blockSize;
			vertexBufferPtr->boneDataPtr = new m3_BoneData[vertexBufferPtr->nBones];
			for( uint32 index = 0; index < vertexBufferPtr->nBones; ++index)
			{
				vertexBufferPtr->boneDataPtr[index].rotationId = _boneblock[index].rotationId;
				vertexBufferPtr->boneDataPtr[index].translationId = _boneblock[index].translationId;
				vertexBufferPtr->boneDataPtr[index]._startPosition = _boneblock[index].position;
				vertexBufferPtr->boneDataPtr[index]._startRotation[0] = _boneblock[index].rotation[0];
				vertexBufferPtr->boneDataPtr[index]._startRotation[1] = _boneblock[index].rotation[1];
				vertexBufferPtr->boneDataPtr[index]._startRotation[2] = _boneblock[index].rotation[2];
				vertexBufferPtr->boneDataPtr[index]._startRotation[3] = _boneblock[index].rotation[3];
				vertexBufferPtr->boneDataPtr[index]._startScale = _boneblock[index].scale;
				vertexBufferPtr->boneDataPtr[index].parent = _boneblock[index].parent;
				vertexBufferPtr->boneDataPtr[index].parentPtr = NULL;
			}
			for( uint32 index = 0; index < vertexBufferPtr->nBones; ++index)
			{
				if(vertexBufferPtr->boneDataPtr[index].parent != -1)
				{
					vertexBufferPtr->boneDataPtr[index].parentPtr = &vertexBufferPtr->boneDataPtr[vertexBufferPtr->boneDataPtr[index].parent];
				}
			}
		}
		
		if(_tagNameStr == "RYAL") // Read textures names.
		{
			LAYR* layr = (LAYR*)(fileData + tags[i].blockOffset);
			std::string _textureInFileName = (std::string)(fileData + tags[layr->name.reference].blockOffset);
		}

		if(_tagNameStr == "_VID") // Read index data block.
		{
			_indexRegionBlock = (m3_IndexRegionBlock*)(fileData + tags[i].blockOffset);
			vertexBufferPtr->nIndeces = _indexRegionBlock->faces.nEntries;
			indexBlock = (uint16*)(fileData + tags[_indexRegionBlock->faces.reference].blockOffset);
			_regionBlock = (m3_RegionBlock*)(fileData + tags[_indexRegionBlock->regions.reference].blockOffset);	
		}

		if(_tagNameStr == "__8U")// Read vertex data block.
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

				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[0] = _vertexBlock_v02[i].boneIndex[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[1] = _vertexBlock_v02[i].boneIndex[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[2] = _vertexBlock_v02[i].boneIndex[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneIndex[3] = _vertexBlock_v02[i].boneIndex[3];

				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[0] = _vertexBlock_v02[i].boneWeight[0];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[1] = _vertexBlock_v02[i].boneWeight[1];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[2] = _vertexBlock_v02[i].boneWeight[2];
				vertexBufferPtr->boneVertexDataPtr[i].boneWeight[3] = _vertexBlock_v02[i].boneWeight[3];
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

	delete[] fileData;
	return vertexBufferPtr;*/
	return NULL;
}

m3_VertexBufferID*  m3_M3Loader::Load(m3_VertexBufferPtr* value)
{
	m3_VertexBufferID* vertexBufferId = new m3_VertexBufferID();

	m3_VBO::glGenBufferVBO()( 1, &vertexBufferId->vertexId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, vertexBufferId->vertexId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->vertexDataPtr, GL_STREAM_DRAW_ARB );

	m3_VBO::glGenBufferVBO()( 1, &vertexBufferId->textureCoordId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, vertexBufferId->textureCoordId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, value->nVerteces*2*sizeof(float), value->textureCoordPtr, GL_STREAM_DRAW_ARB );

	m3_VBO::glGenBufferVBO()( 1, &vertexBufferId->normalId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, vertexBufferId->normalId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->normalDataPtr, GL_STREAM_DRAW_ARB );

	return vertexBufferId;
}