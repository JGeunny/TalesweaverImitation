#pragma once
#include "Obj.h"
class CBossInfo :
	public CObj
{
public:
	CBossInfo();
	virtual ~CBossInfo();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();
};

