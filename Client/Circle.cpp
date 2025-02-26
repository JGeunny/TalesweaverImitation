#include "stdafx.h"
#include "Circle.h"

#include "ImgMgr.h"

#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"

#include "Slime.h"
#include "Hunter.h"
#include "Boss.h"


CCircle::CCircle()
	:m_eMonsterID(CCircle::END)
{
}


CCircle::~CCircle()
{
}

void CCircle::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Effect/Portal.bmp", L"Portal");
	CImgMgr::Get_Instance()->AddImage(L"Effect/Portal2.bmp", L"Portal2");

	m_tDraw.fcx = 150;
	m_tDraw.fcy = 200;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 0;
	m_iObjTimeCount[OBJ_TIMEID::RUN] = 5000;
	m_eMonsterID = CCircle::SLIME;
}

int CCircle::Update()
{
	CObj::MoveFrame();
	CObj::LiveTime();

	DWORD dwNowTime = GetTickCount();
	if (TEAM_1 == m_iTeam)
	{
		m_pFrameKey = L"Portal2";
	}
	else
	{
		m_pFrameKey = L"Portal";
	}

	if (m_dwObjTime[OBJ_TIMEID::RUN] == dwNowTime)
	{
		INFO_DRAW tDraw = m_tDraw;
		switch (m_eMonsterID)
		{
		case CCircle::SLIME:
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CSlime>::Create_Unit(m_iTeam, tDraw.fx, tDraw.fy, 0, L"슬라임", 0, 500));
			break;
		case CCircle::MONSTER:
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CMonster>::Create_Unit(m_iTeam, tDraw.fx, tDraw.fy, 0, L"몬스터"));
			break;
		case CCircle::HUNTER:
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CHunter>::Create_Unit(m_iTeam, tDraw.fx, tDraw.fy, 0, L"헌터"));
			break;
		case CCircle::END:
			break;
		default:
			break;
		}
	}
	return 0;
}

void CCircle::LateUpdate()
{

}

void CCircle::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 255, 255));
}

void CCircle::Release()
{
}


void CCircle::LateInit()
{
}

void CCircle::SceneChange()
{
}
