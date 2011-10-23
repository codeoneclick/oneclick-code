#ifndef CBASESECOND_H
#define CBASESECOND_H

#include "CBase.h"

class CBaseSecond : public CBase
{
public :
	CBaseSecond();
	~CBaseSecond();

	virtual void onUpdate();
};

#endif