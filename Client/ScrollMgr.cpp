#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ImgMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)
bool CScrollMgr::m_bShakeIt = false;
bool CScrollMgr::m_bHorizontalScroll = false;
POINTFLOAT CScrollMgr::m_ptScroll = { 0, 0 };
CScrollMgr::CScrollMgr()
	: m_iMovement(0)
	, m_iSpeed(13)
{
	Initialize();
}

CScrollMgr::~CScrollMgr()
{
	Release();
}

void CScrollMgr::ScrollObj(list<CObj*>& rSrc)
{
	for (auto pObj : rSrc)
	{
		/*INFO_DRAW tData = pObj->Get_Info();
		tData.fx += m_ptScroll.x;
		tData.fy += m_ptScroll.y;
		pObj->Set_Info(tData);*/
	}
}

void CScrollMgr::ScrollLock()
{
	if (m_ptScroll.x > 0)
		m_ptScroll.x = 0;
	if (m_ptScroll.y > 0)
		m_ptScroll.y = 0;

	int iTileX = g_iTileX;
	int iTileY = g_iTileY;

	if (WINCX - TILECX * iTileX > m_ptScroll.x)
		m_ptScroll.x = (float)WINCX - (float)TILECX * iTileX;
	if (m_bHorizontalScroll)
	{
		if (WINCY - TILECY * iTileY + TILECY > m_ptScroll.y)
			m_ptScroll.y = (float)WINCY - (float)TILECY * iTileY + TILECY;

		if(false == m_bShakeIt)
			m_ptScroll.y = -30;
	}
	else
	{
		if (WINCY - TILECY * iTileY > m_ptScroll.y)
			m_ptScroll.y = (float)WINCY - (float)TILECY * iTileY;
	}

	/*if (WINCX - TILECX * TILEX > m_ptScroll.x)
		m_ptScroll.x = WINCX - TILECX * TILEX;
	if (WINCY - TILECY * TILEY > m_ptScroll.y)
		m_ptScroll.y = WINCY - TILECY * TILEY;*/
	// -1110, -1315
}

bool CScrollMgr::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Effect/comline.bmp", L"comline");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 0;
	m_tFrame.dwFrameTime = GetTickCount();

	m_dwShackItTime = GetTickCount();
	return true;
}

void CScrollMgr::LateUpdate()
{
	if (m_bShakeIt)
	{
		if (m_iMovement > 20)
			m_iSpeed = -1 * abs(m_iSpeed);
		if (m_iMovement < -20)
			m_iSpeed = abs(m_iSpeed);
		m_iMovement += m_iSpeed;
		m_ptScroll.y += m_iSpeed;
		MoveFrame();
	}
	if (m_dwShackItTime + 350 < GetTickCount())
	{
		m_bShakeIt = false;
		m_ptScroll.y -= m_iMovement;
		m_iMovement = 0;
	}
}

void CScrollMgr::Render(HDC hDC)
{
	if (m_bShakeIt)
	{
		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"comline");
		GdiTransparentBlt(hDC, 0, 0,
			WINCX, WINCY, hMemDC,
			0, 0,
			800, 600,
			RGB(0, 0, 0));
	}
}

void CScrollMgr::Release()
{
}

void CScrollMgr::DoShackIt()
{
	m_bShakeIt = true;
	m_dwShackItTime = GetTickCount();
}

void CScrollMgr::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}
