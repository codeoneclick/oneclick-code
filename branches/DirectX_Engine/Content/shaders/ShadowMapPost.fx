
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

float 	SHADOW_MAP_SIZE = 1024; //Размер текстуры для источника света

//-----------------------------------------------------------------------------------------------
//Структуры
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
// Текстуры
//-----------------------------------------------------------------------------------------------

// Карта глубин
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
//Вершинный шейдер для расчета глубины
//-----------------------------------------------------------
VSOUTPUT_SHADOW vs_shadow_depth( VS_INPUT_SHADOW IN)
{
	VSOUTPUT_SHADOW OUT;

	// Позиция
	OUT.Position = mul( IN.Position, mat_Light_World_View_Proj );

	// Передаем растояние от источника света до верширы
	OUT.Depth = OUT.Position.z;

	return OUT;
}
//-----------------------------------------------------------
// Пиксельный шейдер для расчета глубины
//-----------------------------------------------------------
float4  ps_shadow_depth( VSOUTPUT_SHADOW IN ) : COLOR0
{
	// Цвет пикселя, равен глубине
	return float4( IN.Depth, 0.0f, 0.0f, 1.0f );
}

//-----------------------------------------------------------------------------------------------
// Name: Shadow_Depth
// Вычисляем глубину пикселей, видимых в поле зрения источника света
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
// Вершинный шейдер, для создания карты теней
//-----------------------------------------------------------
VSOUTPUT_SHADOWMAP vs_screen_shadow_map(VS_INPUT_SHADOW IN)
{
	VSOUTPUT_SHADOWMAP OUT = (VSOUTPUT_SHADOWMAP)0;

	// Положение
	OUT.Position = mul( IN.Position, mat_World_View_Proj );
		
	// Новые текстурные координаты
	OUT.TexCoord = mul( IN.Position, matTexture );

	return OUT;
} 
//-----------------------------------------------------------
// Пиксельный шейдер, для создания карты теней
//-----------------------------------------------------------
float4 ps_screen_shadow_map( VSOUTPUT_SHADOWMAP IN ) : COLOR0
{
	// Вычисляем размер текселя
	float TexelSize = 1.0f / SHADOW_MAP_SIZE;
 
	float ShadowTerm = 0.0f; // Уровень затенения

	for( int x = -1; x <= 1; x++ )
	for( int y = -1; y <= 1; y++ )
	{

		// Получаем значение глубины от источника света( из текстуры глубин )
		float DS = tex2Dproj( DepthSampler,IN.TexCoord + float4( x*TexelSize, y*TexelSize, 0.0f, 0.0f ) ).r;

		// Текущее значение Z координаты, с учетом матрицы преобразования
		// 0.001f - необходимо для устранения артефактов. Также оно уменьшает растояние, начиная с которого начинает рисоваться тень
		float Z = ( IN.TexCoord.z - 0.001f );
		
		// Затеняем пиксель, если находится дальше глубины на карте теней
		if( DS > Z ) ShadowTerm += 1.0f;	// Свет
		else		ShadowTerm += 0.25f;	// Тень
	}

	// Находим среднее значение
	ShadowTerm = ShadowTerm / 9.0f;

	return ShadowTerm;
} 

//-----------------------------------------------------------------------------------------------
// Name: Shadow_ShadowMap
// Создание карты теней
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
