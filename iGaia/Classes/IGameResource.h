//
//  IGameResource.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IGameResource_h
#define iGaia_IGameResource_h

class IGameResource
{
protected:
    int m_iCount;
public:
    IGameResource(void);
    virtual ~IGameResource(void);
    virtual void Update(void) = 0;
    int Get_Count(void) { return m_iCount; }
    void Set_Count(int _iCount) { m_iCount = _iCount; }
};

#endif
