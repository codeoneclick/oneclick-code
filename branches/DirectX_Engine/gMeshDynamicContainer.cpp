#include "gMeshDynamicContainer.h"

gMeshDynamicContainer::gMeshDynamicContainer()
{
}
void gMeshDynamicContainer::Load(const gResourceData *resource)
{
	this->LoadFromFile(resource->vertexFileName);
	FILE *file = fopen(resource->vertexFileName, "rb");
	SMD2Header	fileHeader;
	fread(&fileHeader, 1, sizeof(SMD2Header),file);

	char g_skins[MAX_MD2SKINS][64];
	unsigned char buffer[MAX_VERTS*4+128];
	gMd2TextureCoordData base_st[MAX_VERTS];
	
	gMd2TriangleData  triangleData;
	gMd2TriangleFrameData *triangleFrameData;

	this->nFrames     = fileHeader.num_frames;
	this->nVerteces   = fileHeader.num_xyz;
	this->nTriangles  = fileHeader.num_tris;
	
	this->_indexData = new gMd2IndexList[fileHeader.num_tris];
	this->_frameVertexList = new gMd2FrameVertexList[fileHeader.num_frames];
	
	for( int i = 0; i < fileHeader.num_frames; i++)
		this->_frameVertexList[i].vertex = new D3DXVECTOR3[fileHeader.num_xyz];
	
	fread( g_skins, 1, fileHeader.num_skins * MAX_SKINNAME, file );
	
	fread( base_st, 1, fileHeader.num_st * sizeof(base_st[0]), file );
	
	int	max_tex_u = 0, max_tex_v = 0;

	for(int i = 0; i < fileHeader.num_tris; i++ ) 
	{
		fread(&triangleData, 1, sizeof(gMd2TriangleData), file);
		
		this->_indexData[i].index.x = triangleData.index_xyz[2];
		this->_indexData[i].index.y = triangleData.index_xyz[1];
		this->_indexData[i].index.z = triangleData.index_xyz[0];
	
		this->_indexData[i].textureCoord[0].x = base_st[triangleData.index_st[2]].s;
		this->_indexData[i].textureCoord[0].y = base_st[triangleData.index_st[2]].t;
		this->_indexData[i].textureCoord[1].x = base_st[triangleData.index_st[1]].s;
		this->_indexData[i].textureCoord[1].y = base_st[triangleData.index_st[1]].t;
		this->_indexData[i].textureCoord[2].x = base_st[triangleData.index_st[0]].s;
		this->_indexData[i].textureCoord[2].y = base_st[triangleData.index_st[0]].t;
		max_tex_u = max( max_tex_u, base_st[triangleData.index_st[0]].s );
		max_tex_u = max( max_tex_u, base_st[triangleData.index_st[1]].s );
		max_tex_u = max( max_tex_u, base_st[triangleData.index_st[2]].s );
		max_tex_v = max( max_tex_v, base_st[triangleData.index_st[0]].t );
		max_tex_v = max( max_tex_v, base_st[triangleData.index_st[1]].t );
		max_tex_v = max( max_tex_v, base_st[triangleData.index_st[2]].t );
	}

	for (int i = 0; i < fileHeader.num_tris; i++ ) 
	{
		this->_indexData[i].textureCoord[0].x /= max_tex_u;
		this->_indexData[i].textureCoord[1].x /= max_tex_u;
		this->_indexData[i].textureCoord[2].x /= max_tex_u;
		this->_indexData[i].textureCoord[0].y /= max_tex_v;
		this->_indexData[i].textureCoord[1].y /= max_tex_v;
		this->_indexData[i].textureCoord[2].y /= max_tex_v;
	}

	for(int i = 0; i < fileHeader.num_frames; i++ ) 
	{
		triangleFrameData = (gMd2TriangleFrameData*)buffer;
		fread(triangleFrameData, 1, fileHeader.framesize, file);
		
		for( int j = 0; j < fileHeader.num_xyz; j++ ) 
		{
			 this->_frameVertexList[i].vertex[j].x = triangleFrameData->verts[j].v[0] * triangleFrameData->scale[0] + triangleFrameData->translate[0];
			 this->_frameVertexList[i].vertex[j].y = triangleFrameData->verts[j].v[1] * triangleFrameData->scale[1] + triangleFrameData->translate[1];
			 this->_frameVertexList[i].vertex[j].z = triangleFrameData->verts[j].v[2] * triangleFrameData->scale[2] + triangleFrameData->translate[2];
		}
	}
	
	fclose(file);

	this->_framesVertexData = new gMd2FrameVertexData[this->nFrames];
	for( int i = 0; i < this->nFrames; ++i)
		this->_framesVertexData[i].verteces = new gMd2Vertex[this->nTriangles*3];

	for ( int i = 0; i < this->nFrames; i++ )
	{
		int vertexIndex = 0;
		for( int j = 0; j < this->nTriangles; j++) 
		{
			this->_framesVertexData[i].verteces[vertexIndex].position = D3DXVECTOR3( this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.x].x, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.x].y, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.x].z);
			this->_framesVertexData[i].verteces[vertexIndex].textureCoordinates = D3DXVECTOR2(this->_indexData[j].textureCoord[0].x,this->_indexData[j].textureCoord[0].y);
			vertexIndex++;

			this->_framesVertexData[i].verteces[vertexIndex].position = D3DXVECTOR3( this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.y].x, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.y].y, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.y].z);
			this->_framesVertexData[i].verteces[vertexIndex].textureCoordinates = D3DXVECTOR2(this->_indexData[j].textureCoord[1].x,this->_indexData[j].textureCoord[1].y);
			vertexIndex++;

			this->_framesVertexData[i].verteces[vertexIndex].position = D3DXVECTOR3( this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.z].x, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.z].y, this->_frameVertexList[i].vertex[(int)this->_indexData[j].index.z].z);
			this->_framesVertexData[i].verteces[vertexIndex].textureCoordinates = D3DXVECTOR2(this->_indexData[j].textureCoord[2].x,this->_indexData[j].textureCoord[2].y);
			vertexIndex++;
		}
	}

	IDirect3DTexture9* _texture;
	D3DXCreateTextureFromFile(gDevice::device, resource->texturesListFileName, &_texture);
	this->_texturesColorList.push_back(_texture);
	this->_effectsList["mesh_effect"] =  gCore::ShadersService()->Find("dynamic_mesh_effect");
	this->_effectsList["shadow_effect"] =  gCore::ShadersService()->Find("shadow_effect");
}

