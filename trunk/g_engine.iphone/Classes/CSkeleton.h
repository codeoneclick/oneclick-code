//
//  CSkeleton.h
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSkeleton_h
#define gEngine_CSkeleton_h
#include "CBone.h"


class CSkeleton
{
private:
	int			m_iNumBones;
	CBone*		m_pRootBone;
public:
	CSkeleton(int _iNumBones)
    : m_iNumBones(_iNumBones)
    , m_pRootBone(NULL)
	{}
    
    void AddBone( CBone* _pBone );
    void AnimateHierarhy();
    void SetupBindPose();
	
	inline int Get_NumBones() const { return m_iNumBones; }
	inline CBone* Get_BoneByID( int _iID )
	{
		if ( !m_pRootBone )
        {
			return NULL;
        }
		if ( m_pRootBone->Get_ID() == _iID )
        {
			return m_pRootBone;
        }
        
		return m_pRootBone->FindInChildrensByID( _iID );
	}
};


#endif
