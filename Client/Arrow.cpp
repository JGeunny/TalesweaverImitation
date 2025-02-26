#include "stdafx.h"
#include "Arrow.h"
#include "ImgMgr.h"

CArrow::CArrow()
	:m_bMissile(false)
{
}


CArrow::~CArrow()
{
}

void CArrow::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Skill/Missile.bmp", L"Missile");
	CBow::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 1500;
	if (m_bMissile)
	{
		m_tDraw.fcx = 60.f;
		m_tDraw.fcy = 60.f;
		m_tDraw.fSpeed = 15;
	}
	else
	{
		m_tDraw.fcx = 96.f;
		m_tDraw.fcy = 90.7f;
		m_tDraw.fSpeed = 15;
	}

	m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();
	m_dwObjTime[OBJ_TIMEID::RUN] = GetTickCount();
}

int CArrow::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	if (m_pMaster == nullptr)
		return OBJ_DEAD;

	CObj::LateInit();
	CObj::LiveTime();

	DWORD dwNowTime = GetTickCount();
	
	if (m_dwObjTime[OBJ_TIMEID::SKILL] + 500 < dwNowTime)
	{
		if (m_dwObjTime[OBJ_TIMEID::RUN] + 1000 > dwNowTime)
		{
			if (m_pTarget)
			{
				if (m_pTarget->Get_Team() == m_iTeam)
				{
					Set_Target(nullptr);
					return OBJ_NOEVENT;
				}
				INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
				m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
			}
		}
		
	}
	m_tDraw.Fn_Move();

	return OBJ_NOEVENT;
}

void CArrow::LateUpdate()
{
	if (m_bMissile)
	{
		CArrow::MoveFrame();
		CArrow::Set_ImgDir(m_tDraw.fAngle);
	}
	else
	{
		CBow::LateUpdate();
	}
}

void CArrow::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	if (m_bMissile)
	{
		tDraw.fcx = 60.f;
		tDraw.fcy = 60.f;
		RECT tRect = tDraw.Get_Rect();
		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Missile");
		GdiTransparentBlt(hDC, tRect.left, tRect.top,
			(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
			(int)tDraw.fcx * m_tFrame.iFrameStart,
			0,
			(int)tDraw.fcx, (int)tDraw.fcy,
			RGB(255, 0, 255));
	}
	else
	{
		tDraw.fcx = 96.f;
		tDraw.fcy = 90.7f;
		RECT tRect = tDraw.Get_Rect();
		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
		GdiTransparentBlt(hDC, tRect.left, tRect.top,
			(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
			(int)tDraw.fcx * 4,
			(int)tDraw.fcy * m_tFrame.iFrameScene,
			(int)tDraw.fcx, (int)tDraw.fcy,
			RGB(0, 255, 255));
	}	
}

void CArrow::Release()
{
}

void CArrow::LateInit()
{
}

void CArrow::Set_ImgDir(float _fAngle)
{
	int iAngle = int(m_tDraw.fAngle + 0) % 360;
	if (iAngle < 0)
		iAngle = 360 + iAngle;
	//18
	int iDir = iAngle / 5.625;

	m_tFrame.iFrameStart = iDir;
	m_tFrame.iFrameEnd = iDir + 1;	
}

void CArrow::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd - 1;
}
