#include "SkySphere.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../../Core/CGlobal.h"
#include "../../Math/Util.h"

using namespace Enviroment;

CSkySphere::CSkySphere()
{
	m_Cols = 32;
	m_Rows = 32;
	m_fInnerRadius = 20.0f;
	//m_fOuterRadius = 20.0f;


		m_nSize = 8; //Higher, Better, More CPU/GPU
		m_nSamples = 2;//Higher, Better, More CPU/GPU
		m_fKr = 0.0025f;
		m_fKr4PI = m_fKr * 4.0f * D3DX_PI;
		m_fKm = 0.0010f;
		m_fKm4PI = m_fKm * 4.0f * D3DX_PI;
		m_fESun = 20.0f;
		m_fKrESun = m_fESun * m_fKr;
		m_fKmESun = m_fESun * m_fKm;
		m_fg = -0.990f;
		m_fg2 = m_fg * m_fg;
		m_fOuterRadius = m_fInnerRadius * 1.025f;
		m_fScale = 1.0f / (m_fOuterRadius - m_fInnerRadius);

		m_fRayleighScaleDepth = 0.25f;
		m_fScaleOverScaleDepth = m_fScale / m_fRayleighScaleDepth;
		m_vInvWavelength4.x = 1.0f / powf(0.650f, 4.0f);
		m_vInvWavelength4.y = 1.0f / powf(0.570f, 4.0f);
		m_vInvWavelength4.z = 1.0f / powf(0.475f, 4.0f);
		m_vHG.x = 1.5f * ( (1.0f - m_fg2) / (2.0f + m_fg2) );
		m_vHG.y = 1.0f + m_fg2;
		m_vHG.z = 2.0f * m_fg;
		m_vEye.x = 0.0f;
		m_vEye.y = m_fInnerRadius + 1.0e-6f;
		m_vEye.z = 0.0f;

		m_bSkyBuffer = false;
		
		D3DXCreateTexture( Core::CGlobal::GetDevice()->Ref(), m_nSize, m_nSize, 1, 0,	D3DFMT_A16B16G16R16F, D3DPOOL_MANAGED, &m_pSkyBuffer);
		D3DXCreateTexture( Core::CGlobal::GetDevice()->Ref(), m_nSize, m_nSize, 1, 0,	D3DFMT_A16B16G16R16F, D3DPOOL_MANAGED, &m_pSkyBackBuffer);
}


void CSkySphere::Load(std::vector<SResource> _resource)
{
	m_MeshList["sky"] = new Core::CMesh();
	m_MeshList["sky"]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList["sky"]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();

	SResource skyResource = *_resource.begin();
	for(unsigned int index = 0; index < K_MAX_TEXTURES_PER_MESH; ++index)
	{
		if(skyResource.m_TextureFileList[index].length())
			m_MeshList["sky"]->m_TextureArray[index] = CResource::GetTextureControllerInstance()->Load(skyResource.m_TextureFileList[index],Core::ITexture::DDS_EXT);
	}
	m_MeshList["sky"]->m_Shader = CResource::GetShaderControllerInstance()->Load(skyResource.m_ShaderFile);	

	unsigned int numVertex = m_Cols * m_Rows;
	unsigned int numIndex = ( m_Cols - 1 ) * (m_Rows - 1) * 6;

	SVertex* vertexData = (SVertex*)m_MeshList["sky"]->m_VertexBuffer->Load(numVertex,sizeof(SVertex),0);

	unsigned int index = 0;
	for( int i = 0; i < m_Cols; i++ )
	{
		const float moveXZ = cos( 1.0f ) * i / (m_Cols - 1) ;
		for( int j = 0; j < m_Rows; j++ )
		{	
			const float moveY = (3.141592654f * 2.0f) * j / (m_Rows - 1) ;

			vertexData[index].m_vPosition.x = sin( moveXZ ) * cos( moveY  );
			vertexData[index].m_vPosition.y = cos( moveXZ );
			vertexData[index].m_vPosition.z = sin( moveXZ ) * sin( moveY  );
			vertexData[index].m_vPosition *= m_fOuterRadius;

			vertexData[index].m_vTexCoord.x = j / (m_Rows - 1.0f);
			vertexData[index].m_vTexCoord.y = i / (m_Cols - 1.0f);
			index++;
		}
	}
	m_MeshList["sky"]->m_VertexBuffer->CommitToVRAM(0);


	unsigned int *indexData = m_MeshList["sky"]->m_IndexBuffer->Load(numIndex);

	for( unsigned char i = 0; i < m_Rows - 1; i++)
	{
		for( unsigned char j = 0; j < m_Cols - 1; j++)
		{
			*(indexData++) = i * m_Rows + j;
			*(indexData++) = (i + 1) * m_Rows + j;
			*(indexData++) = (i + 1) * m_Rows + j + 1;

			*(indexData++) = (i + 1) * m_Rows + j + 1;
			*(indexData++) = i * m_Rows + j + 1;
			*(indexData++) = i * m_Rows + j;
		}
	}

	m_MeshList["sky"]->m_IndexBuffer->CommitToVRAM();

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[2];
	
	declaration.m_Elements[0].m_stream = 0;
	declaration.m_Elements[0].m_index = 0;
	declaration.m_Elements[0].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_offset = 0;

	declaration.m_Elements[1].m_stream = 0;
	declaration.m_Elements[1].m_index = 0;
	declaration.m_Elements[1].m_size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_offset = 12;

	declaration.m_ElementCount = 2;

	m_MeshList["sky"]->m_VertexBuffer->SetDeclaration(declaration);
}

