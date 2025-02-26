#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"

#include "ImgMgr.h"

CMouse::CMouse()
	:m_iDrawID(0), m_iNextMaxTime(0)
	, m_iNextLogo(0)
	, m_bAttack(false)
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tDraw.fcx = 32.f;
	m_tDraw.fcy = 31.f;
	ShowCursor(FALSE);

	m_dwNextTime = GetTickCount();
	m_iNextMaxTime = 40;
}

int CMouse::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	POINTFLOAT ptScroll = CScrollMgr::Alter_Scroll();
	m_tDraw.fx = float(pt.x) - ptScroll.x;
	m_tDraw.fy = float(pt.y) - ptScroll.y;

	return 0;
}

void CMouse::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
		m_iDrawID = 1;
	else 
		m_iDrawID = 0;

}

void CMouse::Render(HDC hDC)
{
	RECT rt = m_tDraw.Get_Rect();
	
	if (m_bAttack)
	{
		HDC MemDC = CImgMgr::Get_Instance()->GetImgDC(L"Mouse_Attack");
		GdiTransparentBlt(hDC,
			rt.left + (int)m_tDraw.fcx * 0.5, rt.top + (int)m_tDraw.fcy * 0.5,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			MemDC,
			(int)m_tDraw.fcx * m_iNextLogo, 0,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			RGB(0, 0, 0));
	}
	else
	{
		HDC MemDC = CImgMgr::Get_Instance()->GetImgDC(L"Mouse");
		GdiTransparentBlt(hDC,
			rt.left + (int)m_tDraw.fcx * 0.5, rt.top + (int)m_tDraw.fcy * 0.5,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			MemDC,
			(int)m_tDraw.fcx * m_iNextLogo, (int)m_tDraw.fcy*m_iDrawID,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			RGB(255, 0, 255));
	}
	if (m_dwNextTime + m_iNextMaxTime < GetTickCount())
	{
		++m_iNextLogo;
		if (m_bAttack)
		{
			m_iNextLogo = m_iNextLogo % 7;
			m_iNextMaxTime = 90;
		}
		else if (m_iDrawID == 0)
		{
			m_iNextLogo = m_iNextLogo % 13;
			m_iNextMaxTime = 40;
		}
		else
		{
			m_iNextLogo = m_iNextLogo % 2;
			m_iNextMaxTime = 120;
		}
		m_dwNextTime = GetTickCount();
	}

}

void CMouse::Release()
{
}
