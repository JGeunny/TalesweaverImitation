#pragma once
#include "Skill.h"
class CBomb :
	public CSkill
{
public:
	CBomb();
	virtual ~CBomb();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	float m_fAngle;
};

