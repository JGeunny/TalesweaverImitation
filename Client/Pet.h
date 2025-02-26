#pragma once

#include "Unit.h"
class CPet :
	public CUnit
{
public:
	CPet();
	virtual ~CPet();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void Control();
	virtual void LateInit();

public:
	virtual void SceneChange();
};

