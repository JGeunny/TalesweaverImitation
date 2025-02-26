#pragma once
#include "Scene.h"
class CField :
	public CScene
{
public:
	CField();
	virtual ~CField();

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

