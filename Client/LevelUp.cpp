#include "stdafx.h"
#include "LevelUp.h"
#include "ImgMgr.h"
#include "SoundMgr.h"

CLevelUp::CLevelUp()
{
}


CLevelUp::~CLevelUp()
{
}

void CLevelUp::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"lvup.mp3", CSoundMgr::EFFECT);
	CImgMgr::Get_Instance()->AddImage(L"Effect/LvUp.bmp", L"LvUp");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);
	//m_iObjTimeCount[OBJ_TIMEID::LIVE] = 300;
	m_tDraw.fSpeed = 5;
	m_tDraw.fcx = 150;
	m_tDraw.fcy = 150;

	//Crash를 위한 애니메
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 29;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameTime = GetTickCount();
	m_fDist = 0;
}

int CLevelUp::Update()
{
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_bObjState[OBJ_STATEID::DEAD] = true;
	}
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	m_tDraw.fy -= 2;
	m_fDist += 2;
	return OBJ_NOEVENT;
}

void CLevelUp::LateUpdate()
{
	CObj::MoveFrame();
}

void CLevelUp::Render(HDC hDC)
{
	RECT tRect = m_tDraw.Get_Rect();
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fy += m_fDist;
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"LvUp");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		256 * m_tFrame.iFrameStart,
		0,
		256, 256,
		RGB(255, 0, 255));
}

void CLevelUp::Release()
{
}

void CLevelUp::LateInit()
{
}
