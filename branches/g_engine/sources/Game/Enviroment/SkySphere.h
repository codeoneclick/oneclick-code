#ifndef CSKYSPHERE_H
#define CSKYSPHERE_H

#include "Dummy.h"

namespace Enviroment
{
	class CSkySphere : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
		};

		struct SXVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
			char value[12];
		};

		math::Vector3d m_vSunDir;
		float m_fSunTheta;
		float m_fSunPhi;

		unsigned int m_nSize;
		unsigned int m_nSamples;

		bool m_bSkyBuffer;
		math::Vector3d m_vInvWavelength4;
		LPDIRECT3DTEXTURE9 m_pSkyBuffer, m_pSkyBackBuffer;	
		float m_fScaleOverScaleDepth;
		float m_fScale;
		float m_fRayleighScaleDepth;
		float m_fKr4PI;
		float m_fKm4PI;
		float m_fInnerRadius;
		math::Vector3d m_vHG;
		math::Vector3d m_vEye;
		float m_fKr;
		float m_fKm;
		float m_fKrESun;
		float m_fESun;
		float m_fKmESun;
		float m_fg;
		float m_fg2;
		

		void SetTime(float T);
		void UpdateSkyBuffer();
		float scale(float fCos);
		LPDIRECT3DTEXTURE9 GetRead();
		LPDIRECT3DTEXTURE9 GetWrite();
		math::Vector3d expv( const math::Vector3d &v );

		unsigned int m_Cols;
		unsigned int m_Rows;
		float m_fOuterRadius;

	public :
		CSkySphere();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
	};
};

#endif