math::Vector3d CSkySphere::expv( const math::Vector3d &v )
{
	return math::Vector3d( expf(v.x), expf(v.y), expf(v.z) );
}

LPDIRECT3DTEXTURE9 CSkySphere::GetWrite()
{
	if ( m_bSkyBuffer ) return m_pSkyBuffer;
	return m_pSkyBackBuffer;
}

LPDIRECT3DTEXTURE9 CSkySphere::GetRead()
{
	if ( !m_bSkyBuffer ) return m_pSkyBuffer;
	return m_pSkyBackBuffer;
}

float CSkySphere::scale(float fCos)
{
		float x = 1.0f - fCos;
		return m_fRayleighScaleDepth * exp(-0.00287f + x*(0.459f + x*(3.83f + x*(-6.80f + x*5.25f))));
}

void CSkySphere::UpdateSkyBuffer()
{
		D3DLOCKED_RECT Rect;

		if ( FAILED(GetWrite()->LockRect(0,&Rect,NULL,D3DLOCK_NOSYSLOCK) ) ) 
			exit(-1);

		D3DXVECTOR4_16F * pBuffer = (D3DXVECTOR4_16F *)(Rect.pBits);
		
		UINT nIndex = 0;
		for( UINT x = 0; x < m_nSize; x++ )
		{
			const float fCosxz = cos( 1.0f ) * x / (float)(m_nSize - 1.0f);
			for( UINT y = 0; y < m_nSize; y++ )
			{	
				const float fCosy = (D3DX_PI * 2.0f) * y / (float)(m_nSize - 1.0f);

				math::Vector3d vVecPos, vEye = math::Vector3d(0.0f, m_fInnerRadius + 1e-6f, 0.0f);

				vVecPos.x = sin( fCosxz ) * cos( fCosy  ) * m_fOuterRadius;
				vVecPos.y = cos( fCosxz ) * m_fOuterRadius;
				vVecPos.z = sin( fCosxz ) * sin( fCosy  ) * m_fOuterRadius;

				math::Vector3d v3Pos = vVecPos;
				math::Vector3d v3Ray = v3Pos - vEye;
				float fFar = v3Ray.length();//D3DXVec3Length(&v3Ray);
				v3Ray /= fFar;

				// Calculate the ray's starting position, then calculate its scattering offset
				math::Vector3d v3Start = vEye;
				float fHeight = v3Start.length();//D3DXVec3Length(&v3Start);
				float fDepth = exp(m_fScaleOverScaleDepth * (m_fInnerRadius - vEye.y));
				float fStartAngle = math::dot(v3Ray, v3Start)  / fHeight; //D3DXVec3Dot(&v3Ray, &v3Start) / fHeight;
				float fStartOffset = fDepth * scale(fStartAngle);

				// Initialize the scattering loop variables
				float fSampleLength = fFar / m_nSamples;
				float fScaledLength = fSampleLength * m_fScale;
				math::Vector3d v3SampleRay = v3Ray * fSampleLength;
				math::Vector3d v3SamplePoint = v3Start + v3SampleRay * 0.5f;

				// Now loop through the sample rays
				math::Vector3d v3FrontColor = math::Vector3d(0.0f, 0.0f, 0.0f);
				for(unsigned int i=0; i<m_nSamples; i++)
				{
					float fHeight = v3SamplePoint.length();//D3DXVec3Length(&v3SamplePoint);
					float fDepth = exp(m_fScaleOverScaleDepth * (m_fInnerRadius - fHeight));
					float fLightAngle = math::dot(m_vSunDir,v3SamplePoint) / fHeight; //D3DXVec3Dot(&m_vSunDir, &v3SamplePoint) / fHeight;
					float fCameraAngle = math::dot(v3Ray, v3SamplePoint) / fHeight;//D3DXVec3Dot(&v3Ray, &v3SamplePoint) / fHeight;
					float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
					math::Vector3d v3Attenuate = expv((m_vInvWavelength4 * m_fKr4PI + math::Vector3d(m_fKm4PI, m_fKm4PI, m_fKm4PI)) * -fScatter);
					v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
					v3SamplePoint += v3SampleRay;
				}

				//D3DXVECTOR3 V = vEye - vVecPos;
				//D3DXVec3Normalize( &V, &V );

				pBuffer[nIndex].x = min( v3FrontColor.x, 6.5519996e4f);
				pBuffer[nIndex].y = min( v3FrontColor.y, 6.5519996e4f);
				pBuffer[nIndex].z = min( v3FrontColor.z, 6.5519996e4f);
				pBuffer[nIndex].w = 0.0f;//D3DXVec3Dot(&vSunDir, &V);

				nIndex++;
			}
		}

		GetWrite()->UnlockRect(0);
		m_bSkyBuffer = !m_bSkyBuffer;
}

