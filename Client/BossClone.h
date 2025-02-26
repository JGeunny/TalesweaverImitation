#pragma once
#include "Skill.h"
class CBossClone :
	public CSkill
{
public:
	CBossClone();
	virtual ~CBossClone();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();
};

