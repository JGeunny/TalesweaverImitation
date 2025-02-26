#pragma once
#include "Obj.h"

class CBeAttacked :
	public CObj
{
public:
	CBeAttacked();
	virtual ~CBeAttacked();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	virtual int& Alter_Attack() { return m_iAtt; }

public:
	int m_iAtt;
	int m_iNumCount;

	float m_fDist;
};

