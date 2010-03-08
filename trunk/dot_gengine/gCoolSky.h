class gCoolSky
{
private :
    IDirect3DCubeTexture9* sky_texture_color;
    IDirect3DTexture9* clouds_textures_color[2];
	IDirect3DTexture9* star_textures_color;

	ID3DXMesh* SkyMesh;
	ID3DXMesh* CloudMesh;


	ID3DXEffect* SkyEffect;
	ID3DXEffect* CloudEffect;
	float time_of_day;                       
    float moon_intensivity;                
    
	#define _turbidity =  2.25f            

    D3DXVECTOR2 wind_power;
    D3DXVECTOR2 clouds_size;
    D3DXVECTOR2 layers_opacity;

    D3DXVECTOR2 clouds_move_outer;
    D3DXVECTOR2 clouds_move_inner;


	//#define LATITUDE = 0.6981317f   

    #define SKY_RADIUS = 180.0f        

    D3DXVECTOR3 CLOUDS_NIGHT_COLOR;
    D3DXVECTOR3 CLOUDS_DAY_COLOR;

    //#define SUN_RISE = (float)(3.14f * 1.0f / 12.0f);
   // #define SUN_SET = (float)(3.14f * 1.0f / -10.0f);

	float Saturate(float value);
	inline float Lerp(float value, float min, float max) { return (value - min) / (max - min);}
	AltAzAngles CalculateSunPosition(float julianDate, float latitude);
	D3DXVECTOR3 SkyZenithColor(float turbidity, float sunTheta); 


public :
	int Id;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Color;
	D3DXMATRIX matrix;

public :
	gCoolSky();
	~gCoolSky() ;
	void Create(int id);
	void Render();
	void Update(gCamera *camera,gLight *light);
};



gCoolSky::gCoolSky()
{
    int a = (14 - 9) / 12, y = 1975 + 4800 - a, m = 9 + 12 * a - 3;
    this->time_of_day = 95 + (153 * m + 2) / 5 + y * 365 + y / 4 - y / 100 + y / 400 - 32045;
    this->time_of_day -= 2442414;
    this->time_of_day -= 1.0f / 24.0f;

	CLOUDS_NIGHT_COLOR = D3DXVECTOR3(0.175f, 0.175f, 0.2f);
    CLOUDS_DAY_COLOR = D3DXVECTOR3(0.9f, 0.9f, 0.9f);

	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	this->SkyMesh = NULL;
	this->CloudMesh = NULL;
	this->SkyEffect = NULL;
	this->CloudEffect = NULL;
}

gCoolSky::~gCoolSky()
{
}

void gCoolSky::Create(int id)
{
	//_skyHemisphere = _scene.CreateMeshBuilder("SkyHemisphere");
    //        _cloudsDome = _scene.CreateMeshBuilder("CloudsDome");

    //        InitDomes();
	D3DXLoadMeshFromX("Content\\models\\sky_01.x",D3DXMESH_MANAGED,Device, NULL, NULL, NULL, NULL, &SkyMesh );
	D3DXLoadMeshFromX("Content\\models\\sky_01.x",D3DXMESH_MANAGED,Device, NULL, NULL, NULL, NULL, &CloudMesh );

	D3DXCreateTextureFromFile(Device,"Content\\textures\\starmap.dds",&star_textures_color);
	D3DXCreateCubeTextureFromFile(Device, "Content\\textures\\cubenormalizer_ulq.dds", &sky_texture_color);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\cloudslots.dds", &clouds_textures_color[0]);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\cloudsless.dds", &clouds_textures_color[1]);
	
	LPD3DXBUFFER errors = NULL;
	HRESULT error_result;
	char* error_name;

	//error_result  = D3DXCreateEffectFromFile(Device, "Content\\shaders\\skyshader.fx", NULL, NULL, 0, NULL, &SkyEffect, &errors);
	error_result  = D3DXCreateEffectFromFile(Device, "Content\\shaders\\cloudsshader.fx", NULL, NULL, 0, NULL, &CloudEffect, &errors);

	if(FAILED( error_result ))
        error_name = ( char* )errors->GetBufferPointer();

	CloudEffect->SetTexture("texCubeNormalize",sky_texture_color);

	//Effect->SetTechnique("sky");
	//Effect->SetTexture("surfaceTexture",sky_texture_color);
	//Effect->SetTexture("cloud",clouds_textures_color[0]);   
}

