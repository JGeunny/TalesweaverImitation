#pragma once
#include "BeAttacked.h"
class CCriticalAttacked :
	public CBeAttacked
{
public:
	CCriticalAttacked();
	virtual ~CCriticalAttacked();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

};

