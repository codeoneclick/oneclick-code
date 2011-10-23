#include "Grass.h"

#include "RenderController.h"
#include "Utility.h"

Grass::Grass()
{
	_shaderStr = "grass";
	_textureStr[0] = "Content\\textures\\grass_04.dds";
	_textureStr[1] = "Content\\textures\\grasss.dds";
	_textureStr[2] = "Content\\textures\\grass_03.dds";
}

void Grass::Load(std::string value, LevelIndex _index)
{
	_vertexBufferPtr = new VertexBufferPtr();
	_vertexBufferPtr->nVerteces = Resource::MapContainer()->_grassVB->nVerteces;
	_vertexBufferPtr->vertexDataPtr = Resource::MapContainer()->_grassVB->vertexDataPtr;
	_vertexBufferPtr->vertexBufferId = Resource::MapContainer()->_grassVB->vertexBufferId;

	unsigned int nIndeces = 0;
	for(unsigned i = 0; i < Resource::MapContainer()->grassPositionList.size(); ++i)
	{
		if((Resource::MapContainer()->grassPositionList[i].vPosition.x < (_index.indexY * CHUNK_SIZE + CHUNK_SIZE)) && (Resource::MapContainer()->grassPositionList[i].vPosition .z < (_index.indexX * CHUNK_SIZE + CHUNK_SIZE)))
			if((Resource::MapContainer()->grassPositionList[i].vPosition.x > _index.indexY * CHUNK_SIZE) && (Resource::MapContainer()->grassPositionList[i].vPosition .z > _index.indexX * CHUNK_SIZE))
				nIndeces++;
	}

	_vertexBufferPtr->nIndeces = nIndeces * 12;
	_vertexBufferPtr->indecesPtr = new unsigned int[_vertexBufferPtr->nIndeces];
	unsigned int _vertexBufferIndex = 0;
	unsigned int indexValue = 0;

    for(unsigned i = 0; i < Resource::MapContainer()->grassPositionList.size(); ++i)
	{
		if((Resource::MapContainer()->grassPositionList[i].vPosition.x < (_index.indexY * CHUNK_SIZE + CHUNK_SIZE)) && (Resource::MapContainer()->grassPositionList[i].vPosition .z < (_index.indexX * CHUNK_SIZE + CHUNK_SIZE)))
		if((Resource::MapContainer()->grassPositionList[i].vPosition.x > _index.indexY * CHUNK_SIZE) && (Resource::MapContainer()->grassPositionList[i].vPosition .z > _index.indexX * CHUNK_SIZE))
		{
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue--;
		 _vertexBufferIndex++;

         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;

         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue--;
		 _vertexBufferIndex++;

         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
         _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = indexValue; indexValue++;
		 _vertexBufferIndex++;
		 continue;
		}
		indexValue += 8;
     }

	_vertexBufferPtr->bPosition = true;
	_vertexBufferPtr->bTexCoord = true;
	_vertexBufferPtr->bExtValue = true;

	VB::glCreateVB(1, &_vertexBufferPtr->indexBufferId);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->indexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nIndeces*sizeof(unsigned int), _vertexBufferPtr->indecesPtr, GL_STATIC_DRAW_ARB );

	delete[] _vertexBufferPtr->indecesPtr;
}

void Grass::Update()
{
	_UpdateWorldMatrix();
}

void Grass::Render()
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_UpdateShaderParams();

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, NULL );

	//VB::glBindVB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
	//VB::glBindVB(GL_ARRAY_BUFFER_ARB, NULL);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//VB::glBindDataVB(GL_TEXTURE0);

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
}

void Grass::UpdateData(UpdateDataFlag _flag)
{
	//VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId );	
	//_vertexBufferPtr->vertexDataPtr = (VertexData*)VB::glLockVB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
	//VB::glUnlockVB(GL_ARRAY_BUFFER_ARB);
	//_vertexBufferPtr->vertexDataPtr = NULL;
}