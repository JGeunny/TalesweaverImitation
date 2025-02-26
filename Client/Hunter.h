#pragma once
#include "Monster.h"
class CHunter :
	public CMonster
{
public:
	CHunter();
	virtual ~CHunter();

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