gMeshDynamicData gMeshDynamicContainer::GetMeshData()
{
	gMeshDynamicData _meshData;
	_meshData.nTriangles = this->nTriangles;
	_meshData.nVerteces = this->nVerteces;
	_meshData.ptrFrameVertexData = this->_framesVertexData;
	_meshData.effectsList = this->_effectsList;
	_meshData.texturesColorList = this->_texturesColorList;
	_meshData.ib = this->GetModelIB();
	_meshData.vb = this->GetModelVB(0);
	_meshData.tvb = this->GetTextureVB();
	return _meshData;
}


/////////////////////////////////////////////////////////////////////////////////////////////////


// CMD2Model
void gMeshDynamicContainer::LoadFromFile(char* file_name)
{
	// Open the file
	std::ifstream md2_file;
	md2_file.open(file_name, std::ios::in | std::ios::binary);
	Load(md2_file);
}

void gMeshDynamicContainer::Load(std::istream& md2_stream)
{
	GetHeader(md2_stream);

	GetFrameData(md2_stream);
	GetIndexData(md2_stream);
	GetTextureData(md2_stream);
}

void gMeshDynamicContainer::GetHeader(std::istream& md2_stream)
{
	md2_stream.seekg(0, std::ios::beg);
	md2_stream.read((char*)&header, sizeof(md2::header));
}


void gMeshDynamicContainer::GetFrameData(std::istream& md2_stream)
{
	int frame_data_size = (header.framesize * header.num_frames);
	char* buffer = new char[frame_data_size];
	md2_stream.seekg(header.ofs_frames, std::ios::beg);
	md2_stream.read((char*)buffer, frame_data_size);

	MD2_POSITION_VERTEX* vertices = new MD2_POSITION_VERTEX[header.num_xyz];

	md2::frame* cur_frame = (md2::frame*)buffer;
	for (int f = 0; f < header.num_frames; f++)
	{
		cur_frame = (md2::frame*) &buffer[header.framesize * f];
		for (int v = 0; v < header.num_xyz; v++)
		{
			for (int i = 0; i < 3; i++)
				vertices[v].a[i] = (cur_frame->verticies[v].vertex[i] * cur_frame->scale[i])
										+cur_frame->translate[i];
		}
		bool is_created = D3D_OK == gDevice::device->CreateVertexBuffer(sizeof(MD2_POSITION_VERTEX)*header.num_xyz,0,0,D3DPOOL_MANAGED,&model_VB[f],0);
		if (is_created == 0)
		{
			MessageBox(0,"Could not create vertex buffers", "Fatal Error", 0);
			PostQuitMessage(0);
			return;
		}
		void* data_ptr = 0;
		bool is_locked = D3D_OK == model_VB[f]->Lock(0, 0, &data_ptr, 0);//D3DLOCK_DISCARD
		memcpy(data_ptr, vertices, sizeof(MD2_POSITION_VERTEX)*header.num_xyz);
		model_VB[f]->Unlock();

		used_VBs++;
	}

	delete[] vertices;
	delete[] buffer;
}

