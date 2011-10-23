class gEditService
{
	public:
		static void EditGround(float incHeight,float radius, float positionX, float positionZ);
};

void gEditService::EditGround(float incHeight,float radius, float positionX, float positionZ)
{
	int currentMapChanckIndexI = (int)(positionX / (640));
	int currentMapChanckIndexJ = (int)(positionZ / (640));
	for(unsigned index = 0; index < gEnviroment::MapsService()->Maps().size(); ++index)
	{	
		float height = 0.0f;
		int minIndX = (int)floor(positionX - radius)/10.0f;
		int minIndZ = (int)floor(positionZ - radius)/10.0f;
		int maxIndX = (int)floor(positionX + radius)/10.0f;
		int maxIndZ = (int)floor(positionZ + radius)/10.0f;

		for (int x = minIndX; x < maxIndX; x++)
			for (int z = minIndZ; z < maxIndZ; z++) {
				if((x < 0) || (z < 0)) continue;
				float distance = D3DXVec2Length(&D3DXVECTOR2(x*10 - positionX, z*10 - positionZ));
				if (distance > radius)
					continue;
				float riseCoeff=distance/radius;
				riseCoeff=1.0f-riseCoeff*riseCoeff;

				float deltaHeight = incHeight * riseCoeff;

				float Height=gEnviroment::MapsService()->GetMapHeightMap()[x][z] + deltaHeight;
				Height = floor(Height + 0.5f);

				gEnviroment::MapsService()->GetMapHeightMap()[x][z] = Height;
			}
	int vertNumber = 0;
	float middleHeight = 0;
	int CashCount = 0;
	for (int x = minIndX; x < maxIndX; x++)
		for (int z = minIndZ; z < maxIndZ; z++) {
			if((x <= 0) || (z <= 0)) continue;
			float leng = D3DXVec2Length(&D3DXVECTOR2(x*10 - positionX, z*10 - positionZ));
			float coeff = radius - leng;
			height =  gEnviroment::MapsService()->GetMapHeightMap()[x][z];
			middleHeight = 0;
			if (coeff > 0) {
				middleHeight = height;
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x-1][z];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x+1][z];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x-1][z-1];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x][z-1];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x+1][z-1];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x-1][z+1];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x][z+1];
				middleHeight += gEnviroment::MapsService()->GetMapHeightMap()[x+1][z+1];
				height = middleHeight / 9.0f;
				height = floor(height + 0.5f);
			}
			gEnviroment::MapsService()->GetMapHeightMap()[x][z] = height;
		}
	}

	for(int mapChanckIndexI = (currentMapChanckIndexI - 1); mapChanckIndexI <= (currentMapChanckIndexI + 1); ++mapChanckIndexI)
		for(int mapChanckIndexJ = (currentMapChanckIndexJ - 1); mapChanckIndexJ <= (currentMapChanckIndexJ + 1); ++mapChanckIndexJ)
			for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index)
				if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() == mapChanckIndexI)&&(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() == mapChanckIndexJ))
					gEnviroment::MapsService()->Maps()[map_index]->EditGround();
}
