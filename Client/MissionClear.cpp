#include "stdafx.h"
#include "MissionClear.h"

#include "ImgMgr.h"
#include "SoundMgr.h"

CMissionClear::CMissionClear()
	:m_bSizeUp(false)
	, m_bClearImage(true)
{
}

CMissionClear::~CMissionClear()
{
	if (m_bClearImage)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"Success.wav", CSoundMgr::EFFECT);
	}
	else
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"Failed.wav", CSoundMgr::EFFECT);
	}
}

void CMissionClear::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Effect/StageState.bmp", L"StageState");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);

	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 3000;

	//Crash를 위한 애니메
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMissionClear::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	if (m_tFrame.dwFrameTime + 50 < GetTickCount())
	{
		if (m_tDraw.fcx < 229 + 100 && false == m_bSizeUp)
		{
			m_tDraw.fcx += 2;
			++m_tDraw.fcy;
			m_bSizeUp = true;
		}
		else if (true == m_bSizeUp)
		{
			if (m_tDraw.fcx > 229 - 30)
			{
				m_tDraw.fcx -= 2;
				--m_tDraw.fcy;
			}
		}
		m_tFrame.dwFrameTime = GetTickCount();
	}

	//m_tDraw.fcy
	return OBJ_NOEVENT;
}

void CMissionClear::LateUpdate()
{
	CMissionClear::MoveFrame();
}

void CMissionClear::Render(HDC hDC)
{
	m_tDraw.fx = WINCX * 0.5;
	m_tDraw.fy = WINCY * 0.5;
	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"StageState");

	if (m_bClearImage)
	{
		m_tFrame.iFrameStart = 0;
	}
	else
	{
		m_tFrame.iFrameStart = 1;
	}
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
		229 * m_tFrame.iFrameStart, 0, 229, 49,
		RGB(255, 0, 255));

	//Rectangle(hDC, 100, 100, 500, 500);
}

void CMissionClear::Release()
{
}

void CMissionClear::LateInit()
{
	m_tDraw.fx = WINCX * 0.5;
	m_tDraw.fy = WINCY * 0.5;
	m_tDraw.fcx = 229;
	m_tDraw.fcy = 49;

}

void CMissionClear::MoveFrame()
{
	/*if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		++m_tFrame.iFrameScene;
		m_tFrame.iFrameStart = 0;
	}
	if (m_tFrame.iFrameScene > 4)
	{
		m_tFrame.iFrameScene = 0;
	}*/
}
