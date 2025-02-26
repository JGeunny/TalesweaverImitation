#pragma once
#include "Unit.h"

class CMonster :
	public CUnit
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void Control();
	virtual void LateInit();

public:
	void SceneChange();

protected:
};