/*float gCoolSky::Saturate(float value){
    if(value > 1.0f) value = 1.0f;
    if (value < 0.0f) value = 0.0f;
    return value;
}

AltAzAngles gCoolSky::CalculateSunPosition(float julianDate, float latitude) {
            AltAzAngles angles;
            float gamma = 4.93073839645544f;

            float meanAnomaly = 6.2398418f + 0.0172019696455f * julianDate;
            float eccAnomaly = 2.0f * (float)atan(1.016862146f * tan(meanAnomaly / 2.0f));
            eccAnomaly = meanAnomaly + 0.016720f * (float)sin(eccAnomaly);
            float trueAnomaly = 2.0f * (float)atan(1.016862146f * tan(eccAnomaly / 2.0f));
            float lambda = gamma + trueAnomaly;

            float dec = (float)asin(sin(lambda) * 0.39778375791855f);
            float ra = (float)atan(tan(lambda) * 0.917479f);
            if (cos(lambda) < 0.0f) ra += 3.14f;

            float gha = 1.7457f + 6.300388098526f * julianDate;
            float latSun = dec;
            float lonSun = ra - gha;

            // To prevent over-calculation
            float cosLonSun = (float)cos(lonSun);
            float sinLonSun = (float)sin(lonSun);
            float cosLatSun = (float)cos(latSun);
            float sinLatSun = (float)sin(latSun);
            float sinLat = (float)sin(latitude);
            float cosLat = (float)cos(latitude);

            angles.altitude = (float)asin(sinLat * sinLatSun + cosLat * cosLatSun * cosLonSun);
            float west = cosLatSun * sinLonSun;
            float south = -cosLat * sinLatSun + sinLat * cosLatSun * cosLonSun;
            angles.azimuth = (float)atan(west / south);

            if (south >= 0.0f) angles.azimuth = 3.14f - angles.azimuth;
            if (south < 0.0f) angles.azimuth = -angles.azimuth;
            if (angles.azimuth < 0.0f) angles.azimuth += 3.14f*2.0f;

            return angles;
}

float gCoolSky::Chromaticity(float[,] ZC, float turbidity, float sunTheta) {
            // Theta, Theta² and Theta³
            float sunThetaSquared = sunTheta * sunTheta;
            float sunThetaCubed = sunThetaSquared * sunTheta;

            // Turbidity²
            float turbiditySquared = turbidity * turbidity;

            // Vectors will help us with the computation
            D3DXVECTOR3 turbidityVector = D3DXVECTOR3(turbiditySquared, turbidity, 1.0f);
            D3DXVECTOR4 sunThetaVector = D3DXVECTOR4(sunThetaCubed, sunThetaSquared, sunTheta, 1.0f);

            return MulChromaticityMatrices(turbidityVector, ZC, sunThetaVector);
        }

D3DXVECTOR3 gCoolSky::SkyZenithColor(float turbidity, float sunTheta) {
            D3DXVECTOR3 zenith;

            // Zenith luminance
            float chi = (4.0f / 9.0f - turbidity / 120.0f) * (3.14f - 2.0f * sunTheta);
            zenith.z = (4.0453f * turbidity - 4.971f) * (float)tan(chi) - 0.2155f * turbidity + 2.4192f;
            if (zenith.z < 0.0f) zenith.z = -zenith.z;

            // Zenith chromacity	
            zenith.x = Chromaticity(xZenithCoeff, turbidity, sunTheta);
            zenith.y = Chromaticity(yZenithCoeff, turbidity, sunTheta);
            return zenith;
}*/

