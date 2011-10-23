#include "gModel3D.h"

#define EPS   0.001


gModel3D::gModel3D()
{
	this->cCamera = gCore::Camera();
	this->cLight  = gCore::Light();

	this->vb = NULL;
	this->ib = NULL;

	this->_TBNInfo = NULL;
}

void gModel3D::_CalculateTBN(unsigned int nVerteces,unsigned int nIndeces)
{
	if(this->_TBNInfo != NULL)
	{
		delete[] this->_TBNInfo;
		this->_TBNInfo = NULL;
	}

	this->_TBNInfo = new gTBNInfo[nVerteces];

	for( int i = 0; i < nIndeces; i += 3 )
	{
		D3DXVECTOR3 p1 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+0]].position;
		D3DXVECTOR3 p2 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+1]].position;
		D3DXVECTOR3 p3 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+2]].position;

		D3DXVECTOR3 v1 = p2 - p1;
	    D3DXVECTOR3 v2 = p3 - p1;
		D3DXVECTOR3 normal;
		D3DXVec3Cross(&normal,&v1,&v2);
		D3DXVec3Normalize(&normal,&normal);

		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._normal = normal;
		this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._normal = normal;
		this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._normal = normal;
		
		D3DXVECTOR3 tangent;

		D3DXVec3Cross(&tangent,&normal,&v2);
		D3DXVec3Normalize(&tangent,&tangent);

		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent = tangent;
		this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._tangent = tangent;
		this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._tangent = tangent;

		D3DXVECTOR3 binormal;

		D3DXVec3Cross(&binormal,&tangent,&normal);
		D3DXVec3Normalize(&binormal,&binormal);

		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal = binormal;
		this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._binormal = binormal;
		this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._binormal = binormal;


		/*gSimpleVertexFormat _v0 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+0]];
		gSimpleVertexFormat _v1 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+1]];
		gSimpleVertexFormat _v2 = this->_simpleVertexBuffer[this->_simpleIndexBuffer[i+2]];


		D3DXVECTOR3	e0 ( _v1.position.x - _v0.position.x, _v1.textureCoordinates.x - _v0.textureCoordinates.x, _v1.textureCoordinates.y - _v0.textureCoordinates.y );
		D3DXVECTOR3	e1 ( _v2.position.x - _v0.position.x, _v2.textureCoordinates.x - _v0.textureCoordinates.x, _v2.textureCoordinates.y - _v0.textureCoordinates.y );
		D3DXVECTOR3	cp;
		D3DXVec3Cross(&cp,&e0,&e1);

	if ( fabs ( cp.x ) > EPS )
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.x = -cp.y / cp.x;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.x = -cp.z / cp.x;
	}
	else
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.x = 0;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.x = 0;
	}

	e0.x = _v1.position.y - _v0.position.y;
	e1.x = _v2.position.y - _v0.position.y;
	D3DXVec3Cross(&cp,&e0,&e1);
	//cp   = e0 ^ e1;

	if ( fabs ( cp.x ) > EPS )
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.y = -cp.y / cp.x;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.y = -cp.z / cp.x;
	}
	else
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.y = 0;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.y = 0;
	}

	e0.x = _v1.position.z - _v0.position.z;
	e1.x = _v2.position.z - _v0.position.z;
	//cp   = e0 ^ e1;
	D3DXVec3Cross(&cp,&e0,&e1);

	if ( fabs ( cp.x ) > EPS )
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.z = -cp.y / cp.x;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.z = -cp.z / cp.x;
	}
	else
	{
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent.z = 0;
		this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal.z = 0;
	}

	
	this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._binormal = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._binormal = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal;


	this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._tangent = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._tangent = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent;

	D3DXVec3Cross(&this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._normal,&this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._tangent,&this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._binormal);

	this->_TBNInfo[this->_simpleIndexBuffer[i+1]]._normal = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+2]]._normal = 
	this->_TBNInfo[this->_simpleIndexBuffer[i+0]]._normal;*/

	}
}
