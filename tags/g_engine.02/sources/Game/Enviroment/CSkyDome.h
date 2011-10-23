#ifndef CSKYSPHERE_H
#define CSKYSPHERE_H

#include "Dummy.h"
#include "../../Core/CLight.h"

namespace Enviroment
{
	class CSkyDome : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d<float> m_vTexCoord;
		};

		CLight* m_LightRef;

		unsigned int m_nSize;
		unsigned int m_nSamples;

		math::Vector3d m_vInvWavelength4;
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
		

		void RefreshAtmosphericTexture();
		float scale(float fCos);
		math::Vector3d expv( const math::Vector3d &v );

		unsigned int m_Cols;
		unsigned int m_Rows;
		float m_fOuterRadius;

	public :
		CSkyDome();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
		inline float GetSkyHeight() { return m_fInnerRadius; };
	};
};

#endif

