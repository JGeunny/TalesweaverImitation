#pragma once
#include "Skill.h"

//���� ��� ��ų(���Ÿ� ���� �⺻��)
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

