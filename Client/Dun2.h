#pragma once
#include "Scene.h"
class CDun2 :
	public CScene
{
public:
	CDun2();
	virtual ~CDun2();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	int m_iMissionState;
};

