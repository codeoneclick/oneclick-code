#include "gSkyDome.h"

gSkyDome::gSkyDome()
{
	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	this->Mesh = NULL;
	this->day_time = 0.0f;
	this->cloud_animation = 0.0f;
	this->Effect = NULL;
	this->time_am = true;
	this->time_length = 0.01f;

	fTheta = 90;

	fog_color.r = 0.01f;
	fog_color.g = 0.01f;
	fog_color.b = 0.1f;

	sky_intensive = 1.0f;

	this->fog_amount = 0;

	this->night_timer = 1.0f;
	this->rise_timer = 0.0f;
	this->day_timer = 0.0f;
	this->evning_timer = 0.0f;
	this->timer_speed = 0.004f;
	this->timer = 0;
	this->clouds_timer = 0.0f;
}

gSkyDome::~gSkyDome()
{
}

void gSkyDome::Create(int id,ID3DXEffect* Effect,ID3DXEffect* Effect_H)
{
	D3DXLoadMeshFromX("Content\\models\\sky_sphere.x",D3DXMESH_MANAGED,gDevice::device, NULL, NULL, NULL, NULL, &Mesh );
	
	DWORD* contiguity_buffer;

	//contiguity_buffer = NULL;
   // contiguity_buffer = new DWORD[this->Mesh->GetNumFaces() * 3];
   // this->Mesh->GenerateAdjacency( 1e-6f, contiguity_buffer ); 

	//D3DXComputeTangentFrameEx( this->Mesh, D3DDECLUSAGE_TEXCOORD, 0, D3DDECLUSAGE_TANGENT, 0, D3DDECLUSAGE_BINORMAL, 0, D3DDECLUSAGE_NORMAL , 0, D3DXTANGENT_CALCULATE_NORMALS, contiguity_buffer, -1.01f,-0.01f, -1.01f, & this->Mesh, NULL );
	//this->Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,contiguity_buffer,NULL,NULL,NULL);
	//delete[] contiguity_buffer;

	gVertex* p_vertex_data = NULL;
    short* p_index_data = NULL;

	float sky_size = 1;
	float sky_height = 1024;

	/*D3DVERTEXELEMENT9 shader_declaration[] =
{
	{0, 0,   D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, 24,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{0, 32,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	{0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
	{0, 56,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
	{0, 72,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
	D3DDECL_END()
};*/


	//D3DXCreateMesh(16,32, D3DXMESH_MANAGED ,shader_declaration,gDevice::device,&this->_Mesh);
	//this->_Mesh->LockVertexBuffer(D3DLOCK_NOSYSLOCK,(LPVOID*)&p_vertex_data);	
	//	unsigned index = 0;
		//for(int i = 0; i < 8; i++)
		//{
	//		p_vertex_data[index].position = D3DXVECTOR3(-sky_size,sky_height,-sky_size);
	//		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
	//		index++;
	//		p_vertex_data[index].position = D3DXVECTOR3(-sky_size,sky_height,sky_size);
	//		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
	//		index++;
	//		p_vertex_data[index].position = D3DXVECTOR3(sky_size,sky_height,-sky_size);
	//		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
	//		index++;
	//		p_vertex_data[index].position = D3DXVECTOR3(sky_size,sky_height,sky_size);
	//		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
	//		index++;
		//}
	//this->_Mesh->UnlockVertexBuffer();

	//index = 0;

	//this->_Mesh->LockIndexBuffer(0,(void**)&p_index_data);
	//int a = 0;
		//for( int i = 0; i < 8; i++)
		//{
	//		p_index_data[index++] = 0;
	//		p_index_data[index++] = 1;
	//		p_index_data[index++] = 2;
//
	//		p_index_data[index++] = 1;
	//		p_index_data[index++] = 3;
	//		p_index_data[index++] = 2;
		//}
	//this->_Mesh->UnlockIndexBuffer();
	

	D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\Sunset.png", &clouds_textures_color);
	D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\SkyNight.png", &clouds_textures_normal);
	D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\SkyDay.png", &sky_textures_normal);
	D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\cloud.dds", &new_cloud_textures_normal);

	//LPD3DXBUFFER errors = NULL;
	//HRESULT error_result;
	//char* error_name;

	this->Effect = gCore::ShadersService()->Find("sky_effect");
	//this->Effect_H = gCore::ShadersService()->Find("clouds_effect");

	this->Effect->SetTexture("SkyTextureNight",clouds_textures_normal);
	this->Effect->SetTexture("SkyTextureSunset",clouds_textures_color);
	this->Effect->SetTexture("SkyTextureDay",sky_textures_normal); 

	//this->Effect->SetTexture("permTexture",new_cloud_textures_normal);
}

