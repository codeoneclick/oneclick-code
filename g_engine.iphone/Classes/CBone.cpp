//
//  CBone.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBone.h"

void CBone::LinkChildBone(CBone* _pBone )
{
    CBone* pOldChild = m_pChild;
    m_pChild = _pBone;
    m_pChild->m_pNext = pOldChild;
    m_pChild->m_pParent = this;
}

CBone* CBone::FindInChildrensByID( int _iID )
{
    if ( !m_pChild )
        return NULL;
    
    CBone* pChild = m_pChild;
    CBone* pFound = NULL;
    while ( pChild )
    {
        if ( pChild->Get_ID() == _iID )
            return pChild;
        
        pFound = pChild->FindInChildrensByID( _iID );
        if ( pFound )
            break;
        pChild = pChild->Get_Next();
    }
    
    return pFound;
}

void CBone::AnimateHierarhy( const Matrix4x4* _mParentTransform )
{
    if ( _mParentTransform )
        (*m_mTransform) = (*_mParentTransform) * (*m_mTransform);
    
    CBone* pChild = m_pChild;
    while ( pChild )
    {
        pChild->AnimateHierarhy( m_mTransform );
        pChild = pChild->Get_Next();
    }
    
    (*m_mTransform) = (*m_mTransform) * m_mBindPositionInvert;
}

void CBone::SetupBindPose()
{
    if ( m_mTransform )
    {
        Set_BindPositionInvert(Inverse((*m_mTransform)));
    }
    
    CBone* pChild = m_pChild;
    while ( pChild )
    {
        pChild->SetupBindPose();
        pChild = pChild->Get_Next();
    }
}
