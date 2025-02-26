#pragma once
#include "Skill.h"

//총을 쏘는 스킬(원거리 공격 기본형)
class CBullet :
	public CSkill
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

protected:
};

