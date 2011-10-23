/*#ifndef _CMD2Model_H
#define _CMD2Model_H

const int MAX_TRIANGLES = 4096;
const int MAX_VERTS		= 2048;
const int MAX_FRAMES	= 512;
const int MAX_MD2SKINS	= 32;
const int MAX_SKINNAME	= 64;


struct md2_animation{
	int start,end;
	std::string name;
	float current;
	float add;
};

typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH, 
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} animationType;


struct md2Animation
{
	int		first_frame;			
	int		last_frame;			
	int		fps;					
};

struct index_list{
	int a, b, c;
	float a_s, a_t,b_s, b_t,c_s, c_t;
};

struct vertex_list{
	float x, y, z;
};

struct frame_list{
	vertex_list *vertex;
};

struct dstvert_t{
	short s;
	short t;
};

struct gDynamicVertex{
	short index_xyz[3];
	short index_st[3];
};

class gDynamic{
private :

	struct dtrivertx_t
	{
		byte v[3];
		byte lightnormalindex;
	};

	//Identify frames
	struct daliasframe_t
	{
		float scale[3];
		float translate[3];
		char name[16];
		dtrivertx_t verts[1];
	};

	struct SMD2Header
	{
	  int ident;
	  int version;

	  int skinwidth;			//Width and height of frame
	  int skinheight;			//Should be dividable by 8

	  int framesize;

	  int num_skins;			//Number of skintextures
	  int num_xyz;			
	  int num_st;
	  int num_tris;				//Count of triangles
	  int num_glcmds;
	  int num_frames;			//Count of fames

	//Some file offsets
	  int ofs_skins;
	  int ofs_st;
	  int ofs_tris;
	  int ofs_frames;
	  int ofs_glcmds; 
	  int ofs_end;

	} ;

	typedef struct
	{
			D3DXVECTOR3          v;
			int   lightnormalindex;
	} trivert_t;

	typedef struct
	{
			D3DXVECTOR3          mins, maxs;
			char            name[16];
			trivert_t       v[MAX_VERTS];
	} frame_t;

	// The modellvertex for D3D
	struct MODELVERTEX 
	{
	  D3DXVECTOR3   m_vecPos;
	  D3DXVECTOR3   normal;
	  D3DXVECTOR2   m_vecTex;
	} ;
	#define D3DFVF_MODELVERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

	struct SMesh
	{
		std::vector <MODELVERTEX> vertex;
	};

	int animationSpeed;
	int currentFrame;
	int startFrame;
	int endFrame;
    DWORD timerLastTime;

	index_list* m_index_list;
	frame_list* m_frame_list;
	long m_frames,   m_vertices, m_triangles;
	//Save vertice
	SMesh			 m_data [MAX_FRAMES];
	//Called by Load
	

	ID3DXEffect* Effect;
	IDirect3DTexture9* Texture;

	static md2Animation	animlist[21];

	animationType currentAnimation;

public:
	//Look @comments for SAnimation
	//Must be filled externally (see GameInit in main.cpp)
	std::vector <md2_animation> m_anim;

	int				 Init();

	gDynamic();
	~gDynamic();

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	
	//Loads the file 
	BOOL				Load (char* );
	//Frees memory
	void				Destroy ();
	//Draws frame nr frame :-)
	BOOL				Render ();
	void  Update(gCamera *camera);
	//Plays the animation by name and "advances" it but only
	//if advance==TRUE
	//if advance==FALSE the animation stops !
	BOOL				Render (char* name, BOOL advance=TRUE);

	void SetAnimationSpeed(int value);

	void SetAnimation(animationType value);

	void PlayAnimation();

	inline int			GetFrameCount()		{ return    m_frames;	}
	inline int			GetVertexCount()	{ return	m_vertices; }
	inline int			GetTriangleCount()	{ return	m_triangles;} 
};

#endif

// Constructor
gDynamic::gDynamic () 
{
	this->animationSpeed = 60;
	this->currentFrame = 0;
	this->startFrame = 0;
	this->endFrame = 0;
    this->timerLastTime = 0;
	m_index_list = NULL;
	m_frame_list = NULL;
	m_frames = m_vertices = m_triangles = 0;
	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);

	this->currentAnimation = STAND;
}

// Destructor
gDynamic::~gDynamic () 
{
	
	if( m_frame_list != NULL ) 
	{
		for( int i = 0; i < m_frames; i++ )
			delete [] m_frame_list[i].vertex;
		delete [] m_frame_list;
	}
	
	if( m_index_list)
		delete [] m_index_list;
}

md2Animation  gDynamic::animlist[ 21 ] = 
{
	// first, last, fps

	{   0,  39,  9 },	// STAND
	{  40,  45, 10 },	// RUN
	{  46,  53, 10 },	// ATTACK
	{  54,  57,  7 },	// PAIN_A
	{  58,  61,  7 },	// PAIN_B
	{  62,  65,  7 },	// PAIN_C
	{  66,  71,  7 },	// JUMP
	{  72,  83,  7 },	// FLIP
	{  84,  94,  7 },	// SALUTE
	{  95, 111, 10 },	// FALLBACK
	{ 112, 122,  7 },	// WAVE
	{ 123, 134,  6 },	// POINT
	{ 135, 153, 10 },	// CROUCH_STAND
	{ 154, 159,  7 },	// CROUCH_WALK
	{ 160, 168, 10 },	// CROUCH_ATTACK
	{ 196, 172,  7 },	// CROUCH_PAIN
	{ 173, 177,  5 },	// CROUCH_DEATH
	{ 178, 183,  7 },	// DEATH_FALLBACK
	{ 184, 189,  7 },	// DEATH_FALLFORWARD
	{ 190, 197,  7 },	// DEATH_FALLBACKSLOW
	{ 198, 198,  5 },	// BOOM
};


void gDynamic::PlayAnimation()
{
    DWORD timer_current_time = GetTickCount();	
    if((timer_current_time - this->timerLastTime)  > this->animationSpeed){
	   this->timerLastTime = timer_current_time;
	   this->currentFrame++;
    }

	if(this->currentFrame > this->endFrame)
	   this->currentFrame = this->startFrame;
}

void gDynamic::SetAnimation(animationType value)
{
	if(this->currentAnimation == value) return;
	this->currentAnimation = value;
	this->startFrame = animlist[value].first_frame;
	this->endFrame = animlist[value].last_frame;
	this->currentFrame = animlist[value].first_frame;
	this->timerLastTime = 0;
}


void gDynamic::Destroy (void) 
{
	if( m_frame_list != NULL ) {
		
		for( int i = 0; i < m_frames; i++ )
			delete [] m_frame_list[i].vertex;
		
		delete [] m_frame_list;
		m_frame_list = NULL;
	}
	
	if( m_index_list != NULL ) {
		delete [] m_index_list;
		m_index_list = NULL;
	}
}

int gDynamic::Load( char *filename ) 
{
	int i = 0;
	FILE		*modelfile = NULL;
	char		g_skins[MAX_MD2SKINS][64];
	dstvert_t	base_st[MAX_VERTS];
	byte		buffer[MAX_VERTS*4+128];
	SMD2Header	modelheader;
	
	gDynamicVertex     tri;
	daliasframe_t	*out;
	
	if( (modelfile = fopen (filename, "rb")) == NULL )
		return 0;
	
	// Read the header
	fread( &modelheader, 1, sizeof(modelheader), modelfile );
	
	modelheader.framesize = (int)&((daliasframe_t *)0)->verts[modelheader.num_xyz];
	
	//copy some data
	m_frames     = modelheader.num_frames;
	m_vertices   = modelheader.num_xyz;
	m_triangles  = modelheader.num_tris;
	
	m_index_list = new index_list [modelheader.num_tris];
	m_frame_list = new frame_list [modelheader.num_frames];
	
	for( int i = 0; i < modelheader.num_frames; i++)
		m_frame_list[i].vertex = new vertex_list [modelheader.num_xyz];
	
	//read skin information
	fread( g_skins, 1, modelheader.num_skins * MAX_SKINNAME, modelfile );
	
	// read indice of the polygon meshes
	fread( base_st, 1, modelheader.num_st * sizeof(base_st[0]), modelfile );
	
	int	max_tex_u = 0, max_tex_v = 0;

	for( i = 0; i < modelheader.num_tris; i++ ) 
	{
		// read vertice
		fread( &tri, 1, sizeof(gDynamicVertex), modelfile);
		
		(m_index_list)[i].a = tri.index_xyz[2];
		(m_index_list)[i].b = tri.index_xyz[1];
		(m_index_list)[i].c = tri.index_xyz[0];
	
		// read t&u
		(m_index_list)[i].a_s = base_st[tri.index_st[2]].s;
		(m_index_list)[i].a_t = base_st[tri.index_st[2]].t;
		(m_index_list)[i].b_s = base_st[tri.index_st[1]].s;
		(m_index_list)[i].b_t = base_st[tri.index_st[1]].t;
		(m_index_list)[i].c_s = base_st[tri.index_st[0]].s;
		(m_index_list)[i].c_t = base_st[tri.index_st[0]].t;
		max_tex_u = max( max_tex_u, base_st[tri.index_st[0]].s );
		max_tex_u = max( max_tex_u, base_st[tri.index_st[1]].s );
		max_tex_u = max( max_tex_u, base_st[tri.index_st[2]].s );
		max_tex_v = max( max_tex_v, base_st[tri.index_st[0]].t );
		max_tex_v = max( max_tex_v, base_st[tri.index_st[1]].t );
		max_tex_v = max( max_tex_v, base_st[tri.index_st[2]].t );
	}

	//convert t&u to be valid
	for ( i = 0; i < modelheader.num_tris; i++ ) 
	{
		m_index_list[ i ].a_s /= max_tex_u;
		m_index_list[ i ].b_s /= max_tex_u;
		m_index_list[ i ].c_s /= max_tex_u;
		m_index_list[ i ].a_t /= max_tex_v;
		m_index_list[ i ].b_t /= max_tex_v;
		m_index_list[ i ].c_t /= max_tex_v;
	}

	//Devicem_toolz.FTrace ("Animation-names for : ");
	//g_D3D.m_toolz.FTrace (filename);
	//g_D3D.m_toolz.FTrace ("\n\n");

	// Read vertexdata from all animations
	for( i = 0; i < modelheader.num_frames; i++ ) 
	{
		out = (daliasframe_t *)buffer;
		fread( out, 1, modelheader.framesize, modelfile );

		//if (out->name)
		//	g_D3D.m_toolz.FTrace (out->name);
		//g_D3D.m_toolz.FTrace ("\n");
		
		for( int j = 0; j < modelheader.num_xyz; j++ ) 
		{
			 m_frame_list[i].vertex[j].x = out->verts[j].v[0] * out->scale[0] + out->translate[0];
			 m_frame_list[i].vertex[j].y = out->verts[j].v[1] * out->scale[1] + out->translate[1];
			 m_frame_list[i].vertex[j].z = out->verts[j].v[2] * out->scale[2] + out->translate[2];
		}
	}
	
	fclose (modelfile);
	return Init();
}

int gDynamic::Init() 
{
	 D3DXCreateEffectFromFile(gDevice::device, "Content\\shaders\\GUI.fx", NULL, NULL, 0, NULL, &this->Effect, NULL);
	 D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\Marine.jpg", &Texture);
	 this->Effect->SetTexture("texture_color",this->Texture);
	 // For each animation we use one SMesh
	for ( int i = 0; i < GetFrameCount(); i++ )
	{
		MODELVERTEX pVertex;
		
		D3DXCOLOR	LightColor(1.0f, 1.0f, 1.0f, 1.0f );
		for( int j = 0; j < GetTriangleCount(); j++) 
		{
			pVertex.m_vecPos.x = m_frame_list[i].vertex[m_index_list[j].a].x;
			pVertex.m_vecPos.y = m_frame_list[i].vertex[m_index_list[j].a].z;
			pVertex.m_vecPos.z = m_frame_list[i].vertex[m_index_list[j].a].y;
			pVertex.m_vecTex.x = m_index_list[j].a_s;
			pVertex.m_vecTex.y = m_index_list[j].a_t;
			m_data[i].vertex.push_back (pVertex);
			
			pVertex.m_vecPos.x = m_frame_list[i].vertex[m_index_list[j].b].x;
			pVertex.m_vecPos.y = m_frame_list[i].vertex[m_index_list[j].b].z;
			pVertex.m_vecPos.z = m_frame_list[i].vertex[m_index_list[j].b].y;
			pVertex.m_vecTex.x = m_index_list[j].b_s;
			pVertex.m_vecTex.y = m_index_list[j].b_t;
			m_data[i].vertex.push_back (pVertex);
			
			pVertex.m_vecPos.x = m_frame_list[i].vertex[m_index_list[j].c].x;
			pVertex.m_vecPos.y = m_frame_list[i].vertex[m_index_list[j].c].z;
			pVertex.m_vecPos.z = m_frame_list[i].vertex[m_index_list[j].c].y;
			pVertex.m_vecTex.x = m_index_list[j].c_s;
			pVertex.m_vecTex.y = m_index_list[j].c_t;
			m_data[i].vertex.push_back (pVertex);		
		}
	}
	return 1;
}

void gDynamic::Update(gCamera *camera){
	
	D3DXMATRIX world_view_projection_matrix;
	D3DXMatrixIdentity(&world_view_projection_matrix);

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scaling_matrix;

	this->Rotation.y = gCore::Camera()->Rotation.y + 1.57f;

	D3DXMatrixScaling(&scaling_matrix,0.5f,0.5f,0.5f);
	D3DXMatrixTranslation(&translation_matrix, this->Position.x,this->Position.y + 12.0f, this->Position.z);
	D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	rotation_matrix = rotation_x_matrix*rotation_z_matrix*rotation_y_matrix;
	world_view_projection_matrix = scaling_matrix*rotation_matrix*translation_matrix;

	world_view_projection_matrix *= gCore::Camera()->view*gCore::Camera()->projection;
	Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
}

//Draws me !
BOOL gDynamic::Render() 
{	
	//return false;

	if( this->currentFrame >= GetFrameCount()-1 )
		return 0;
	
	gDevice::device->SetFVF(D3DFVF_MODELVERTEX);
	//Device->SetVertexShader(D3DFVF_MODELVERTEX);
	Effect->Begin(NULL,NULL);
    Effect->BeginPass(NULL);
	gDevice::device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, GetTriangleCount (),(BYTE**)&m_data[this->currentFrame].vertex[0],sizeof(MODELVERTEX));
	Effect->EndPass();
    Effect->End();
	return true;//(SUCCEEDED());  //Größe Vertex
}

BOOL gDynamic::Render(char* name  ,BOOL b) 
{	
	return false;
	int play=-1;
	int l = 0;

	//Loop through all animation names
	for (l=0;l<m_anim.size();l++)
	{
		//found it ???
		if (strcmp (m_anim[l].name.c_str(), name)==0)
		{
			if (b)
				m_anim[l].current += m_anim[l].add;

			//restart animation
			if (m_anim[l].current >= m_anim[l].end)
				m_anim[l].current = m_anim[l].start;

			play=l;

			break;
		}
	}
	
	
	//DDevice->SetVertexShader (D3DFVF_MODELVERTEX);

	if (play==-1) return FALSE;
	if (play>=GetFrameCount()) return FALSE;

	gDevice::device->SetFVF(D3DFVF_MODELVERTEX);
	//Device->SetVertexShader(D3DFVF_MODELVERTEX);
	Effect->Begin(NULL,NULL);
    Effect->BeginPass(NULL);
	gDevice::device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, GetTriangleCount (),(BYTE**)&m_data[int(m_anim[l].current)].vertex[0],sizeof(MODELVERTEX));
	Effect->EndPass();
    Effect->End();

	return true;

	//return (SUCCEEDED(Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, //Typ	
											//	GetTriangleCount (),		  //Anzahl
												//(BYTE**)&m_data[int(m_anim[l].current)].vertex[0],		  //Pointer auf Daten
												//sizeof(MODELVERTEX))));  //Größe Vertex
}
*/