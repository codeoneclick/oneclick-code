#include "gMapsService.h"

void gMapsService::Load()
{
	this->map_heightmap			= new float*[FILE_MAP_SIZE+1];
	this->map_decoration_mask	= new gMapDecoration*[FILE_MAP_SIZE+1];
	this->map_tile_mask			= new gMapTileMask*[FILE_MAP_SIZE+1];

	for(int i = 0; i < FILE_MAP_SIZE+1; ++i){
		this->map_heightmap[i]			= new float[FILE_MAP_SIZE+1];
		this->map_decoration_mask[i]	= new gMapDecoration[FILE_MAP_SIZE+1];
		this->map_tile_mask[i]			= new gMapTileMask[FILE_MAP_SIZE+1];
	}


	ifstream input_stream;
	
	float float_value = 0;
	BYTE  byte_value  = 0;
	
	/*input_stream.open("Content\\maps\\world_byte.map",ios::in|ios::binary);
	input_stream.seekg (0, std::ios::end);
	int size = input_stream.tellg();
    input_stream.seekg (0, std::ios::beg);
	
	for(unsigned i = 0;i < (FILE_MAP_SIZE + 1);++i)
		for(unsigned j = 0;j < (FILE_MAP_SIZE + 1);++j){
			input_stream>>float_value;
			this->map_heightmap[i][j]			= float_value;
			
			input_stream>>byte_value;
			this->map_tile_mask[i][j].grass		= byte_value;
			input_stream>>byte_value;
			this->map_tile_mask[i][j].sand		= byte_value;
			input_stream>>byte_value;
			this->map_tile_mask[i][j].rock		= byte_value;
			
			input_stream>>byte_value;
			//this->map_decoration_mask[i][j].	= byte_value;
			input_stream>>byte_value;
			//this->map_decoration_mask[i][j].g	= byte_value;
			input_stream>>byte_value;
			//this->map_decoration_mask[i][j].b	= byte_value;
		}
	input_stream.close();*/


	//input_stream.open("Content\\maps\\map.raw",ios::in|ios::binary);
	//input_stream.seekg (0, std::ios::end);
	//size = input_stream.tellg();
    //input_stream.seekg (0, std::ios::beg);

	FILE *file = NULL;
	file = fopen("Content\\maps\\map.raw","rb");
	unsigned char byteValue;
	
	for(unsigned i = 0;i < FILE_MAP_SIZE;++i)
		for(unsigned j = 0;j < FILE_MAP_SIZE;++j){
			fread(&byteValue,sizeof(unsigned char),1,file);
			this->map_heightmap[i][j] = (float)byteValue;
		}
	//input_stream.close();
	fclose(file);

	file = NULL;
	file = fopen("Content\\maps\\map_road.raw","rb");
	
	for(unsigned i = 0;i < FILE_MAP_SIZE;++i)
		for(unsigned j = 0;j < FILE_MAP_SIZE;++j){
			fread(&byteValue,sizeof(unsigned char),1,file);
			//if(byteValue == 255)
				this->map_decoration_mask[i][j].road = byteValue/192;//1.0f;
			//else
			//	this->map_decoration_mask[i][j].road = 0.0f;
		}
	//input_stream.close();
	fclose(file);


	this->AutoGenerateMapTiles();

	/*char* szFile = "Content\\maps\\new_map.bmp";

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	// Open file.
	ifstream bmpfile (szFile , ios::in | ios::binary);
	if (! bmpfile.is_open()) return;		// Error opening file

	// Load bitmap fileheader & infoheader
	bmpfile.read ((char*)&bmfh,sizeof (BITMAPFILEHEADER));
	bmpfile.read ((char*)&bmih,sizeof (BITMAPINFOHEADER));

	// Check filetype signature
	if (bmfh.bfType!='MB') return;		// File is not BMP

	int Width,Height;		// Dimensions
	int BPP;				// Bits Per Pixel.
	int BytesPerRow;		// Row Width (in bytes).
	BYTE * Raster;			// Bits of the Image.
	RGBQUAD * Palette;		// RGB Palette for the image.
	BITMAPINFO * pbmi;		// BITMAPINFO structure

	// Assign some short variables:
	BPP=bmih.biBitCount;
	Width=bmih.biWidth;
	Height= (bmih.biHeight>0) ? bmih.biHeight : -bmih.biHeight; // absoulte value
	BytesPerRow = Width * BPP / 8;
	BytesPerRow += (4-BytesPerRow%4) % 4;	// int alignment

	// If BPP aren't 24, load Palette:
	if (BPP==24) pbmi=(BITMAPINFO*)new char [sizeof(BITMAPINFO)];
	else
	{
		pbmi=(BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER)+(1<<BPP)*sizeof(RGBQUAD)];
		Palette=(RGBQUAD*)((char*)pbmi+sizeof(BITMAPINFOHEADER));
		bmpfile.read ((char*)Palette,sizeof (RGBQUAD) * (1<<BPP));
	}
	pbmi->bmiHeader=bmih;

	// Load Raster
	bmpfile.seekg (bmfh.bfOffBits,ios::beg);

	//Raster= new BYTE[BytesPerRow*Height];

	// (if height is positive the bmp is bottom-up, read it reversed)
	//if (bmih.biHeight>0)
	//	for (int n=Height-1;n>=0;n--)
	//		bmpfile.read (Raster+BytesPerRow*n,BytesPerRow);
	//else
	//bmpfile.read (Raster,BytesPerRow*Height);

	// so, we always have a up-bottom raster (that is negative height for windows):
	//pbmi->bmiHeader.biHeight=-Height;

	

	/*int bit_index = 0;
	for(unsigned i = 0;i < (FILE_MAP_SIZE + 1);++i)
		for(unsigned j = 0;j < (FILE_MAP_SIZE + 1);++j){
			this->map_heightmap[i][j] = 0;
			bmpfile>>byte_value;
			this->map_heightmap[i][j] += byte_value;//Raster[bit_index];
			bit_index++;
			bmpfile>>byte_value;
			this->map_heightmap[i][j] += byte_value;//Raster[bit_index];
			bit_index++;
			 bmpfile>>byte_value;
			this->map_heightmap[i][j] += byte_value;//Raster[bit_index];
			bit_index++;
		}*/

	//bmpfile.close();

	int maps_main_index = 0;
	for(int index_i = 0; index_i < sqrt((float)NUMBER_OF_MAPS); ++index_i)
	for(int index_j = 0; index_j < sqrt((float)NUMBER_OF_MAPS); ++index_j){
		this->map.push_back(new gMap(index_i,index_j));
		this->map[maps_main_index]->SetMapHeights(this->map_heightmap);
		this->map[maps_main_index]->SetTextureMask(this->map_tile_mask);
		this->map[maps_main_index]->SetDecorationMask(this->map_decoration_mask);
		this->map[maps_main_index]->Create();
		this->map[maps_main_index]->Textures();
		maps_main_index++;
	}
}

