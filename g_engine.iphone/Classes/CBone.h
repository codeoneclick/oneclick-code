//
//  CBone.h
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBone_h
#define gEngine_CBone_h

#include "stdlib.h"
#include <string>
#include "CVector.h"
#include "CMatrix.h"

class CBone
{
private:
	std::string		m_sName;
	int				m_iID;
	int				m_iParentID;
	CBone*			m_pParent;
	CBone*			m_pNext;
	CBone*			m_pChild;
	Matrix4x4*		m_mTransform;
	Matrix4x4		m_mBindPositionInvert;    
public:
	CBone( const std::string& _sName, int _iID, int _iParentID )
    : m_sName(_sName)
    , m_iID(_iID)
    , m_iParentID(_iParentID)
    , m_pParent(NULL)
    , m_pNext(NULL)
    , m_pChild(NULL)
    , m_mTransform(NULL)
	{}
    
	void LinkChildBone(CBone* _pBone );
	CBone* FindInChildrensByID( int _iID );
    void AnimateHierarhy( const Matrix4x4* _mParentTransform );
	void SetupBindPose();
    
	inline int Get_ID() const { return m_iID; }
	inline int Get_ParentID() const { return m_iParentID; }
	inline CBone* Get_Parent() const { return m_pParent; }
	inline CBone* Get_Next() const { return m_pNext; }
	inline CBone* Get_Child() const { return m_pChild; }
	inline void Set_BindPositionInvert( const Matrix4x4& _mValue ) { m_mBindPositionInvert = _mValue; }
	inline const Matrix4x4& Get_BindPositionInverted() const { return m_mBindPositionInvert; }
	inline void Set_Transform( Matrix4x4* _mTransform ) { m_mTransform = _mTransform; }
	inline Matrix4x4* Get_Transform() const { return m_mTransform; }
};

#endif
