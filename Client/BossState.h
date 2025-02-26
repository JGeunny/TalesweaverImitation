#pragma once
#include "StatePattern.h"
class CBossState :
	public CStatePattern
{
public:
	CBossState(CObj* _pObj);
	virtual ~CBossState();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
};