void gMapsService::AutoGenerateMapTiles()
{
	for(int i = 0; i < FILE_MAP_SIZE; ++i)
		for(int j = 0; j < FILE_MAP_SIZE; ++j)
		{
			this->map_tile_mask[i][j].grass = 1.0f;
			this->map_tile_mask[i][j].sand = 0.0f;
			this->map_tile_mask[i][j].rock = 0.0f;
		}

	for(int i = 0; i < FILE_MAP_SIZE; ++i)
		for(int j = 0; j < FILE_MAP_SIZE; ++j)
		{
			if(this->map_heightmap[i][j] <= 140.0f)
				for(int x = (i - 5); x <= (i + 5); ++x)
					for(int z = (j - 5); z <= (j + 5); ++z)
					{
						if((x < 0) || (z < 0) || (x >= FILE_MAP_SIZE) || (z >= FILE_MAP_SIZE))
							continue;
						D3DXVECTOR2 colorTilePower = D3DXVECTOR2(x - i, z - j);
						this->map_tile_mask[i][j].sand = 1.0f - D3DXVec2Length(&colorTilePower)/10.0f;
						this->map_tile_mask[i][j].grass = 1.0f - this->map_tile_mask[i][j].sand;
						this->map_decoration_mask[i][j].plantsFlag = PLANT_GRASS;
					}

			if(this->map_heightmap[i][j] >= 164.0f)
				for(int x = (i - 5); x <= (i + 5); ++x)
					for(int z = (j - 5); z <= (j + 5); ++z)
					{
						if((x < 0) || (z < 0) || (x >= FILE_MAP_SIZE) || (z >= FILE_MAP_SIZE))
							continue;
						D3DXVECTOR2 colorTilePower = D3DXVECTOR2(x - i, z - j);
						this->map_tile_mask[i][j].rock = 1.0f - D3DXVec2Length(&colorTilePower)/10.0f;
						this->map_tile_mask[i][j].grass = 1.0f - this->map_tile_mask[i][j].rock;
					}
		}

	/*for(int i = 1;i < FILE_MAP_SIZE;++i)
		for(int j = 1;j < FILE_MAP_SIZE;++j)
		{
			if(this->map_heightmap[i][j] >= 0)
			{
				this->map_tile_mask[i][j].grass = 0;
				this->map_tile_mask[i][j].sand = 1;
				this->map_tile_mask[i][j].rock = 0;
			}
			if(this->map_heightmap[i][j] > 132)
			{
				this->map_tile_mask[i][j].grass = 1;
				this->map_tile_mask[i][j].sand = 0;
				this->map_tile_mask[i][j].rock = 0;

				for( int i01 = i - 1; i01 <= (i+1); ++i01)
					for( int j01 = j - 1; j01 <= (j+1); ++j01)
						if(abs(this->map_heightmap[i01][j01] - this->map_heightmap[i][j]) > 8.0f) 
							this->map_tile_mask[i][j].rock = abs(this->map_heightmap[i01][j01] - this->map_heightmap[i][j])/16.0f; 
			}
			if(this->map_heightmap[i][j] >= 196)
			{
				this->map_tile_mask[i][j].grass = 0;
				this->map_tile_mask[i][j].sand = 0;
				this->map_tile_mask[i][j].rock = 1;
			}
		}*/
			
}

