#ifndef _DUMMY_H_
#define _DUMMY_H_

#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "glext.h"
#include "VB.h"
#include "StructDef.h"
#include "Core.h"
#include "Math.h"

enum UpdateDataFlag { UPDATE_REFRESH = 0, UPDATE_RECREATE };

struct LevelIndex
{
	unsigned int indexX;
	unsigned int indexY;
};

class Dummy
{
	protected :

		VertexBufferPtr*  _vertexBufferPtr;
		VertexBufferPtr*  _vertexBufferPtr2;

		VertexBufferPtr*  _vertexBufferLODHighPtr;
		VertexBufferPtr*  _vertexBufferLODMiddlePtr;
		VertexBufferPtr*  _vertexBufferLODLowPtr;

		m3_CgShader       *_cgShader;
	    m3_CgShaderBasicParams _cgShaderParams;

		Matrix4x4 _mTranslation;
		Matrix4x4 _mRotationX;
		Matrix4x4 _mRotationY;
		Matrix4x4 _mRotationZ;
		Matrix4x4 _mRotation;
		Matrix4x4 _mScale;
		Matrix4x4 _mWorld;

		Matrix4x4 *_mView;
		Matrix4x4 *_mProjection;

		Matrix4x4 _mWorldView;
		Matrix4x4 _mWorldViewInverse;
		Matrix4x4 _mWorldViewProjection;

		Vector3d  *_vCameraEye;
		Vector3d  *_vLightDirection;

		void _UpdateShaderParams();
		void _UpdateWorldMatrix();
		//void _UpdateVB(VertexBufferPtr*  _vertexBufferPtr);

	public :
		Dummy();
		virtual void Load(std::string value) = NULL;
		virtual void Update() = NULL;
		virtual void Render() = NULL;

		Vector3d vPosition;
		Vector3d vRotation;
		Vector3d vScale;

		std::string _shaderStr;
		std::string _textureStr[8];

		void EnableShader(std::string vs_name, std::string ps_name);
		void DisableShader();

		void EnableVB();
		void DisableVB();

		void EnableIB();
		void DisableIB();
};

#endif