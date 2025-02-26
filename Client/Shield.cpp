#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}


CShield::~CShield()
{
}

void CShield::Initialize()
{
	CBullet::Initialize();
	m_tDraw.fAngle = 0;
}

int CShield::Update()
{
	int Event = CSkill::Update();
	if (Event == OBJ_DEAD) return Event;

	if (m_pMaster)
	{
		INFO_DRAW	tDrawTarget = m_pMaster->Get_Info();
		tDrawTarget.fSpeed = 100;
		tDrawTarget.fAngle = m_tDraw.fAngle;
		tDrawTarget.Fn_Move();
		m_tDraw.fx = tDrawTarget.fx;
		m_tDraw.fy = tDrawTarget.fy;
		m_tDraw.fAngle += 10;
		m_tDraw.fAngle = int(m_tDraw.fAngle) % 360;

	}
	else
	{
		return OBJ_DEAD;
	}

	return Event;
}

void CShield::LateUpdate()
{
}

void CShield::Render(HDC hDC)
{
	CBullet::Render(hDC);
}

void CShield::Release()
{
}

void CShield::LateInit()
{
}
