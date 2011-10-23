#include "3DS.h"

using namespace Loader;

C3DS::S3DSFile* C3DS::ReadData(std::string value)
{
	FILE *file = fopen(value.c_str() , "rb");
	unsigned int   filePosition = 0;
	unsigned int   lFilePosition = 0;
	unsigned int   chunkSize;
	unsigned short chunkId;
	unsigned int   length = 0;
	unsigned int   indecesOffset = 0;

	std::vector<C3DS::S3DSReadData*> readData;
	unsigned int nVertecesReaded = 0;
	unsigned int nIndecesReaded  = 0;
	
	filePosition += 2 * fread(&chunkId,2,1,file);
	if(chunkId != 0x4D4D) return NULL; 
	filePosition += 4 * fread(&chunkSize,4,1,file);

	std::string _chunkName;
	std::vector<std::string> _chunkNames;

	char _char = '_';
	while(filePosition < chunkSize && lFilePosition != filePosition)
	{
		lFilePosition = filePosition;
		filePosition += 2 * fread(&chunkId,2,1,file);
		filePosition += 4 * fread(&length,4,1,file);
	
		switch(chunkId)
		{
			case 0x3d3d:break;
		    case 0x4100:break;

			case 0x4000:
				_chunkName = "";
				_char = '_';
				while(_char != '\0' && filePosition - lFilePosition < length)
				{
					filePosition += fread(&_char,1,1,file);
					if(_char != '\0')
						_chunkName += _char;
				}
				_chunkNames.push_back(_chunkName);
			break;

			case 0x4110:
				readData.push_back(new C3DS::S3DSReadData());
				unsigned short nVertecesToRead;
				filePosition += 2 * fread(&nVertecesToRead,2,1,file);
				(*(readData.end() - 1))->vPosition = new math::Vector3d[nVertecesToRead];
				(*(readData.end() - 1))->nVerteces = nVertecesToRead;
				nVertecesReaded += nVertecesToRead;
				for(int i = 0; i < nVertecesToRead; ++i)
					filePosition += 12 * fread(&(*(readData.end() - 1))->vPosition[i],12,1,file);
		    break;

			case 0x4120:
			{
				unsigned short nTriangles;
				filePosition += 2*fread(&nTriangles,2,1,file);
				(*(readData.end() - 1))->indexData = new unsigned int[nTriangles*3];
				(*(readData.end() - 1))->nIndeces = nTriangles*3;
				unsigned int index = 0;
				for(int i = 0; i < nTriangles; ++i)
				{
					unsigned short indexValue = 0;
					filePosition += 2 * fread(&indexValue,2,1,file);
					(*(readData.end() - 1))->indexData[index] = indexValue + indecesOffset;
					index++;
					filePosition+=2*fread(&indexValue,2,1,file);
					(*(readData.end() - 1))->indexData[index] = indexValue + indecesOffset;
					index++;
					filePosition+=2*fread(&indexValue,2,1,file);
					(*(readData.end() - 1))->indexData[index] = indexValue + indecesOffset;
					index++;
					filePosition+=2*fread(&indexValue,2,1,file);
				}
				indecesOffset  += (*(readData.end() - 1))->nVerteces;
				nIndecesReaded += nTriangles*3;
			}
		    break;

			case 0x4140:
				unsigned short nTexCoord;
			    filePosition += 2 * fread(&nTexCoord,2,1,file);
				(*(readData.end() - 1))->vTexCoord = new math::Vector2d[nTexCoord];
				for(int i = 0; i < nTexCoord; ++i)
				{
					filePosition += 4*fread(&(*(readData.end() - 1))->vTexCoord[i],8,1,file);
				}
		    break;

			default:
				filePosition += length - 6;
				fseek(file,length - 6,SEEK_CUR);
			break;
		}
	}
	fclose(file);

	S3DSFile *_data = new S3DSFile();
	_data->nVerteces = nVertecesReaded;
	_data->nIndeces = nIndecesReaded;
	_data->vertexData = new C3DS::S3DSVertex[nVertecesReaded];
	_data->indexData = new unsigned int[nIndecesReaded];
	_data->nChunks = readData.size();

	
	std::vector<C3DS::S3DSReadData*>::iterator dataIterator = readData.begin();
	unsigned int chunkIndex = 0;
	unsigned int index_01 = 0;
	unsigned int index_02 = 0;
	while(dataIterator != readData.end())
	{
		for(unsigned int i = 0; i < (*dataIterator)->nVerteces; ++i)
		{
			_data->vertexData[index_01].vPosition = (*dataIterator)->vPosition[i];
			_data->vertexData[index_01].vTexCoord = (*dataIterator)->vTexCoord[i];
			index_01++;
		}
		_data->chunks[_chunkNames[chunkIndex]] = new C3DS::S3DSChunk();
		_data->chunks[_chunkNames[chunkIndex]]->nIndeces  = (*dataIterator)->nIndeces;
		_data->chunks[_chunkNames[chunkIndex]]->indexData = new unsigned int[(*dataIterator)->nIndeces];

		for(unsigned int i = 0; i < (*dataIterator)->nIndeces; ++i)
		{
			_data->indexData[index_02] = (*dataIterator)->indexData[i];
			_data->chunks[_chunkNames[chunkIndex]]->indexData[i] = (*dataIterator)->indexData[i];
			index_02++;
		}

		delete[] (*dataIterator)->vPosition;
		delete[] (*dataIterator)->vTexCoord;
		delete[] (*dataIterator)->indexData;
		delete (*dataIterator);
		dataIterator++;
		chunkIndex++;
	}
	readData.clear();
	return _data;
}