void gSkyDome::Update()
{
	
	static int iterator = 0;

	D3DXMatrixTranslation(&translation_matrix, this->Position.x,this->Position.y - 1024, this->Position.z);
	//D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	//D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	//D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	D3DXMatrixScaling(&scale_matrix,this->Scale.x*512,this->Scale.y*512,this->Scale.z*512);
	//rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
	this->matrix = scale_matrix*translation_matrix;
	//world_matrix = this->matrix;

	D3DXMATRIX WorldIT;
	D3DXMATRIX world_view_projection;
	D3DXMATRIX view_inverse;

	D3DXMatrixInverse(&WorldIT,0,&this->matrix);
	D3DXMatrixTranspose(&WorldIT,&WorldIT);  

	D3DXMatrixInverse(&view_inverse,0,&gCore::Camera()->view);

	world_view_projection = world_matrix*gCore::Camera()->view*gCore::Camera()->projection;

	fTheta += 0.0005f;

	float y = (float)cos(this->fTheta);
    float x = (float)sin(this->fTheta);
    float z = (float)sin(this->fTheta);
    float w = 1.0f;

	
	light_direction = D3DXVECTOR4(x,y,z,w);

	gCore::Light()->light_direction.x = light_direction.x;
	gCore::Light()->light_direction.y = -light_direction.y;
	gCore::Light()->light_direction.z = light_direction.z;

	Effect->SetMatrix("matrix_world",&this->matrix);
	Effect->SetMatrix("matrix_view",&gCore::Camera()->view);
	Effect->SetMatrix("matrix_projection",&gCore::Camera()->projection);
	Effect->SetMatrix("matrix_world_inverse_transponse",&WorldIT);
	Effect->SetMatrix("matrix_view_inverse",&view_inverse);
	Effect->SetFloatArray("LightDirection",light_direction,4);
	
	Effect->SetFloat("time",GetTickCount()/2000.0f);

	if(iterator < 10) 
	{
		iterator++;

	}
	else
	{
		iterator = 0;
		Effect->SetFloatArray("SunColor",GetSunColor(-fTheta,2),4);
	}
	
}


D3DXVECTOR4 gSkyDome::GetSunColor(float fTheta, int nTurbidity)
        {
            float fBeta = 0.04608365822050f * nTurbidity - 0.04586025928522f;
            float fTauR, fTauA;
            float *fTau = new float[3];

            float coseno = (float)cos((double)fTheta + 3.14f);
            double factor = (double)fTheta / 3.14f * 180.0;
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

            D3DXVECTOR4 vAttenuation = D3DXVECTOR4(fTau[0], fTau[1], fTau[2], 1.0f);
            return vAttenuation;
        }

void gSkyDome::Render()
{

	//gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	Effect->SetTechnique("SKY");
	Effect->Begin(NULL, 0);
    Effect->BeginPass(0);
    this->Mesh->DrawSubset(NULL);
    Effect->EndPass();
    Effect->End();
	
	
	/*D3DXMATRIX none_matrix;
	D3DXMatrixIdentity(&none_matrix);
	D3DXMatrixTranslation(&none_matrix, this->Position.x,0.0f, this->Position.z);
	D3DXMatrixScaling(&none_matrix,8192.0f,1.0f,8192.0f);
	Effect->SetMatrix("matrix_world",&none_matrix);
    //Device->SetRenderState(D3DRS_ZENABLE, FALSE); 
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	Effect->SetTechnique("CLOUDS");
	Effect->Begin(NULL, 0);
    Effect->BeginPass(0);
	this->_Mesh->DrawSubset(NULL);
    Effect->EndPass();
    Effect->End();
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//Device->SetRenderState(D3DRS_ZENABLE, TRUE); */
}