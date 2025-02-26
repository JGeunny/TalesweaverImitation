#include "stdafx.h"
#include "PlayerStatus.h"
#include "ImgMgr.h"

CPlayerStatus::CPlayerStatus()
{
}


CPlayerStatus::~CPlayerStatus()
{
}

void CPlayerStatus::Initialize()
{
	m_bActivation = false;
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Stats.bmp", L"Player_Stats");
	//293*269
}

int CPlayerStatus::Update()
{
	CObj::LateInit();
	if (m_bActivation)
	{
		
	}
	return 0;
}

void CPlayerStatus::LateUpdate()
{
	if (m_bActivation)
	{

	}
}

void CPlayerStatus::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Stats");
	int x = 100;
	int y = 100;
	GdiTransparentBlt(hDC, x, y, 293, 269, hMemDC,
		0, 0, 293, 269, RGB(255, 0, 255));

	swprintf_s(szInfo, L"%d", tUnit.iLevel);
	RECT rt = {  x + 140, y + 35,  x + 170, y + 50 };	//레벨
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%s", tUnit.szName);
	rt = { x + 140, y + 53,  x + 265, y + 70 };	//이름
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%s", L"전사");
	rt = { x + 140, y + 73,  x + 265, y + 90 };	//타입
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%s", L"웨폰 마스터");
	rt = { x + 140, y + 93,  x + 265, y + 110 };	//칭호
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%d / %d", tUnit.iHp, tUnit.iMaxHp);
	rt = { x + 55, y + 187,  x + 185, y + 203};	//HP
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%d / %d", tUnit.iMp, tUnit.iMaxMp);
	rt = { x + 55, y + 202,  x + 185, y + 218 };	//MP
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	swprintf_s(szInfo, L"%d", tUnit.iGold);
	rt = { x + 55, y + 218,  x + 185, y + 233 };	//SEED
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);
}

void CPlayerStatus::Release()
{
}

void CPlayerStatus::LateInit()
{
}
