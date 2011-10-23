#include "CIntersectController.h"
#include "../Game.h"

using namespace Enviroment;

CIntersectController::CIntersectController()
{

}

void CIntersectController::AddIntersectBlock(std::string _name, Enviroment::CIntersectController::SIntersectBlock *_block)
{
	m_intesectBlockList[_name] = _block;
}

CIntersectController::SIntersectResult* CIntersectController::GetIntersectResult(std::string _name)
{
	std::map<std::string,CIntersectController::SIntersectResult*>::iterator blockIterator = m_intesectResultList.find(_name);
	if(blockIterator != m_intesectResultList.end())
		return (*blockIterator).second;
	
	return NULL;
}

void CIntersectController::Update()
{
	if(m_intesectBlockList.begin() == m_intesectBlockList.end())
		return;

	D3DXVECTOR3 vRayDirection;
	D3DXVECTOR3 vRayPosition;
	D3DXVECTOR3 vCursorPosition;
	D3DXMATRIX  mWorld;
	D3DVIEWPORT9 viewport;	
	POINT pCursorPosition;
	GetCursorPos(&pCursorPosition);
	vCursorPosition = D3DXVECTOR3(pCursorPosition.x,pCursorPosition.y,0.0f);
	math::Matrix4x4 mtView = Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView;
	math::Matrix4x4 mtProjection = Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection;
	math::Vector3d vtCameraPosition = Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(vtCameraPosition.x,vtCameraPosition.y,vtCameraPosition.z);
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;
	memcpy(mView.m,mtView.m, 16 * sizeof(float));
	memcpy(mProjection.m,mtProjection.m, 16 * sizeof(float));
	D3DXMatrixIdentity(&mWorld);
	Core::CGlobal::GetDevice()->Ref()->GetViewport(&viewport);
	D3DXVec3Unproject(&vRayPosition,&vCursorPosition,&viewport,&mProjection,&mView,&mWorld);
	D3DXVec3Normalize(&vRayDirection,&(vRayPosition - vCameraPosition));

	float u, v, distance;
	float delta = -1.0f;
	D3DXVECTOR3 intersectPoint;
	int index = 0;
	CIntersectController::SIntersectBlock* currentIntersectBlock = (*m_intesectBlockList.begin()).second;

	m_intersectPoint = math::Vector3d(0.0f, 0.0f, 0.0f);
		
	while (index < currentIntersectBlock->nIndeces)
	{
		math::Vector3d vtPoint0 = currentIntersectBlock->vertexData[currentIntersectBlock->indexData[index++]];
		math::Vector3d vtPoint1 = currentIntersectBlock->vertexData[currentIntersectBlock->indexData[index++]];
		math::Vector3d vtPoint2 = currentIntersectBlock->vertexData[currentIntersectBlock->indexData[index++]];

		D3DXVECTOR3 vPoint0 = D3DXVECTOR3(vtPoint0.x, vtPoint0.y, vtPoint0.z);
		D3DXVECTOR3 vPoint1 = D3DXVECTOR3(vtPoint1.x, vtPoint1.y, vtPoint1.z);
		D3DXVECTOR3 vPoint2 = D3DXVECTOR3(vtPoint2.x, vtPoint2.y, vtPoint2.z);

		//D3DXVECTOR3 vPoint0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 vPoint1 = D3DXVECTOR3(256.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 vPoint2 = D3DXVECTOR3(0.0f, 0.0f, 256.0f);

		if (D3DXIntersectTri(&vPoint0, &vPoint1, &vPoint2, &vRayPosition, &vRayDirection, &u, &v, &distance))
		{
			if (delta == -1 || distance < delta )
			{
				delta = distance;
				intersectPoint = vPoint0 + u * (vPoint1 - vPoint0) + v * (vPoint2 - vPoint0);
				m_intersectPoint = math::Vector3d(intersectPoint.x, intersectPoint.y, intersectPoint.z);
			}
		}
	}
	
}

