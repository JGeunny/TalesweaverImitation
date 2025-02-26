#pragma once
#include "Scene.h"
class CDun1 :
	public CScene
{
public:
	CDun1();
	virtual ~CDun1();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	int	m_iMissionState;	// 0 초기값, 1 미션 클리어 2미션 페일
};


