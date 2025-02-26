#pragma once
#include "Skill.h"

//휘두르는 스킬(근접공격 기본형)
class CWield :
	public CSkill
{
public:
	CWield();
	virtual ~CWield();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	CRotatePos* m_pRotatePos;
	float		m_fAngle;
};

