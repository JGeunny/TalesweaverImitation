#pragma once
#include "Unit.h"
class CTurretB :
	public CUnit
{
public:
	CTurretB();
	virtual ~CTurretB();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void MoveFrame();
	int m_iFrameDir;
	float m_fAngle;

	bool m_bExplosion;
};

