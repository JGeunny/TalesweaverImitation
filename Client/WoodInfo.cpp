#include "stdafx.h"
#include "WoodInfo.h"
#include "ImgMgr.h"

CWoodInfo::CWoodInfo()
{
}

CWoodInfo::~CWoodInfo()
{
}

void CWoodInfo::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"ui/WoodInfo.bmp", L"WoodInfo");
	m_dwTime = GetTickCount();

	//287*265
}

int CWoodInfo::Update()
{
	if (m_tDraw_Wood.fy > WINCY + 300)
	{
		return OBJ_DEAD;
	}
	CObj::LateInit();

	if (m_dwTime + 5000 > GetTickCount())
	{
		if (m_tDraw_Wood.fy > WINCY - m_tDraw_Wood.fcy * 0.5)
			m_tDraw_Wood.fy -= 10;
	}
	else
	{
		m_tDraw_Wood.fy += 10;
	}

	return 0;
}

void CWoodInfo::LateUpdate()
{
}

void CWoodInfo::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"WoodInfo");
	RECT rt = m_tDraw_Wood.Get_Rect();
	GdiTransparentBlt(hDC, rt.left, rt.top, m_tDraw_Wood.fcx, m_tDraw_Wood.fcy, hMemDC,
		0, 0, 287, 265, RGB(255, 255, 255));
	rt.top += 60;
	rt.left += 20;
	rt.right -= 20;
	DWORD dwRGB = GetTextColor(hDC);
	SetTextColor(hDC, RGB(4, 82, 115));

	HFONT hFont = CreateFont(18, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("±¼¸²"));
	HFONT saveFont = (HFONT)SelectObject(hDC, hFont);

	DrawText(hDC, m_szInfo, lstrlen(m_szInfo), &rt, DT_VCENTER | DT_CENTER |DT_WORDBREAK);

	DeleteObject(SelectObject(hDC, saveFont));
	SetTextColor(hDC, dwRGB);
}

void CWoodInfo::Release()
{
}

void CWoodInfo::LateInit()
{
	m_tDraw_Wood.fcx = 200;
	m_tDraw_Wood.fcy = 200;
	m_tDraw_Wood.fx = WINCX - m_tDraw_Wood.fcx * 0.5;
	m_tDraw_Wood.fy = WINCY + m_tDraw_Wood.fcy * 0.5;
}
