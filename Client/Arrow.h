#pragma once
#include "Bow.h"
class CArrow :
	public CBow
{
public:
	CArrow();
	virtual ~CArrow();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	virtual void Set_ImgDir(float _fAngle);
	virtual void MoveFrame();

	virtual bool& Alter_Missile() { return m_bMissile;	}
public:
	bool m_bMissile;
};

