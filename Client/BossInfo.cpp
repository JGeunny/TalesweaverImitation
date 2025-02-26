#include "stdafx.h"
#include "BossInfo.h"
#include "ImgMgr.h"

CBossInfo::CBossInfo()
{
}


CBossInfo::~CBossInfo()
{
}

void CBossInfo::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Monster/BorisBar.bmp", L"BorisBar");
	//229*46
	CImgMgr::Get_Instance()->AddImage(L"Monster/BorisHp.bmp", L"BorisHp");
	// 159* 15
}

int CBossInfo::Update()
{
	return 0;
}

void CBossInfo::LateUpdate()
{
}

void CBossInfo::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;

	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"BorisBar");
	GdiTransparentBlt(hDC, WINCX - 229, 0, 229, 46, hMemDC,
		0, 0, 229, 46, RGB(255, 0, 255));

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"BorisHp");
	GdiTransparentBlt(hDC, WINCX - 229 + 66, 21, int(159 * tUnit.iHp / tUnit.iMaxHp), 15, hMemDC,
		0, 0, 159, 15, RGB(255, 0, 255));

	swprintf_s(szInfo, L"%d / %d", tUnit.iHp, tUnit.iMaxHp);
	//TextOut(hDC, WINCX - 229 + 110, 21, szInfo, lstrlen(szInfo));
	RECT rt = { WINCX - 229 + 66, 21 + 2,  WINCX - 229 + 66 + 159, 21 + 15 };
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);
}

void CBossInfo::Release()
{
}

void CBossInfo::LateInit()
{
}