void gMeshDynamicContainer::GetIndexData(std::istream& md2_stream)
{	
	md2::triangle* tri_buffer = new md2::triangle[header.num_tris];
	md2::index_buffer* index_buffer = new md2::index_buffer[header.num_tris];

	md2_stream.seekg(header.ofs_tris, std::ios::beg);
	md2_stream.read((char*)tri_buffer, sizeof(md2::triangle)*header.num_tris);

	for (int i = 0; i < header.num_tris; i++)
	{
		index_buffer[i][0] = tri_buffer[i].vertex_indicies[0];
		index_buffer[i][1] = tri_buffer[i].vertex_indicies[1];
		index_buffer[i][2] = tri_buffer[i].vertex_indicies[2];
	}

	gDevice::device->CreateIndexBuffer(sizeof(md2::index_buffer)*header.num_tris,0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&model_IB,0);

	void* data_ptr;
	model_IB->Lock(0, 0, &data_ptr, 0);
	memcpy(data_ptr, index_buffer, sizeof(md2::index_buffer)*header.num_tris);
	model_IB->Unlock();

	delete[] index_buffer;
	delete[] tri_buffer;
}

void gMeshDynamicContainer::GetTextureData(std::istream& md2_stream)
{
	md2::tex_coord* c_buffer = new md2::tex_coord[header.num_st];
	MD2_TEXTURE_VERTEX* tex_buffer = new MD2_TEXTURE_VERTEX[header.num_st];

	md2_stream.seekg(header.ofs_st, std::ios::beg);
	md2_stream.read((char*)c_buffer, sizeof(md2::tex_coord)*header.num_st);

	for (int i = 0; i < header.num_st; i++)
	{
		tex_buffer[i].s = ((float)c_buffer[i].s / (float)(header.skinwidth));
		tex_buffer[i].t = ((float)c_buffer[i].t / (float)(header.skinheight));
	}

	// get the tex coord ref'd in the indices, then move it into vert_tex_buffer
	MD2_TEXTURE_VERTEX* vert_tex_buffer = new MD2_TEXTURE_VERTEX[header.num_xyz];
	md2::triangle* tri_buffer = new md2::triangle[header.num_tris];

	md2_stream.seekg(header.ofs_tris, std::ios::beg);
	md2_stream.read((char*)tri_buffer, sizeof(md2::triangle)*header.num_tris);

	for (int t = 0; t < header.num_tris; t++)
	{
		for (int i = 0; i < 3; i++)
		{
			int vertex_i = tri_buffer[t].vertex_indicies[i];
			vert_tex_buffer[vertex_i].s = tex_buffer[tri_buffer[t].texture_indicies[i]].s;
			vert_tex_buffer[vertex_i].t = tex_buffer[tri_buffer[t].texture_indicies[i]].t;
		}
	}

	gDevice::device->CreateVertexBuffer(sizeof(MD2_TEXTURE_VERTEX)*header.num_xyz,0,0,D3DPOOL_MANAGED,&texture_VB,0);
		
	void* data_ptr;
	texture_VB->Lock(0, 0, &data_ptr, 0);
	memcpy(data_ptr, vert_tex_buffer, sizeof(MD2_TEXTURE_VERTEX)*header.num_xyz);
	texture_VB->Unlock();

	delete[] tri_buffer;
	delete[] vert_tex_buffer;
	delete[] tex_buffer;
	delete[] c_buffer;
}


IDirect3DVertexBuffer9** gMeshDynamicContainer::GetModelVB(int frame)
{
	return model_VB;
}

IDirect3DVertexBuffer9* gMeshDynamicContainer::GetTextureVB(void)
{
	return texture_VB;
}

IDirect3DIndexBuffer9* gMeshDynamicContainer::GetModelIB(void)
{
	return model_IB;
}

int gMeshDynamicContainer::GetVertCount(void)
{
	return header.num_xyz;
}

int gMeshDynamicContainer::GetTriangleCount(void)
{
	return header.num_tris;
}

int gMeshDynamicContainer::GetFrameCount(void)
{
	return header.num_frames;
}
