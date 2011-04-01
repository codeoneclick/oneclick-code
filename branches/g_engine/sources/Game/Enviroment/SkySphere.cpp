#include "SkySphere.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../../Core/CGlobal.h"
#include "../../Math/Util.h"

using namespace Enviroment;

CSkySphere::CSkySphere()
{

}


void CSkySphere::Load(std::vector<SResource> _resource)
{
	D3DXLoadMeshFromX("Content\\models\\skySphere.x",D3DXMESH_MANAGED,Core::CGlobal::GetDevice()->Ref(), NULL, NULL, NULL, NULL, &m_d3dMesh );
	int bytePerVertex = m_d3dMesh->GetNumBytesPerVertex();
	int numVertex = m_d3dMesh->GetNumVertices();
	SXVertex *XVertexData = new SXVertex[numVertex];
	m_d3dMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&XVertexData);
	m_d3dMesh->UnlockVertexBuffer();

	int numIndeces = m_d3dMesh->GetNumFaces() * 3;
	unsigned short *XIndexData = new unsigned short[numIndeces];
	m_d3dMesh->LockIndexBuffer(D3DLOCK_READONLY,(LPVOID*)&XIndexData);
	m_d3dMesh->UnlockIndexBuffer();

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

	SVertex* vertexData = (SVertex*)m_MeshList["sky"]->m_VertexBuffer->Load(numVertex,sizeof(SVertex),0);

	for(unsigned int i = 0; i < numVertex; ++i)
	{
		vertexData[i].m_vPosition = XVertexData[i].m_vPosition;
		vertexData[i].m_vTexCoord = XVertexData[i].m_vTexCoord;
	}

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

	m_MeshList["sky"]->m_VertexBuffer->CommitToVRAM(0);
	m_MeshList["sky"]->m_VertexBuffer->SetDeclaration(declaration);

	unsigned int *indexData = m_MeshList["sky"]->m_IndexBuffer->Load(numIndeces);

	for(unsigned int i = 0; i < numIndeces; i++)
	{
		indexData[i] = XIndexData[i];
	}

	m_MeshList["sky"]->m_IndexBuffer->CommitToVRAM();
}

math::Vector3d CSkySphere::GetSunColor(float _theta, int _turbidity)
{
    float fBeta = 0.04608365822050f * _turbidity - 0.04586025928522f;
    float fTauR, fTauA;
    float *fTau = new float[3];

    float coseno = (float)cos((double)_theta + 3.14f);
    double factor = (double)_theta / 3.14f * 180.0;
    double jarl = pow(93.885 - factor, -1.253);
    float potencia = (float)jarl;
    float m = 1.0f / (coseno + 0.15f * potencia);

    int i;
    float *fLambda = new float[3];
    fLambda[0] = 0.65f;
    fLambda[1] = 0.57f;
    fLambda[2] = 0.475f;


    for (i = 0; i < 3; i++)
    {
        potencia = (float)pow((double)fLambda[i], 4.0);
        fTauR = (float)exp((double)(-m * 0.008735f * potencia));

        const float fAlpha = 1.3f;
        potencia = (float)pow((double)fLambda[i], (double)-fAlpha);
        if (m < 0.0f)
            fTau[i] = 0.0f;
        else
        {
            fTauA = (float)exp((double)(-m * fBeta * potencia));
            fTau[i] = fTauR * fTauA;
        }

    }
    return  math::Vector3d(fTau[0], fTau[1], fTau[2]);
}

void CSkySphere::Update()
{
	Matrix();

	//m_vScale = math::Vector3d(32.0f,32.0f,32.0f);

	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);

		static float fTheta = 0.0f;
		fTheta += 0.001f;
		float y = (float)cos(fTheta);
		float x = (float)sin(fTheta);
		float z = (float)sin(fTheta);
		math::Vector3d vLightDir = math::Vector3d(x,y,z);

		meshIteratorBegin->second->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector(GetSunColor(-fTheta,2),"vSunColor",Core::IShader::VS_SHADER);
		meshIteratorBegin++;
	}
}

void CSkySphere::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_NONE);
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_ZENABLE, FALSE);//AlphaBlendDisable();
	//Core::CGlobal::GetDevice()->AlphaTestEnable();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[1],"Texture_02",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[2],"Texture_03",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->Draw();
		meshIteratorBegin++;
	}
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_ZENABLE, TRUE);
	//Core::CGlobal::GetDevice()->AlphaBlendEnable();
	//Core::CGlobal::GetDevice()->AlphaTestDisable();
}