void C3DS::Commit(S3DSFile *in_value, Core::CMesh *out_value)
{
	out_value->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	S3DSVertex *v_data = (S3DSVertex*)out_value->m_VertexBuffer->Load(in_value->nVerteces,sizeof(S3DSVertex),0);
	memcpy(v_data,in_value->vertexData,sizeof(S3DSVertex) * in_value->nVerteces);

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[5];
	
	declaration.m_Elements[0].m_index = 0;
	declaration.m_Elements[0].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_offset = 0 * sizeof(float);

	declaration.m_Elements[1].m_index = 0;
	declaration.m_Elements[1].m_size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_offset = 3 * sizeof(float);

	declaration.m_Elements[2].m_index = 0;
	declaration.m_Elements[2].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[2].m_type = Core::IVertexBuffer::ELEMENT_NORMAL;
	declaration.m_Elements[2].m_offset = 5 * sizeof(float);

	declaration.m_Elements[3].m_index = 1;
	declaration.m_Elements[3].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[3].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[3].m_offset = 8 * sizeof(float);

	declaration.m_Elements[4].m_index = 2;
	declaration.m_Elements[4].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[4].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[4].m_offset = 11 * sizeof(float);

	declaration.m_ElementCount = 5;

	out_value->m_VertexBuffer->SetDeclaration(declaration);

	out_value->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	unsigned int *ib_ref = out_value->m_IndexBuffer->Load(in_value->nIndeces);
	memcpy(ib_ref,in_value->indexData,sizeof(unsigned int) * in_value->nIndeces);

	Math::Util::SVertexTBN * dataTBN = Math::Util::CalculateTBN(v_data,ib_ref,out_value->m_VertexBuffer->GetVertexCount(),out_value->m_IndexBuffer->GetIndexCount(),sizeof(S3DSVertex));
	for(int i = 0; i < out_value->m_VertexBuffer->GetVertexCount(); ++i)
	{
		v_data[i].vNormal = dataTBN[i].vNormal;
		v_data[i].vNormal.normalize();
		v_data[i].vTangent = dataTBN[i].vTangent;
		v_data[i].vTangent.normalize();
		v_data[i].vBinormal = dataTBN[i].vBinormal;
		v_data[i].vBinormal.normalize();
	}
	delete[] dataTBN;

	out_value->m_VertexBuffer->CommitToVRAM(0);
	out_value->m_IndexBuffer->CommitToVRAM();

	delete[] in_value->vertexData;
	delete[] in_value->indexData;
}