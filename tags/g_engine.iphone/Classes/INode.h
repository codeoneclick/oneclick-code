//
//  INode.h
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_INode_h
#define gEngine_INode_h

#include "CMatrix.h"
#include "CShader.h"
#include "CVertexBuffer.h"
#include "CCamera.h"
#include "CResource.h"
#include <Box2D/Box2D.h>
#include <vector>

class INode
{
public:
    enum E_NODE { E_SHAPE = 0, E_SPRITE, E_MOVIECLIP, E_SHAPE_BOX2D, E_SPRITE_BOX2D, E_MOVIECLIP_BOX2D };
    struct SResourceParam
    {
        std::string m_sName;
        std::string m_sTexture;
        std::string m_sShader;
        std::string m_sSequence;
        Vector4d    m_vColor;
        Vector2d    m_vSize;
        Vector3d    m_vPosition;
        E_NODE      m_eNode;
    };
    
protected:
    Matrix4x4 m_mScale;
    Matrix4x4 m_mRotation;
    Matrix4x4 m_mTranslation;
    Matrix4x4 m_mWorld;
    
    Matrix4x4* m_mProjection;
    Matrix4x4* m_mView;
    
    CShader*        m_pShader;
    CTexture*       m_pTexture;
    CVertexBuffer*  m_pVb;
    static GLubyte* m_pIb;
    
    b2BodyDef      m_pBodyDef;
    b2Body*        m_pBody;
    
    Vector2d     m_vScale;
    Vector3d     m_vPosition;
    float        m_fRotation;
    Vector2d     m_vSize;
    
    INode*       m_pParent;
    std::vector<INode*> m_lChilds;
public:
    INode();
    virtual ~INode();
    virtual void Load(SResourceParam &_param);
    virtual void Update(float _fTime);
    virtual void Render();
    inline CVertexBuffer* Get_VB() { return m_pVb; }
    inline GLubyte* Get_IB() { return m_pIb; }
    void Set_Color(Vector4d& _vColor);
    Vector3d Get_Position() { return m_vPosition; }
    virtual void Set_Position(Vector3d &_vPosition) { m_vPosition = _vPosition; }
    float Get_Rotation() { return m_fRotation; }
    virtual void Set_Rotation(float _fRotation) { m_fRotation = _fRotation; }
    Vector2d Get_Scale() { return m_vScale; }
    virtual void Set_Scale(Vector2d &_vScale) { m_vScale = _vScale; }
    virtual Vector2d Get_Size() { return m_vSize; }
    virtual void Set_Parent(INode* _pNode) { m_pParent = _pNode; }
    virtual INode* Get_Parent() { return m_pParent; }
    virtual void AddChild(INode* _pNode);
    virtual INode* GetChildAt(unsigned int _index);
    inline std::vector<INode*> Get_Childs() { return m_lChilds; }
    virtual void RemoveChild(INode* _pNode);
    virtual void RemoveChildAt(unsigned int _index);
    void RemoveChilds();
    inline Matrix4x4 Get_WorldMatrix() { return m_mWorld; }
    Vector3d Get_GlobalPosition();
};


#endif
