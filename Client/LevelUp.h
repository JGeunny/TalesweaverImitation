#pragma once
#include "Obj.h"
class CLevelUp :
	public CObj
{
public:
	CLevelUp();
	virtual ~CLevelUp();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	float	m_fDist;
};

