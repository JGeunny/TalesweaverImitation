#include "stdafx.h"
#include "Player_Slot.h"
#include "ImgMgr.h"
#include "Inventory.h"
#include "Item.h"

#include "KeyMgr.h"

#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"
#include "Restore.h"
#include "Pet.h"

CPlayer_Slot::CPlayer_Slot()
	:m_pItem_Hp(nullptr)
	, m_pItem_Pet(nullptr)
{
}


CPlayer_Slot::~CPlayer_Slot()
{

}

void CPlayer_Slot::Initialize()
{
	//m_bActivation = false;
	CImgMgr::Get_Instance()->AddImage(L"ui/Player_Slot.bmp", L"Player_Slot");
	CImgMgr::Get_Instance()->AddImage(L"item/items.bmp", L"items");
	//133*45
}

int CPlayer_Slot::Update()
{
	CObj::LateInit();
	if (m_bActivation)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_F1, CKeyMgr::ID::SPECIAL))
		{
			if (m_pTarget)
			{
				CObj* pPlayer = m_pTarget->Get_Target();
				//플레이어가 존재 한다면 실행
				if (pPlayer)
				{
					//물약을 찾는다.
					m_pItem_Hp = nullptr;
					auto& listItem = static_cast<CInventory*>(m_pTarget)->Alter_ListItem();
					for (auto& pObj : listItem)
					{
						if (CItem::ID::HP == static_cast<CItem*>(pObj)->Get_Kind())
						{
							m_pItem_Hp = pObj;
							break;
						}
					}
					//물약이 있다.
					if (m_pItem_Hp)
					{
						if (static_cast<CItem*>(m_pItem_Hp)->Alter_ItemCount() > 0)
						{
							static_cast<CItem*>(m_pItem_Hp)->Alter_ItemCount() -= 1;
							INFO_UNIT tUnit = static_cast<CUnit*>(pPlayer)->Get_Unit();
							tUnit.iHp += static_cast<CItem*>(m_pItem_Hp)->Alter_Item().iHp;
							tUnit.iHp = (tUnit.iHp > tUnit.iMaxHp) ? tUnit.iMaxHp : tUnit.iHp;
							static_cast<CUnit*>(pPlayer)->Set_Unit(tUnit);
							INFO_DRAW tDraw = pPlayer->Get_Info();
							CObjMgrBuffer::Get_Instance()->AddObject(OBJID::EFFECT,
								CAbstractFactory<CRestore>::Create(TEAM_MOUSE, tDraw.fx, tDraw.fy));
						}
					}
				}
			}
		}
		if (CKeyMgr::Get_Instance()->KeyDown(VK_F2, CKeyMgr::ID::SPECIAL))
		{
			if (m_pTarget)
			{
				CObj* pPlayer = m_pTarget->Get_Target();
				//플레이어가 존재 한다면 실행
				if (pPlayer)
				{
					//펫 주머니를 찾는다.
					m_pItem_Pet = nullptr;
					auto& listItem = static_cast<CInventory*>(m_pTarget)->Alter_ListItem();
					for (auto& pObj : listItem)
					{
						if (CItem::ID::SEED == static_cast<CItem*>(pObj)->Get_Kind())
						{
							m_pItem_Pet = pObj;
							break;
						}
					}
					//펫 주머니가 있다.
					if (m_pItem_Pet)
					{
						if (static_cast<CItem*>(m_pItem_Pet)->Alter_ItemCount() > 0)
						{
							static_cast<CItem*>(m_pItem_Pet)->Alter_ItemCount() -= 1;
							INFO_DRAW tDraw = pPlayer->Get_Info();
							CObj* pObj = CAbstractFactory<CPet>::Create_Unit(TEAM_1, tDraw.fx - 100, tDraw.fy, 0, L"커비", 100, 800);
							pObj->Set_Master(pPlayer);
							CObjMgrBuffer::Get_Instance()->AddObject(OBJID::ID::UNIT, pObj);
							CObjMgrBuffer::Get_Instance()->AddObject(OBJID::EFFECT,
								CAbstractFactory<CRestore>::Create(TEAM_MOUSE, tDraw.fx, tDraw.fy));
						}
					}
				}
			}
		}
	}
	return 0;
}

void CPlayer_Slot::LateUpdate()
{
	if (m_bActivation)
	{

	}
}

void CPlayer_Slot::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Player_Slot");
	int x = 0;
	int y = WINCY - 45;
	GdiTransparentBlt(hDC, x, y, 133, 45, hMemDC,
		0, 0, 133, 45, RGB(255, 0, 255));

	bool bItemHp = false;
	bool bItemPet = false;
	auto& listItem = static_cast<CInventory*>(m_pTarget)->Alter_ListItem();
	for (auto& pObj : listItem)
	{
		if (CItem::ID::HP == static_cast<CItem*>(pObj)->Get_Kind())
		{
			if (static_cast<CItem*>(pObj)->Alter_ItemCount() > 0)
			{
				bItemHp = true;
			}
		}
		if (CItem::ID::SEED == static_cast<CItem*>(pObj)->Get_Kind())
		{
			if (static_cast<CItem*>(pObj)->Alter_ItemCount() > 0)
			{
				bItemPet = true;
			}
		}
	}
	//물약이 있다.
	if (bItemHp)
	{
		hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"items");
		GdiTransparentBlt(hDC, x + 10, y + 15, 24, 24, hMemDC,
			0, 0, 24, 24, RGB(255, 0, 255));
	}

	//펫이 있다.
	if (bItemPet)
	{
		hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"items");
		GdiTransparentBlt(hDC, x + 10 + 24 + 5, y + 15, 24, 24, hMemDC,
			24 * 13, 0, 24, 24, RGB(255, 0, 255));
	}
}

void CPlayer_Slot::Release()
{
}

void CPlayer_Slot::LateInit()
{
}
