#pragma once
#include "Turret.h"
class CGrenadeTurret :
	public CTurret
{
public:
	CGrenadeTurret();
	virtual ~CGrenadeTurret();


public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
};

