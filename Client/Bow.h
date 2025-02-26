#pragma once
#include "Skill.h"
class CBow :
	public CSkill
{
public:
	CBow();
	virtual ~CBow();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	virtual void Set_MultiShot(bool _bMultiShot)
	{
		m_bMultiShot = _bMultiShot;
	}

public:
	virtual void Set_ImgDir(float _fAngle);
	float m_fAngle;
	bool m_bMultiShot;
};

