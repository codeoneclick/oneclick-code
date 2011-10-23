#include "CSkyDome.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../../Core/CGlobal.h"
#include "../../Math/Util.h"

using namespace Enviroment;

CSkyDome::CSkyDome()
{
	m_LightRef = NULL;

	m_Cols = 32;
	m_Rows = 32;
	m_nSize = 8; 
	m_nSamples = 2;
	m_fInnerRadius = 20.0f;

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

	m_Name = "sky_dome";
}


void CSkyDome::Load(std::vector<SResource> _resource)
{
	m_LightRef = Game::GetEnviromentControllerInstance()->GetLightInstance();
	
	m_MeshList[m_Name] = new Core::CMesh();
	m_MeshList[m_Name]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList[m_Name]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	m_MeshList[m_Name]->m_TextureArray[0] = Core::CGlobal::GetDevice()->CreateTextureExt(m_nSize,m_nSize,Core::ITexture::BPP_16);

	SResource skyResource = *_resource.begin();
	m_MeshList[m_Name]->m_Shader = CResource::GetShaderControllerInstance()->Load(skyResource.m_ShaderFile);	

	unsigned int numVertex = m_Cols * m_Rows;
	unsigned int numIndex = ( m_Cols - 1 ) * (m_Rows - 1) * 6;

	SVertex* vertexData = (SVertex*)m_MeshList[m_Name]->m_VertexBuffer->Load(numVertex,sizeof(SVertex),0);

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
	m_MeshList[m_Name]->m_VertexBuffer->CommitToVRAM(0);


	unsigned int *indexData = m_MeshList[m_Name]->m_IndexBuffer->Load(numIndex);

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

	m_MeshList[m_Name]->m_IndexBuffer->CommitToVRAM();

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

	m_MeshList[m_Name]->m_VertexBuffer->SetDeclaration(declaration);
}

math::Vector3d CSkyDome::expv( const math::Vector3d &v )
{
	return math::Vector3d( expf(v.x), expf(v.y), expf(v.z) );
}

float CSkyDome::scale(float fCos)
{
		float x = 1.0f - fCos;
		return m_fRayleighScaleDepth * exp(-0.00287f + x*(0.459f + x*(3.83f + x*(-6.80f + x*5.25f))));
}

void CSkyDome::RefreshAtmosphericTexture()
{
	D3DXVECTOR4_16F * pBuffer = (D3DXVECTOR4_16F *)m_MeshList[m_Name]->m_TextureArray[0]->Lock();
	unsigned int nIndex = 0;
	for( unsigned int x = 0; x < m_nSize; x++ )
	{
		const float fCosxz = cos( 1.0f ) * x / (float)(m_nSize - 1.0f);
		for( unsigned int y = 0; y < m_nSize; y++ )
		{	
			const float fCosy = (D3DX_PI * 2.0f) * y / (float)(m_nSize - 1.0f);
			math::Vector3d vVecPos = math::Vector3d(0.0f, m_fInnerRadius + 1e-6f, 0.0f);

			vVecPos.x = sin( fCosxz ) * cos( fCosy  ) * m_fOuterRadius;
			vVecPos.y = cos( fCosxz ) * m_fOuterRadius;
			vVecPos.z = sin( fCosxz ) * sin( fCosy  ) * m_fOuterRadius;

			math::Vector3d v3Pos = vVecPos;
			math::Vector3d v3Ray = v3Pos - m_vEye;
			float fFar = v3Ray.length();
			v3Ray /= fFar;

			math::Vector3d v3Start = m_vEye;
			float fHeight = v3Start.length();
			float fDepth = exp(m_fScaleOverScaleDepth * (m_fInnerRadius - m_vEye.y));
			float fStartAngle = math::dot(v3Ray, v3Start)  / fHeight; 
			float fStartOffset = fDepth * scale(fStartAngle);

			float fSampleLength = fFar / m_nSamples;
			float fScaledLength = fSampleLength * m_fScale;
			math::Vector3d v3SampleRay = v3Ray * fSampleLength;
			math::Vector3d v3SamplePoint = v3Start + v3SampleRay * 0.5f;

			math::Vector3d v3FrontColor = math::Vector3d(0.0f, 0.0f, 0.0f);
			for(unsigned int i=0; i<m_nSamples; i++)
			{
				float fHeight = v3SamplePoint.length();
				float fDepth = exp(m_fScaleOverScaleDepth * (m_fInnerRadius - fHeight));
				float fLightAngle = math::dot(m_LightRef->GetDirection(),v3SamplePoint) / fHeight; 
				float fCameraAngle = math::dot(v3Ray, v3SamplePoint) / fHeight;
				float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
				math::Vector3d v3Attenuate = expv((m_vInvWavelength4 * m_fKr4PI + math::Vector3d(m_fKm4PI, m_fKm4PI, m_fKm4PI)) * -fScatter);
				v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
				v3SamplePoint += v3SampleRay;
			}

			if(x == m_nSize / 2)
				Game::GetEnviromentControllerInstance()->GetCameraInstance()->m_FogColor = v3FrontColor;	

			pBuffer[nIndex].x = v3FrontColor.x;//min( v3FrontColor.x, 6.5519996e4f);
			pBuffer[nIndex].y = v3FrontColor.y;//min( v3FrontColor.y, 6.5519996e4f);
			pBuffer[nIndex].z = v3FrontColor.z;//min( v3FrontColor.z, 6.5519996e4f);
			pBuffer[nIndex].w = 0.0f;

			nIndex++;
		}
	}

	m_MeshList[m_Name]->m_TextureArray[0]->Unlock();
}

void CSkyDome::Update()
{
	Matrix();
	
	RefreshAtmosphericTexture();
	
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection, "worldViewProj", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetFloat(m_fKrESun , "fKrESun", Core::IShader::VS_SHADER );
		meshIteratorBegin->second->m_Shader->SetFloat( m_fKmESun, "fKmESun", Core::IShader::VS_SHADER );
		math::Vector3d temp = math::Vector3d( (float)m_nSize, 1.0f / m_nSize, 0.0f );
		meshIteratorBegin->second->m_Shader->SetVector( temp, "Tex", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_LightRef->GetDirection(),"vSunPos", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vHG,"vHG", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vInvWavelength4,"vInvWavelength", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector( m_vEye, "vEye", Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetTexture(m_MeshList[m_Name]->m_TextureArray[0], "Texture_01" ,Core::IShader::VS_SHADER );
		meshIteratorBegin++;
	}
}

void CSkyDome::Render()
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