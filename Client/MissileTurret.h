#pragma once
#include "Turret.h"
class CMissileTurret :
	public CTurret
{
public:
	CMissileTurret();
	virtual ~CMissileTurret();

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
};

