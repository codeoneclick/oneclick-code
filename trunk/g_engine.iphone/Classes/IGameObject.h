//
//  IGameObject.h
//  gEngine
//
//  Created by sergey.sergeev on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IGameObject_h
#define gEngine_IGameObject_h

#include "INode.h"
#include "IResource.h"
#include <vector>

class IGameObject
{
public:
    struct SNavigationIndex
    {
         int m_pIndex[2];
    };
protected:
    Vector3d m_vScale;
    Vector3d m_vPosition;
    Vector3d m_vRotation;
    SNavigationIndex m_tNavigationIndex;
public:
    IGameObject();
    virtual ~IGameObject();
    virtual void Load(std::vector<IResource::SResource> _lResource) = 0;
    virtual void Update(float _fTime) = 0;
    virtual bool IsPicker() = 0;   
    
    inline void Set_Position(Vector3d _vPosition) { m_vPosition = _vPosition; }
    inline Vector3d Get_Position() { return m_vPosition; }
    inline void Set_Rotation(Vector3d _vRotation) { m_vRotation = _vRotation; }
    inline Vector3d Get_Rotation() { return m_vRotation; }
    inline void Set_Scale(Vector3d _vScale) { m_vScale = _vScale; }
    inline Vector3d Get_Scale() { return m_vScale; }
    inline SNavigationIndex Get_NavigationIndex() { return m_tNavigationIndex; }
    inline void Set_NavigationIndex(SNavigationIndex _tNavigationIndex) { m_tNavigationIndex = _tNavigationIndex; }
};

#endif