void gMapsService::Save()
{
	std::string map_file_name = "Content\\maps\\world.map";
	ofstream output_stream;
	output_stream.open("Content\\maps\\world_byte.map",ios::out);
	for(int i = 0;i < (FILE_MAP_SIZE + 1);++i){
		for(int j = 0;j < (FILE_MAP_SIZE + 1);++j){
			output_stream<<(float)this->map_heightmap[i][j];
			
			output_stream<<(BYTE)this->map_tile_mask[i][j].grass;
			output_stream<<(BYTE)this->map_tile_mask[i][j].sand;
			output_stream<<(BYTE)this->map_tile_mask[i][j].rock;
			
			//output_stream<<(BYTE)this->map_decoration_mask[i][j].r;
			//output_stream<<(BYTE)this->map_decoration_mask[i][j].g;
			//output_stream<<(BYTE)this->map_decoration_mask[i][j].b;
		}
	}
	output_stream.close();
}

D3DXVECTOR2 gMapsService::Normal(float position_x, float position_z)
{
	D3DXVECTOR2 resultNormal = D3DXVECTOR2(0.0f,0.0f);

	int pos1X = (int) (position_x + 20)/10;
	int pos1Z = (int) (position_z + 20)/10;

	int pos2X = (int) (position_x + 20)/10;
	int pos2Z = (int) (position_z - 20)/10;

	int pos3X = (int) (position_x - 20)/10;
	int pos3Z = (int) (position_z + 20)/10;

	int pos4X = (int) (position_x - 20)/10;
	int pos4Z = (int) (position_z - 20)/10;

	D3DXVECTOR3 vMain =  D3DXVECTOR3(position_x/10, this->map_heightmap[(int)position_x/10][(int)position_z/10],position_z/10);

	D3DXVECTOR3 v1 = vMain - D3DXVECTOR3(pos1X + 1, this->map_heightmap[pos1X + 1][pos1Z],pos1Z);
	D3DXVECTOR3 v2 = vMain - D3DXVECTOR3(pos1X, this->map_heightmap[pos1X][pos1Z + 1],pos1Z + 1);

	D3DXVECTOR3 v3 = D3DXVECTOR3(pos2X + 1, this->map_heightmap[pos2X + 1][pos2Z],pos2Z)  - vMain;
	D3DXVECTOR3 v4 = D3DXVECTOR3(pos2X, this->map_heightmap[pos2X][pos2Z + 1],pos2Z + 1)  - vMain;

	D3DXVECTOR3 v5 = D3DXVECTOR3(pos3X + 1, this->map_heightmap[pos3X + 1][pos3Z],pos3Z)  - vMain;
	D3DXVECTOR3 v6 = D3DXVECTOR3(pos3X, this->map_heightmap[pos3X][pos3Z + 1],pos3Z + 1)  - vMain;

	D3DXVECTOR3 v7 = D3DXVECTOR3(pos4X + 1, this->map_heightmap[pos4X + 1][pos4Z],pos4Z)  - vMain;
	D3DXVECTOR3 v8 = D3DXVECTOR3(pos4X, this->map_heightmap[pos4X][pos4Z + 1],pos4Z + 1)  - vMain;
	

	D3DXVECTOR3 normal1;
	D3DXVec3Cross(&normal1,&v1,&v2);
	D3DXVec3Normalize(&normal1,&normal1);

	D3DXVECTOR3 normal2;
	D3DXVec3Cross(&normal2,&v3,&v4);
	D3DXVec3Normalize(&normal2,&normal2);

	D3DXVECTOR3 normal3;
	D3DXVec3Cross(&normal3,&v5,&v6);
	D3DXVec3Normalize(&normal3,&normal3);

	D3DXVECTOR3 normal4;
	D3DXVec3Cross(&normal4,&v7,&v8);
	D3DXVec3Normalize(&normal4,&normal4);

	D3DXVECTOR3 normal = D3DXVECTOR3((normal1.x+normal2.x+normal3.x+normal4.x)/4.0f,(normal1.y+normal2.y+normal3.y+normal4.y)/4.0f,(normal1.z+normal2.z+normal3.z+normal4.z)/4.0f);
	
	D3DXVec3Normalize(&normal,&normal);

	//D3DXVECTOR3 mainV = D3DXVECTOR3((gCore::Camera()->LookAt.x - gCore::Camera()->Position.x),0.0f,(gCore::Camera()->LookAt.z - gCore::Camera()->Position.z));

	D3DXVECTOR3 v9 = D3DXVECTOR3(1.0f,0.0f,0.0f);
	D3DXVECTOR3 v10 = D3DXVECTOR3(0.0f,0.0f,1.0f);

	//D3DXVec3Normalize(&mainV,&mainV);

	resultNormal.x = 0;//acos(D3DXVec3Dot(&normal1,&v9)) - 1.57;
	resultNormal.y = 0;//acos(D3DXVec3Dot(&normal1,&v10)) - 1.57;

	return resultNormal;
}

