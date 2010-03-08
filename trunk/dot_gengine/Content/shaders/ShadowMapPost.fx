
//-----------------------------------------------------------------------------------------------
//    Copyright (c) 
//
//    Name: ShadowMap.fx
//    Author: Gluharev Aleksi Sergeevith (aivle1@yandex.ru)  aka "Aldaron"
//    24.09.2007
//    HTTP://LASTWORLD.NET.RU
//
// 	Shadow Map   
// 
//-----------------------------------------------------------------------------------------------

float4x4    mat_Light_World_View_Proj; 
float4x4    mat_World_View_Proj;

float4x4    matTexture;

float 	SHADOW_MAP_SIZE = 1024; //������ �������� ��� ��������� �����

//-----------------------------------------------------------------------------------------------
//���������
//-----------------------------------------------------------------------------------------------
struct VS_INPUT_SHADOW
{
  float4 Position : POSITION;
};

struct VSOUTPUT_SHADOW
{
	float4 Position	: POSITION;
	float  Depth	: TEXCOORD0;
};


struct VSOUTPUT_SHADOWMAP
{
   float4 Position   : POSITION;
   float4 TexCoord   : TEXCOORD0;
   float  Depth      : TEXCOORD1;
};
//-----------------------------------------------------------------------------------------------
// ��������
//-----------------------------------------------------------------------------------------------

// ����� ������
texture DepthMap;
sampler DepthSampler = sampler_state
{
	texture = (DepthMap);

	MipFilter = Linear;
	MinFilter = Linear;
	MagFilter = Linear;
	
	AddressU = Clamp;
	AddressV = Clamp;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------
//��������� ������ ��� ������� �������
//-----------------------------------------------------------
VSOUTPUT_SHADOW vs_shadow_depth( VS_INPUT_SHADOW IN)
{
	VSOUTPUT_SHADOW OUT;

	// �������
	OUT.Position = mul( IN.Position, mat_Light_World_View_Proj );

	// �������� ��������� �� ��������� ����� �� �������
	OUT.Depth = OUT.Position.z;

	return OUT;
}
//-----------------------------------------------------------
// ���������� ������ ��� ������� �������
//-----------------------------------------------------------
float4  ps_shadow_depth( VSOUTPUT_SHADOW IN ) : COLOR0
{
	// ���� �������, ����� �������
	return float4( IN.Depth, 0.0f, 0.0f, 1.0f );
}

//-----------------------------------------------------------------------------------------------
// Name: Shadow_Depth
// ��������� ������� ��������, ������� � ���� ������ ��������� �����
//-----------------------------------------------------------------------------------------------
technique Shadow_Depth
{
    pass P0
    {
		VertexShader = compile vs_1_1 vs_shadow_depth();
		PixelShader  = compile ps_2_0 ps_shadow_depth();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------
// ��������� ������, ��� �������� ����� �����
//-----------------------------------------------------------
VSOUTPUT_SHADOWMAP vs_screen_shadow_map(VS_INPUT_SHADOW IN)
{
	VSOUTPUT_SHADOWMAP OUT = (VSOUTPUT_SHADOWMAP)0;

	// ���������
	OUT.Position = mul( IN.Position, mat_World_View_Proj );
		
	// ����� ���������� ����������
	OUT.TexCoord = mul( IN.Position, matTexture );

	return OUT;
} 
//-----------------------------------------------------------
// ���������� ������, ��� �������� ����� �����
//-----------------------------------------------------------
float4 ps_screen_shadow_map( VSOUTPUT_SHADOWMAP IN ) : COLOR0
{
	// ��������� ������ �������
	float TexelSize = 1.0f / SHADOW_MAP_SIZE;
 
	float ShadowTerm = 0.0f; // ������� ���������

	for( int x = -1; x <= 1; x++ )
	for( int y = -1; y <= 1; y++ )
	{

		// �������� �������� ������� �� ��������� �����( �� �������� ������ )
		float DS = tex2Dproj( DepthSampler,IN.TexCoord + float4( x*TexelSize, y*TexelSize, 0.0f, 0.0f ) ).r;

		// ������� �������� Z ����������, � ������ ������� ��������������
		// 0.001f - ���������� ��� ���������� ����������. ����� ��� ��������� ���������, ������� � �������� �������� ���������� ����
		float Z = ( IN.TexCoord.z - 0.001f );
		
		// �������� �������, ���� ��������� ������ ������� �� ����� �����
		if( DS > Z ) ShadowTerm += 1.0f;	// ����
		else		ShadowTerm += 0.25f;	// ����
	}

	// ������� ������� ��������
	ShadowTerm = ShadowTerm / 9.0f;

	return ShadowTerm;
} 

//-----------------------------------------------------------------------------------------------
// Name: Shadow_ShadowMap
// �������� ����� �����
//-----------------------------------------------------------------------------------------------
technique Shadow_ShadowMap
{
    pass P0
    {

	VertexShader = compile vs_1_1 vs_screen_shadow_map();
	PixelShader  = compile ps_2_0 ps_screen_shadow_map();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
