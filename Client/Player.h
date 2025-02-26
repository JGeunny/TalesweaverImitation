#pragma once
#include "Unit.h"

class CPlayer :
	public CUnit
{
public:
	CPlayer();
	virtual ~CPlayer();	

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void Control();
	virtual void LateInit();

	virtual void IsOffset();
	
	virtual void SceneChange();

protected:
	INFO_DRAW	m_tDraw_Target;

	//슬라이딩 스피드
	DWORD		m_dwSlidingTime;
	int			m_iSliding_Count;
	float		m_fSpeedBuf;
	float		m_fSliding;

	int			m_iBaseAttack;
	bool		m_bWhirlWind;
	bool		m_bArrow;
};

