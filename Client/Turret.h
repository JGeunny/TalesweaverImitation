#pragma once
#include "Unit.h"
class CTurret :
	public CUnit
{
public:
	CTurret();
	virtual ~CTurret();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	bool m_bExplosion;
};

