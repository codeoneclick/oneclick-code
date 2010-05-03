#pragma once
#ifndef _M3_ENTITY_H_
#define _M3_ENTITY_H_

#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "glext.h"
#include "m3_VBO.h"
#include "m3_FileFormat.h"
#include "m3_Core.h"

class m3_Entity
{
	protected :
		m3_VertexBufferPtr* _vertexBufferPtr;
		m3_VertexBufferID*  _vertexBufferId;

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
		Matrix4x4 _mWorldViewProjection;

		Vector3d  *_vCameraEye;
		Vector3d  *_vLightDirection;

		void _EnableShader();
		void _DisableShader();
		void _UpdateShaderParams();
		void _UpdateWorldMatrix();

	public :
		m3_Entity();
		virtual void Load(std::string value) = NULL;
		virtual void Update() = NULL;
		virtual void Render() = NULL;

		Vector3d vPosition;
		Vector3d vRotation;
		Vector3d vScale;

		std::string _shaderStr;
		std::string _textureStr[4];

		float _textureAnimSpeed;
};

#endif