void gCoolSky::Update(gCamera *camera,gLight *light)
{
	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scale_matrix;
	D3DXMATRIX world_matrix;


	D3DXMatrixTranslation(&translation_matrix, this->Position.x,this->Position.y, this->Position.z);
	D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	D3DXMatrixScaling(&scale_matrix,this->Scale.x*10.0f,this->Scale.y*10.0f,this->Scale.z*10.0f);

	rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
	this->matrix = scale_matrix*rotation_matrix*translation_matrix;
	Device->SetTransform(D3DTS_WORLD, &this->matrix);

	world_matrix = this->matrix;

	//AltAzAngles sunAngles = AltAzAngles();
	//sunAngles = CalculateSunPosition(time_of_day + 0.2f, 0.6981317f);
    //D3DXVECTOR3 sunNormedPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//sunNormedPos = normalize(sunNormedPos);
	
    //_maths.TVVec3Normalize(ref sunNormedPos, sunNormedPos);
    // float sunTheta 1.57f;//= SkyMaths.VectorToTheta(sunNormedPos);
	// SkyEffect->SetFloat("_sunTheta", sunTheta);
	// SkyEffect->SetValue("_sunVector",sunNormedPos,3*sizeof(float));
     //_skyShader.SetEffectParamFloat("_sunTheta", sunTheta);
     //_skyShader.SetEffectParamVector3("_sunVector", sunNormedPos);

            // Set the size of the flares depending on viewport size and a dot product
           // TV_3DMATRIX tempMatrix = _camera.GetRotationMatrix();
          //  TV_3DVECTOR normedLookAt = new TV_3DVECTOR(tempMatrix.m31, tempMatrix.m32, tempMatrix.m33);
          //  float dotProduct = _maths.TVVec3Dot(normedLookAt, sunNormedPos);
            //_sunHalfFlareSize = _viewportSize.x / 5f * (dotProduct * dotProduct * dotProduct);

            // Sun lightning direction
            //TV_3DVECTOR sunDirection = new TV_3DVECTOR();
            //_maths.TVVec3Subtract(ref sunDirection, _sunPosition, camPosXZ);
		 //#define SUN_RISE = (float)(3.14f * 1.0f / 12.0f);
   // #define SUN_SET = (float)(3.14f * 1.0f / -10.0f);

            //float sunIntensity = Saturate(Lerp(sunAngles.altitude, 3.14f * 1.0f / -10.0f, 3.14f * 1.0f / 12.0f));

            // Stars and moon opacity
           // moon_intensivity = Saturate(Lerp(sunAngles.altitude, 0.0f, 3.14f * 1.0f / -10.0f)) * 0.95f;
           // SkyEffect->SetFloat("_starsIntensity", moon_intensivity);
           // moon_intensivity += 0.05f;
            //_matFact.SetEmissive(_globals.GetMat("Moon"), _moonIntensity, _moonIntensity, _moonIntensity, 0f);

            // A hack to kill the orange tones in the nightsky
           //  SkyEffect->SetFloat("_nightDarkness", 1.0f - (moon_intensivity - 0.05f));

            // Calculate the constant matrices
           // D3DXVECTOR3 _zenithColors = SkyMaths.SkyZenithColor(_turbidity, sunTheta);
           // SkyMaths.xyYCoeffs _distribCoeffs = SkyMaths.DistributionCoefficients(_turbidity);
           // _skyShader.SetEffectParamVector3("_zenithColor", _zenithColors.AsVector3);
           // for (int i=0; i<5; i++) {
           //     _skyShader.SetEffectParamFloat("_xDistribCoeffs[" + i + "]", _distribCoeffs.x[i]);
           //     _skyShader.SetEffectParamFloat("_yDistribCoeffs[" + i + "]", _distribCoeffs.y[i]);
           //     _skyShader.SetEffectParamFloat("_YDistribCoeffs[" + i + "]", _distribCoeffs.Y[i]);
           // }

            // Set the adaptative luminance and gamma corrections
           // float gamma = 1f / (1.6f + (_turbidity - 2f) * 0.1f);
           // _skyShader.SetEffectParamFloat("_invGammaCorrection", 1.5f * gamma);
           // _skyShader.SetEffectParamFloat("_invPowLumFactor", gamma);
           // _skyShader.SetEffectParamFloat("_invNegMaxLum", -1.25f / SkyMaths.MaximumLuminance(
           //     _turbidity, sunTheta, _zenithColors, _distribCoeffs));

            // Clouds movement
           // TV_2DVECTOR _windEffectInner = new TV_2DVECTOR(_windPower.x * _accumulatedTime, _windPower.y * _accumulatedTime);
           // _maths.TVVec2Add(ref _cloudsTranslationInner, _cloudsTranslationInner, _windEffectInner);
           // TV_2DVECTOR _windEffectOuter = new TV_2DVECTOR(_windPower.x / 2f * _accumulatedTime, _windPower.y / 2f * _accumulatedTime);
           // _maths.TVVec2Add(ref _cloudsTranslationOuter, _cloudsTranslationOuter, _windEffectOuter);
            //_cloudsShader.SetEffectParamVector2("_cloudsTranslation[0]", _cloudsTranslationOuter);
            //_cloudsShader.SetEffectParamVector2("_cloudsTranslation[1]", _cloudsTranslationInner);

            // Clouds coloring
            //TV_COLOR atmoCol = SkyMaths.AtmosphereColor(_turbidity, sunTheta, _zenithColors, _distribCoeffs);
           // TV_3DVECTOR atmoColVec = new TV_3DVECTOR(atmoCol.r, atmoCol.g, atmoCol.b);
           // float dayState = SkyMaths.Saturate(SkyMaths.Lerp(sunAngles.altitude, (float)(Math.PI * 1f / (6f - _turbidity / 2f)), SUN_RISE));
           // _maths.TVVec3Lerp(ref atmoColVec, CLOUDS_NIGHT_COLOR, atmoColVec, sunIntensity);
           // _maths.TVVec3Lerp(ref atmoColVec, CLOUDS_DAY_COLOR, atmoColVec, dayState);
            //_cloudsShader.SetEffectParamVector3("_cloudsColor", atmoColVec);

	//day_time = light->light_position.y/42.66f;
	//long div = 100000;
   // day_time += 0.01f;//((float)GetTickCount()/ div);
	//if(day_time > 24.0f)
	//	day_time = 0.0f;
    // cloud_animation += 0.00001f;
    // if (cloud_animation > 1)
    //      cloud_animation = 0;

	D3DXVECTOR4 camera_position = D3DXVECTOR4(camera->Position.x,camera->Position.y,camera->Position.z,0.0f);

	D3DXMATRIX world_view_projection_matrix = world_matrix*camera->view*camera->projection;
    CloudEffect->SetMatrix("matWorldViewProj",&world_view_projection_matrix);
   // Effect->SetMatrix("matrixView",&camera->view);
   // Effect->SetMatrix("matrixProjection",&camera->projection);
	//Effect->SetVector("EyePosition",&camera_position);
	//Effect->SetFloat("timeOfDay",day_time);
   // Effect->SetFloat("cloudTimer",cloud_animation);
}

void gCoolSky::Render(){
	 Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	 CloudEffect->Begin(NULL, 0);
     CloudEffect->BeginPass(0);
	 for(int i = 0; i < 6; i++)
            this->CloudMesh->DrawSubset(i);
     CloudEffect->EndPass();
     CloudEffect->End();
	 Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}