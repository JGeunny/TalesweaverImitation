#include "stdafx.h"
#include "Store_UI.h"
#include "ImgMgr.h"
#include "ObjMgr.h"

#include "Item.h"
#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"

#include "InterFace.h"
#include "Inventory.h"

#include "SoundMgr.h"

CStore_UI::CStore_UI()
{
}


CStore_UI::~CStore_UI()
{
	Release();
}

void CStore_UI::Initialize()
{
	m_bActivation = false;
	CImgMgr::Get_Instance()->AddImage(L"ui/trade.bmp", L"trade");
	//343*356

	int x = 50;
	int y = 100;
	for (int i = 0; i < CItem::END; ++i)
	{	
		if (i == CItem::MP) continue;
		if (i == CItem::SP) continue;
		CObj* pItem = CAbstractFactory<CItem>::Create(TEAM_MOUSE, x + 10, y + 45);
		static_cast<CItem*>(pItem)->Set_Kind((CItem::ID)i);
		m_listItem.emplace_back(pItem);
		y += 25;
	}
}

int CStore_UI::Update()
{
	RECT rt = {50, 100, 343 + 50, 356 + 100};
	POINT pt;
	GetCursorPos(&pt);
	ClientToScreen(g_hWND, &pt);

	CObj::LateInit();
	
	if (m_bActivation)
	{
		for (auto& pItem : m_listItem)
		{
			if (OBJ_SELECT == pItem->Update())
			{
				CObj* pInven = CInterFace::Get_Instance()->pInterFace[CInterFace::ID::Inventory];
				CObj* pPlayer = pInven->Get_Target();
				if (pInven && pPlayer)
				{
					if (static_cast<CInventory*>(pInven)->Get_InvenSize() < 12)
					{
						INFO_UNIT tUnit = static_cast<CUnit*>(pPlayer)->Get_Unit();

						auto& tItem = static_cast<CItem*>(pItem)->Alter_Item();
						if (tUnit.iGold >= tItem.iGold)
						{
							//물건을 산경우
							CSoundMgr::Get_Instance()->MyPlaySound(L"Buy.wav", CSoundMgr::CHANNELID::NPC);

							tUnit.iGold -= tItem.iGold;
							static_cast<CUnit*>(pPlayer)->Set_Unit(tUnit);
							//펫주머니인 경우에는 탐색을 해서 있는 경우 카운트만 올려줌
							if (static_cast<CItem*>(pItem)->Get_Kind() == CItem::ID::SEED)
							{
								bool bFind = false;
								auto& listItem = static_cast<CInventory*>(pInven)->Alter_ListItem();
								for (auto& pItem : listItem)
								{
									if (static_cast<CItem*>(pItem)->Get_Kind() == CItem::ID::SEED)
									{
										static_cast<CItem*>(pItem)->Alter_ItemCount() += 1;
										bFind = true;
										break;
									}
								}
								if (false == bFind)
								{
									CObj* pCreateItem = CAbstractFactory<CItem>::Create(TEAM_MOUSE, 0, 0);
									static_cast<CItem*>(pCreateItem)->Set_Kind(static_cast<CItem*>(pItem)->Get_Kind());
									static_cast<CInventory*>(pInven)->AddItem(pCreateItem);
								}
							}
							//물약인 경우에는 탐색을 해서 있는 경우 카운트만 올려줌
							else if (static_cast<CItem*>(pItem)->Get_Kind() == CItem::ID::HP)
							{
								bool bFind = false;
								auto& listItem = static_cast<CInventory*>(pInven)->Alter_ListItem();
								for (auto& pItem : listItem)
								{
									if (static_cast<CItem*>(pItem)->Get_Kind() == CItem::ID::HP)
									{
										static_cast<CItem*>(pItem)->Alter_ItemCount() += 1;
										bFind = true;
										break;
									}
								}
								if (false == bFind)
								{
									CObj* pCreateItem = CAbstractFactory<CItem>::Create(TEAM_MOUSE, 0, 0);
									static_cast<CItem*>(pCreateItem)->Set_Kind(static_cast<CItem*>(pItem)->Get_Kind());
									static_cast<CInventory*>(pInven)->AddItem(pCreateItem);
								}
							}
							else
							{
								CObj* pCreateItem = CAbstractFactory<CItem>::Create(TEAM_MOUSE, 0, 0);
								static_cast<CItem*>(pCreateItem)->Set_Kind(static_cast<CItem*>(pItem)->Get_Kind());
								static_cast<CInventory*>(pInven)->AddItem(pCreateItem);
							}
						}
						else
						{
							CSoundMgr::Get_Instance()->MyPlaySound(L"over.mp3", CSoundMgr::CHANNELID::NPC);
							//골드가 부족해서 못 사는 경우
						}
					}
					else
					{
						//인벤토리가 부족해서 못사는 경우
						CSoundMgr::Get_Instance()->MyPlaySound(L"over.mp3", CSoundMgr::CHANNELID::NPC);
					}
				}
			}
			pItem->Alter_Activation() = m_bActivation;
		}
	}
	
	return 0;
}

void CStore_UI::LateUpdate()
{
	if (m_bActivation)
	{
		for (auto& pItem : m_listItem)
		{
			pItem->LateUpdate();
		}
	}
}

void CStore_UI::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Inven_Info");
	int x = 50;
	int y = 100;
	GdiTransparentBlt(hDC, x, y, 343, 356, hMemDC,
		0, 0, 343, 356, RGB(255, 0, 255));

	for (auto& pItem : m_listItem)
	{
		pItem->Render(hDC);
	}
}

void CStore_UI::Release()
{
	for (auto& pItem : m_listItem)
	{
		SAFE_DELETE(pItem);
	}
	m_listItem.clear();
}

void CStore_UI::LateInit()
{
}

void CStore_UI::Store_Open()
{
	if (!m_bActivation)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"OpenWnd.wav", CSoundMgr::CHANNELID::NPC);
		m_bActivation = true;
		if (m_pTarget)
		{
			m_pTarget->Alter_Activation() = true;
		}
	}
}

void CStore_UI::Store_Close()
{
	if (m_bActivation)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"CloseWnd.wav", CSoundMgr::CHANNELID::NPC);
		m_bActivation = false;
		if (m_pTarget)
		{
			m_pTarget->Alter_Activation() = false;
		}
	}
}
