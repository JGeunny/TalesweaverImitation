#pragma once
#include "Skill.h"
class CWhirlwind :
	public CSkill
{
public:
	CWhirlwind();
	virtual ~CWhirlwind();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	float		m_fAngle;	
};

