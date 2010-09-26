#ifndef _RENDERBUFFER_H_
#define _RENDERBUFFER_H_
#include "VBExtension.h"
#include "Vector3d.h"

#define VB_V3_T2              20
#define VB_V3_T2_N3_B3_T3     56
#define VB_V3_T2_N3_B3_T3_W4  68


class RenderBuffer : public extension::VBExtension
{
	protected :
		unsigned int VB_VRAM_addr_ptr;
		unsigned int IB_VRAM_addr_ptr;

		unsigned char *VB_DRAM_addr_ptr;
		unsigned int  *IB_DRAM_addr_ptr;
		
		unsigned char VB_declaration;

		unsigned int nVerteces;
		unsigned int nIndeces;

	public :
		RenderBuffer();
		~RenderBuffer();

		void*          CreateVB(unsigned int nVerteces, unsigned char VB_declaration);
		unsigned int*  CreateIB(unsigned int nIndeces);

		void DeleteVB_VRAM();
		void DeleteIB_VRAM();

		void DeleteVB_DRAM();
		void DeleteIB_DRAM();

		void CommitVB_VRAM(bool DRAM_CLEAR);
		void ComminIB_VRAM(bool DRAM_CLEAR);

		void*         LockVB();
		unsigned int* LockIB();

		void UnlockVB();
		void UnlockIB();

		void EnableVB();
		void EnableIB();

		void DisableVB();
		void DisableIB();

		void CalculateTBN();
};

#endif