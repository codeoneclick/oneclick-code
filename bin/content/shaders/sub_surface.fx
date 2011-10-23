float4x4 mWorldViewProjection;
float4x4 mWorld;

float3 vCameraEye;
float3 vLightDir;

texture Texture_01;
sampler Texture_01_Sampler = sampler_state {
	Texture = <Texture_01>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_01_NH;
sampler Texture_01_NH_Sampler = sampler_state {
	Texture = <Texture_01_NH>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
	float3 vNormal		  : NORMAL;
	float3 vTangent		  : TEXCOORD1;
	float3 vBinormal	  : TEXCOORD2;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float3 vWorldPosition   : TEXCOORD0;
   float3 vCameraEye       : TEXCOORD1;
   float3 vLightDir        : TEXCOORD2;
   float3 vNormal          : TEXCOORD3;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vWorldPosition = OUT.vPosition.xyz;
   OUT.
   
   OUT.vTexCoord = IN.vTexCoord;
   
   float3x3 mTangentSpace;
   mTangentSpace[0] = mul(-IN.vTangent, mWorld);
   mTangentSpace[1] = mul(-IN.vBinormal, mWorld);
   mTangentSpace[2] = mul(-IN.vNormal, mWorld);
   
   OUT.vLightDir = mul(mTangentSpace,vLightDir);
   OUT.vCameraEye = mul(mTangentSpace,mul(IN.vPosition, mWorld) - vCameraEye);
   return OUT;
}


 
30	float halfLambert(in vec3 vect1, in vec3 vect2)
31	{
32	    float product = dot(vect1,vect2);
33	    return product * 0.5 + 0.5;
34	}
35	 
36	float blinnPhongSpecular(in vec3 normalVec, in vec3 lightVec, in float specPower)
37	{
38	    vec3 halfAngle = normalize(normalVec + lightVec);
39	    return pow(clamp(0.0,1.0,dot(normalVec,halfAngle)),specPower);
40	}
41	 
42	// Main fake sub-surface scatter lighting function
43	 
44	vec4 subScatterFS()
45	{
46	    float attenuation = 10.0 * (1.0 / distance(lightPos,vertPos));
47	    vec3 eVec = normalize(eyeVec);
48	    vec3 lVec = normalize(lightVec);
49	    vec3 wNorm = normalize(worldNormal);
50	 
51	    vec4 dotLN = vec4(halfLambert(lVec,wNorm) * attenuation);
52	    //dotLN *= texture2D(Texture, gl_TexCoord[0].xy);
53	    dotLN *= BaseColor;
54	 
55	    vec3 indirectLightComponent = vec3(MaterialThickness * max(0.0,dot(-wNorm,lVec)));
56	    indirectLightComponent += MaterialThickness * halfLambert(-eVec,lVec);
57	    indirectLightComponent *= attenuation;
58	    indirectLightComponent.r *= ExtinctionCoefficient.r;
59	    indirectLightComponent.g *= ExtinctionCoefficient.g;
60	    indirectLightComponent.b *= ExtinctionCoefficient.b;
61	 
62	    vec3 rim = vec3(1.0 - max(0.0,dot(wNorm,eVec)));
63	    rim *= rim;
64	    rim *= max(0.0,dot(wNorm,lVec)) * SpecColor.rgb;
65	 
66	    vec4 finalCol = dotLN + vec4(indirectLightComponent,1.0);
67	    finalCol.rgb += (rim * RimScalar * attenuation * finalCol.a);
68	    finalCol.rgb += vec3(blinnPhongSpecular(wNorm,lVec,SpecPower) * attenuation * SpecColor * finalCol.a * 0.05);
69	    finalCol.rgb *= LightColor.rgb;
70	 
71	    return finalCol;
72	}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
    IN.vCameraEye = normalize(IN.vCameraEye);
    IN.vLightDir = normalize(IN.vLightDir);
   
    float fHeightPower = 0.0f;
    float2 vDisplaceTexCoord = IN.vTexCoord;
    for(int i = 0; i < 0; i++)
    {
		 fHeightPower = tex2D(Texture_01_NH_Sampler, IN.vTexCoord).a;
		 fHeightPower *= 0.04f;
		 vDisplaceTexCoord = vDisplaceTexCoord + (-IN.vCameraEye.xy * fHeightPower);
    }
    
    float3 vNormalColor = tex2D(Texture_01_NH_Sampler, vDisplaceTexCoord).rgb;
	
	vNormalColor = vNormalColor * 2 - 1;
	vNormalColor = normalize(vNormalColor);
	
	float4 vDiffuseColor =  tex2D( Texture_01_Sampler, vDisplaceTexCoord);
	
	float4 vAmbientColor = vDiffuseColor;
	
	float vDiffuseFactor = saturate(dot(vNormalColor, IN.vLightDir));
	float3 vLightReflect = reflect(IN.vLightDir, vNormalColor);
	float vSpecularFactor = pow(max(0.0f, dot(vLightReflect, IN.vCameraEye) ), fSpecularPower);
	
	float rim = 1.0f - max(0.0f,dot(vNormalColor,IN.vCameraEye));
	rim *= rim;
	//rim *= max(0.0,dot(vNormalColor,IN.vLightDir));
	
	//float rim = smoothstep(0.5f , 1.0f ,1.0f - dot(vNormalColor,IN.vCameraEye));
  
    float4 vColor = vDiffuseColor * vDiffuseFactor + vAmbientColor * fAmbientFactor + vSpecularFactor * vSpecularColor +  float4(rim,0.0f,0.0f,1.0f);
    return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}