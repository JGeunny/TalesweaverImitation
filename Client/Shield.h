#pragma once
#include "Obj.h"
class CShield :
	public CBullet
{
public:
	CShield();
	virtual ~CShield();

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

