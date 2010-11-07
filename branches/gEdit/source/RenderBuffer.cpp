#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{
	VB_VRAM_addr_ptr = 0;
	IB_VRAM_addr_ptr = 0;

	VB_DRAM_addr_ptr = NULL;
	IB_DRAM_addr_ptr = NULL;
		
	VB_declaration = 0;

	nVerteces = 0;
	nIndeces = 0;
}

RenderBuffer::~RenderBuffer()
{
	if(IB_DRAM_addr_ptr != NULL)
	{
		delete[] IB_DRAM_addr_ptr;
		IB_DRAM_addr_ptr = NULL;
	}

	if(VB_DRAM_addr_ptr != NULL)
	{
		delete[] VB_DRAM_addr_ptr;
		VB_DRAM_addr_ptr = NULL;
	}

	if(VB_VRAM_addr_ptr != 0)
	{	
		extension::VBExtension::glDeleteBuffersARB(1, &VB_VRAM_addr_ptr);
		VB_VRAM_addr_ptr = 0;
	}

	if(IB_VRAM_addr_ptr != 0)
	{
		extension::VBExtension::glDeleteBuffersARB(1, &IB_VRAM_addr_ptr);
		IB_VRAM_addr_ptr = 0;
	}
}

void* RenderBuffer::CreateVB(unsigned int nVerteces, unsigned char VB_declaration)
{
	if(VB_DRAM_addr_ptr != NULL)
	{
		delete[] VB_DRAM_addr_ptr;
		VB_DRAM_addr_ptr = NULL;
	}
	this->nVerteces = nVerteces;
	VB_DRAM_addr_ptr = new unsigned char[nVerteces * VB_declaration];
	memset(VB_DRAM_addr_ptr,0x0,nVerteces * VB_declaration);
	return VB_DRAM_addr_ptr;
}

unsigned int *RenderBuffer::CreateIB(unsigned int nIndeces)
{
	if(IB_DRAM_addr_ptr != NULL)
	{
		delete[] IB_DRAM_addr_ptr;
		IB_DRAM_addr_ptr = NULL;
	}
	this->nIndeces = nIndeces;
	IB_DRAM_addr_ptr = new unsigned int[nIndeces];
	memset(IB_DRAM_addr_ptr,0x0,nIndeces);
	return IB_DRAM_addr_ptr;
}

void RenderBuffer::DeleteVB_DRAM()
{
	if(VB_DRAM_addr_ptr != NULL)
	{
		delete[] VB_DRAM_addr_ptr;
		VB_DRAM_addr_ptr = NULL;
	}
}

void RenderBuffer::DeleteIB_DRAM()
{
	if(IB_DRAM_addr_ptr != NULL)
	{
		delete[] IB_DRAM_addr_ptr;
		IB_DRAM_addr_ptr = NULL;
	}
}

void RenderBuffer::DeleteVB_VRAM()
{
	if(VB_VRAM_addr_ptr != 0)
	{	
		extension::VBExtension::glDeleteBuffersARB(1, &VB_VRAM_addr_ptr);
		VB_VRAM_addr_ptr = 0;
	}
}

void RenderBuffer::DeleteIB_VRAM()
{
	if(IB_VRAM_addr_ptr != 0)
	{
		extension::VBExtension::glDeleteBuffersARB(1, &IB_VRAM_addr_ptr);
		IB_VRAM_addr_ptr = 0;
	}
}

void RenderBuffer::CommitVB_VRAM(bool DRAM_CLEAR)
{
	//extension::VBExtension::glGenBuffersARB( 1, &VB_VRAM_addr_ptr );							
	//extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, VB_VRAM_addr_ptr );		
	//extension::VBExtension::glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*sizeof(type::VertexData), value->vertexDataPtr, GL_STATIC_DRAW_ARB );
	//delete[] value->vertexDataPtr;
}