float gMapsService::Height(float position_x,float position_z)
{
	position_x /= 10.0f;
	position_z /= 10.0f;

	int round_position_x = (int) position_x;
	int round_position_z = (int) position_z;

	float remain_position_x = position_x - round_position_x;
	float remain_position_z = position_z - round_position_z;

	if((round_position_x < 1) || (round_position_z < 1) || (round_position_x > (FILE_MAP_SIZE - 1)) || (round_position_z > (FILE_MAP_SIZE - 1)))
		 return 0.0f;
	
	float height_11 = this->map_heightmap[round_position_x][round_position_z];
	float height_12 = this->map_heightmap[round_position_x][round_position_z +1];
	float height_21 = this->map_heightmap[round_position_x + 1][round_position_z];
	float height_22 = this->map_heightmap[round_position_x + 1][round_position_z + 1];
    float main_height;

    if( remain_position_x > remain_position_z )
	{
		main_height = height_11 + (height_22 - height_21)*remain_position_z + (height_21 - height_11)*remain_position_x;
	}
	else
	{
		main_height = height_11 + (height_22 - height_12)*remain_position_x + (height_12 - height_11)*remain_position_z;
	}

	float height = (1 - remain_position_x) * ((1 - remain_position_z) * height_11 + remain_position_z * height_12) + remain_position_x * ((1 - remain_position_z) * height_21 + remain_position_z * height_22);
	if(height < 128.0f)
		return 128.0f;
	else
		return height;
}
