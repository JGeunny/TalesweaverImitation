#include "stdafx.h"
#include "Tile.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"

CTile::CTile()
{
	lstrcpy(m_szFrameKey, L"Tile_0");
}


CTile::~CTile()
{
}

void CTile::Initialize()
{
	m_tDraw.Initialize(400, 300, 30, 30, 10, 0);
}

int CTile::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CTile::LateUpdate()
{
}

void CTile::Render(HDC hDC)
{
	RECT rt = m_tDraw.Get_Rect();
	/*Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);*/
	int iScrollX = (int)CScrollMgr::Alter_Scroll().x;
	int iScrollY = (int)CScrollMgr::Alter_Scroll().y;
	/*HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Tile");
	BitBlt(hDC, rt.left + iScrollX, rt.top + iScrollY,
		m_tDraw.fcx, m_tDraw.fcy,
		hMemDC,
		m_tDraw.fcx * m_iDrawID, 0,
		SRCCOPY);*/

	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_szFrameKey);
	GdiTransparentBlt(hDC, rt.left + iScrollX, rt.top + iScrollY,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
		0, 0,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy,
		RGB(255, 0, 255));

}

void CTile::Release()
{
}

void CTile::LateInit()
{
}
