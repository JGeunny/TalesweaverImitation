#pragma once
#include "Obj.h"
class CPlayerStatus :
	public CObj
{
public:
	CPlayerStatus();
	virtual ~CPlayerStatus();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();
};

