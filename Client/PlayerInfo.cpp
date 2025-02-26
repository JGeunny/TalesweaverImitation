#include "stdafx.h"
#include "PlayerInfo.h"
#include "ImgMgr.h"

CPlayerInfo::CPlayerInfo()
{
}


CPlayerInfo::~CPlayerInfo()
{
}

void CPlayerInfo::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Info.bmp", L"Player_Info");
	// 178*100
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Hp.bmp", L"Player_Hp");
	// 84* 14
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Mp.bmp", L"Player_Mp");
	// 84* 14
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Sp.bmp", L"Player_Sp");
	// 84* 14
}

int CPlayerInfo::Update()
{
	CObj::LateInit();
	return 0;
}

void CPlayerInfo::LateUpdate()
{
}

void CPlayerInfo::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;

	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Info");
	GdiTransparentBlt(hDC, 0, 0, 178, 100, hMemDC,
		0, 0, 178, 100,	RGB(255, 0, 255));

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Hp");
	tUnit.iMaxHp = tUnit.iMaxHp <= 0 ? 1 : tUnit.iMaxHp;
	GdiTransparentBlt(hDC, 94, 15, int(84 * tUnit.iHp / tUnit.iMaxHp), 14, hMemDC,
		0, 0, 84, 14, RGB(255, 0, 255));
	swprintf_s(szInfo, L"%d / %d", tUnit.iHp, tUnit.iMaxHp);
	//TextOut(hDC, 100, 15, szInfo, lstrlen(szInfo));
	RECT rt = {94, 15 + 2,  94 + 84, 15 + 14};
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Mp");
	tUnit.iMaxMp = tUnit.iMaxMp <= 0 ? 1 : tUnit.iMaxMp;
	GdiTransparentBlt(hDC, 94, 31, int(84 * tUnit.iMp / tUnit.iMaxMp), 14, hMemDC,
		0, 0, 84, 14, RGB(255, 0, 255));
	swprintf_s(szInfo, L"%d / %d", tUnit.iMp, tUnit.iMaxMp);
	//TextOut(hDC, 100, 31, szInfo, lstrlen(szInfo));
	rt = { 94, 31 + 2,  94 + 84, 31 + 14 };
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Sp");
	tUnit.iMaxExp = tUnit.iMaxExp <= 0 ? 1 : tUnit.iMaxExp;
	GdiTransparentBlt(hDC, 94, 47, int(84 * tUnit.iExp / tUnit.iMaxExp), 14, hMemDC,
		0, 0, 84, 14, RGB(255, 0, 255));
	swprintf_s(szInfo, L"%d / %d", tUnit.iExp, tUnit.iMaxExp);
	//TextOut(hDC, 100, 47, szInfo, lstrlen(szInfo));
	rt = { 94, 47 + 2,  94 + 84, 47 + 14 };
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	//·¹º§
	//Ellipse(hDC,50, 70, 50 + 20, 70 +20);
	swprintf_s(szInfo, L"%d", tUnit.iLevel);
	TextOut(hDC, 60, 73 + 2, szInfo, lstrlen(szInfo));
}

void CPlayerInfo::Release()
{
}

void CPlayerInfo::LateInit()
{
	
}
