#pragma once
#include "Obj.h"
class CScore :
	public CObj
{
public:
	CScore();
	virtual ~CScore();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	int m_iScore;
	int m_iNumCount;

	float m_fDist;
};

