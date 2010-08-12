#ifndef _SHADER_H_
#define _SHADER_H_
#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "Matrix4x4.h"
#include "Vector3d.h"
#include <string>

class CShader
{
	public :
	struct CGShader
	{
		CGcontext   context;
		CGprofile   vertexProfile;
		CGprofile   pixelProfile;
		CGprogram   vertexProgram;
		CGprogram   pixelProgram;
	};

	struct CGShaderParams
	{
		CGparameter texture[8];
		CGparameter mWorldViewProjection;
		CGparameter mWorld;
		CGparameter vCameraPosition;
		CGparameter vLightDirection;
		CGparameter fClipHeigth;
		CGparameter bClipInc;
		CGparameter fTimer;
	};

	protected :
		CGShader *_cgShader;
		CGShaderParams _cgShaderParams;
	public :
		CShader();
		~CShader();
		void Create(std::string name);
		void Enable();
		void Disable();
		void Update();

		void SetWVPMatrix(math::matrix::Matrix4x4 &matrix);
		void SetWMatrix(math::matrix::Matrix4x4 &matrix);
		void SetTexture(unsigned int index, unsigned int addr_ptr);
		void SetCamera(math::vector::Vector3d &position);
		void SetLight(math::vector::Vector3d &direction);
		void SetClip(float incValue, float clipValue);
		void UpdateTimer();
};

#endif
