#include "CM2.h"
#include <fstream>

using namespace Loader;

CM2::SMeshBuffer* CM2::ReadData(std::string value)
{
	std::ifstream inStream;
	inStream.open(value.c_str(),std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();

	SHeader *header = (SHeader*)fileData;
	STag *tags =(STag*)(fileData + header->offset);

	EM3VERSION version = M3_UNKNOWN;
	SVertexBlock_01 *vertexBlock_v01;
	SVertexBlock_02 *vertexBlock_v02;
	SVertexBlock_03 *vertexBlock_v03;

	SMeshBuffer *meshBuffer = new SMeshBuffer();
	SIndexBlock *indexBlockRef;
	unsigned short *indexBlock;
	SRegion *regionBlock;

	bool firstIndexBlockFlag = false;
	unsigned int blockSize = 0;
	std::string tagName = "none";

	for(unsigned int i = 0; i < header->tagsCount; ++i)
	{
		tagName = tags[i].name;
		tagName.resize(4);

		if( tagName == "_VID" )
		{
			indexBlockRef = (SIndexBlock*)(fileData + tags[i].offset);
			meshBuffer->nIndeces = indexBlockRef->faces.entries;
			indexBlock = (unsigned short*)(fileData + tags[indexBlockRef->faces.ref].offset);
			regionBlock = (SRegion*)(fileData + tags[indexBlockRef->regions.ref].offset);
		}

		if( tagName == "__8U" )
		{
			blockSize = tags[i].size % sizeof(SVertexBlock_01);
			vertexBlock_v01 = (SVertexBlock_01*)(fileData + tags[i].offset);
			if((blockSize == 0) && (vertexBlock_v01[0].tangent[3] == 255))
			{
				meshBuffer->nVerteces = (tags[i].size) / sizeof(SVertexBlock_01);
				vertexBlock_v01 = (SVertexBlock_01*)(fileData + tags[i].offset);
				version = M3_01;
			}

			blockSize = tags[i].size % sizeof(SVertexBlock_02);
			vertexBlock_v02 = (SVertexBlock_02*)(fileData + tags[i].offset);
			if((blockSize == 0) && (vertexBlock_v02[0].tangent[3] == 255))
			{
				meshBuffer->nVerteces = (tags[i].size) / sizeof(SVertexBlock_02);
				vertexBlock_v02 = (SVertexBlock_02*)(fileData + tags[i].offset);
				version = M3_02;
			}

			blockSize = tags[i].size % sizeof(SVertexBlock_03);
			if(blockSize == 0 && version != M3_02)
			{
				meshBuffer->nVerteces = (tags[i].size)/sizeof(SVertexBlock_03);
				vertexBlock_v03 = (SVertexBlock_03*)(fileData + tags[i].offset);
				version = M3_03;
			}
		}
	}

	meshBuffer->indeces = new unsigned int[meshBuffer->nIndeces];
	meshBuffer->position = new math::Vector3d[meshBuffer->nVerteces];
	meshBuffer->normal = new math::Vector3d[meshBuffer->nVerteces];
	meshBuffer->tangent = new math::Vector3d[meshBuffer->nVerteces];
	meshBuffer->texcoord = new math::Vector2d[meshBuffer->nVerteces];

	float wNormal = 0.0f; 

	for(unsigned int i = 0; i < meshBuffer->nVerteces; ++i)
	{
		switch(version)
		{
			case M3_01:
				
				meshBuffer->position[i] = vertexBlock_v01[i].position;
				meshBuffer->normal[i] = math::Vector3d( 2.0f * (float)vertexBlock_v01[i].normal[0] / 255.0f - 1.0f, 
														2.0f * (float)vertexBlock_v01[i].normal[1] / 255.0f - 1.0f,
														2.0f * (float)vertexBlock_v01[i].normal[2] / 255.0f - 1.0f );
				wNormal = (float) vertexBlock_v01[i].normal[3] / 255.0f;
				if(wNormal)
				{
					meshBuffer->normal[i].x /= wNormal;
					meshBuffer->normal[i].y /= wNormal; 
					meshBuffer->normal[i].z /= wNormal;
				}
				
				meshBuffer->texcoord[i] = math::Vector2d( (float) vertexBlock_v01[i].uv[0] / 2048.0f, 
														  (float) vertexBlock_v01[i].uv[1] / 2048.0f );
			break;

			case M3_02:
				meshBuffer->position[i] = vertexBlock_v02[i].position;
				meshBuffer->normal[i] = math::Vector3d( 2.0f * (float)vertexBlock_v02[i].normal[0] / 255.0f - 1.0f, 
														2.0f * (float)vertexBlock_v02[i].normal[1] / 255.0f - 1.0f,
														2.0f * (float)vertexBlock_v02[i].normal[2] / 255.0f - 1.0f );
				wNormal = (float) vertexBlock_v02[i].normal[3] / 255.0f;
				if(wNormal)
				{
					meshBuffer->normal[i].x /= wNormal;
					meshBuffer->normal[i].y /= wNormal; 
					meshBuffer->normal[i].z /= wNormal;
				}
				
				meshBuffer->texcoord[i] = math::Vector2d( (float) vertexBlock_v02[i].uv[0] / 2048.0f, 
														  (float) vertexBlock_v02[i].uv[1] / 2048.0f );

			break;

			case M3_03:
				meshBuffer->position[i] = vertexBlock_v03[i].position;
				meshBuffer->normal[i] = math::Vector3d( 2.0f * (float)vertexBlock_v03[i].normal[0] / 255.0f - 1.0f, 
														2.0f * (float)vertexBlock_v03[i].normal[1] / 255.0f - 1.0f,
														2.0f * (float)vertexBlock_v03[i].normal[2] / 255.0f - 1.0f );
				wNormal = (float) vertexBlock_v03[i].normal[3] / 255.0f;
				if(wNormal)
				{
					meshBuffer->normal[i].x /= wNormal;
					meshBuffer->normal[i].y /= wNormal; 
					meshBuffer->normal[i].z /= wNormal;
				}
				
				meshBuffer->texcoord[i] = math::Vector2d( (float) vertexBlock_v03[i].uv[0] / 2048.0f, 
														  (float) vertexBlock_v03[i].uv[1] / 2048.0f );
			break;
		}
	}

	for(unsigned int i = 0; i < meshBuffer->nIndeces; ++i)
		meshBuffer->indeces[i] = indexBlock[i];

	return meshBuffer;
}

void CM2::Commit(SMeshBuffer* in_value, Core::CMesh *out_value)
{
	out_value->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	SM3Vertex *v_data = (SM3Vertex*)out_value->m_VertexBuffer->Load(in_value->nVerteces,sizeof(SM3Vertex),0);
	
	for(int i = 0; i < in_value->nVerteces; i++)
	{
		v_data[i].vPosition = in_value->position[i];
		v_data[i].vNormal = in_value->normal[i];
		v_data[i].vTexCoord = in_value->texcoord[i];
	}

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
	memcpy(ib_ref,in_value->indeces, sizeof(unsigned int) * in_value->nIndeces);

	out_value->m_VertexBuffer->CommitToVRAM(0);
	out_value->m_IndexBuffer->CommitToVRAM();
}