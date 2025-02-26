#include "stdafx.h"
#include "Equip.h"
#include "ImgMgr.h"
#include "Item.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CEquip::CEquip()
{
}


CEquip::~CEquip()
{
}

void CEquip::Initialize()
{
	m_bActivation = false;
	CImgMgr::Get_Instance()->AddImage(L"ui/Equip_Info.bmp", L"Equip_Info");
	//195*182
	ZeroMemory(m_pItem, sizeof(m_pItem));
}

int CEquip::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < CEquip::ID::END; ++i)
		{
			if (!m_pItem[i]) continue;
			if (PtInRect(&m_rtItem[i], pt))
			{
				if (m_pTarget)// 인벤토리
				{
					CObj* pPlayer = m_pTarget->Get_Target();
					if (pPlayer)//플레이어
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"SwordEquip.wav", CSoundMgr::CHANNELID::EFFECT);
						INFO_UNIT tUnit = static_cast<CUnit*>(pPlayer)->Get_Unit();
						static_cast<CItem*>(m_pItem[i])->Alter_Equip() = false;
						tUnit.iAtt -= static_cast<CItem*>(m_pItem[i])->Alter_Item().iAtt;
						tUnit.iMaxHp -= static_cast<CItem*>(m_pItem[i])->Alter_Item().iHp;
						tUnit.iHp = (tUnit.iHp > tUnit.iMaxHp) ? tUnit.iMaxHp : tUnit.iHp;
						static_cast<CUnit*>(pPlayer)->Set_Unit(tUnit);
						m_pItem[i] = nullptr;
					}
				}
			}
		}
	}
	return 0;
}

void CEquip::LateUpdate()
{
	/*for (int i = 0; i < CEquip::ID::END; ++i)
	{
		if (m_pItem[i])
			m_pItem[i]->LateUpdate();
	}*/
}

void CEquip::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Equip_Info");
	int x = 100;
	int y = 100;
	GdiTransparentBlt(hDC, x, y, 195, 182, hMemDC,
		0, 0, 195, 182, RGB(255, 0, 255));

	//int x = 50 + 343 + 25 + 10, y = 100 + 45;
	x += 7;
	y += 20;
	for (int i = 0; i < CEquip::ID::END; ++i)
	{
		m_rtItem[i] = { x, y + 5, x + 180, y + 35 };
		//Rectangle(hDC, m_rtItem[i].left, m_rtItem[i].top, m_rtItem[i].right, m_rtItem[i].bottom);
		if (m_pItem[i])
		{
			auto& tDraw = m_pItem[i]->Alter_Draw();
			bool bViewType = static_cast<CItem*>(m_pItem[i])->Alter_DetailsVeiw();
			static_cast<CItem*>(m_pItem[i])->Alter_DetailsVeiw() = false;
			//INFO_DRAW tDraw_Temp = tDraw;
			tDraw.fx = (float)x;
			tDraw.fy = (float)y;
			m_pItem[i]->Render(hDC);
			static_cast<CItem*>(m_pItem[i])->Alter_DetailsVeiw() = bViewType;
		}
		y += 31;
	}

	
}

void CEquip::Release()
{
}

void CEquip::LateInit()
{
}
