#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	virtual ~CTitle();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	bool		m_bLateInit;
	INFO_DRAW	m_tDraw;
};