void CSkySphere::SetTime(float T)
{
		float time = T ;
		float meridian = 1.3788101f;
		float longitude = 1.3852096f;
		float latitude = 0.762127107f;
		int day = 172;

		double t, delta;
		double A, B, C, D, E, F;

		A = 4*D3DX_PI*(day - 80) / 373;
		B = 2*D3DX_PI*(day - 8)  / 355;
		C = 2*D3DX_PI*(day - 81) / 368;

		t = time +
			0.170*sin(A) -
			0.129*sin(B) +
			12*(meridian - longitude)/D3DX_PI;

		delta = 0.4093*sin(C);

		D = D3DX_PI*t/12;

		E = sin(latitude)*sin(delta) -
			cos(latitude)*cos(delta)*cos(D);

		F = (-cos(delta)*sin(D))/(cos(latitude)*sin(delta) -
			sin(latitude)*cos(delta)*cos(D));

		m_fSunTheta = D3DX_PI * 0.5f - (float)asin(E);
		m_fSunPhi = (float)atan(F);
	
		m_vSunDir.x = 0.0f;
		m_vSunDir.y = (float)cos(T * 0.1);
		m_vSunDir.z = (float)sin(T * 0.1);

		math::Vector3d Zenith = math::Vector3d(0,1,0);
		m_fSunTheta = acos(math::dot(m_vSunDir,Zenith));
		

		m_vSunDir.normalize();

		UpdateSkyBuffer();
}


void CSkySphere::Update()
{
	Matrix();
	
	static float time = 0.0f;
	time += 0.04f;

	SetTime(time);
	
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection, "worldViewProj", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetFloat(m_fKrESun , "fKrESun", Core::IShader::VS_SHADER );
		meshIteratorBegin->second->m_Shader->SetFloat( m_fKmESun, "fKmESun", Core::IShader::VS_SHADER );
		math::Vector3d temp = math::Vector3d( (float)m_nSize, 1.0f / m_nSize, 0.0f );
		meshIteratorBegin->second->m_Shader->SetVector( temp, "Tex", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vSunDir,"vSunPos", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vHG,"vHG", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vInvWavelength4,"vInvWavelength", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vEye, "vEye", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetD3DTexture( GetRead(), "tSkyBuffer" ,Core::IShader::VS_SHADER );
		meshIteratorBegin++;
	}
}

void CSkySphere::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_NONE);
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_ZENABLE, FALSE);
	Core::CGlobal::GetDevice()->AlphaTestDisable();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->Draw();
		meshIteratorBegin++;
	}
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_ZENABLE, TRUE);
}