#pragma once
#include "Unit.h"
class CNPC :
	public CUnit
{
public:
	CNPC();
	virtual ~CNPC();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void Control();
	virtual void LateInit();

private:
	bool m_bReady;
};