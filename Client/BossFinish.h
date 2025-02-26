#pragma once
#include "Scene.h"
class CBossFinish :
	public CScene
{
public:
	CBossFinish();
	virtual ~CBossFinish();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	virtual void CatchUnitInField();
public:
	DWORD m_dwBackGroundX;

protected:
	int	m_iMissionState;	// 0 초기값, 1 미션 클리어 2미션 페일
	INFO_DRAW m_tDrawGround;
};

