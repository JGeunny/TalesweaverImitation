#include "stdafx.h"
#include "Inventory.h"
#include "ImgMgr.h"
#include "InterFace.h"
#include "Item.h"
#include "Equip.h"
#include "SoundMgr.h"

CInventory::CInventory()
{
}


CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize()
{
	Release();
	m_bActivation = false;
	CImgMgr::Get_Instance()->AddImage(L"ui/Inven_Info.bmp", L"Inven_Info");
	//343*398
}

int CInventory::Update()
{
	RECT rt = { 50 + 343 + 25, 100, 50 + 343 + 25 +343, 398 + 100 };
	POINT pt;
	GetCursorPos(&pt);
	ClientToScreen(g_hWND, &pt);

	CObj::LateInit();

	if (m_bActivation)
	{
		CObj* pStore = CInterFace::Get_Instance()->pInterFace[CInterFace::ID::Store_UI];
		CObj* pEquip = CInterFace::Get_Instance()->pInterFace[CInterFace::ID::Equip];
		CObj* pSlot = CInterFace::Get_Instance()->pInterFace[CInterFace::ID::Player_Slot];
		for (auto& iter = m_listItem.begin(); iter != m_listItem.end();)
		{
			int iEvent = (*iter)->Update();

			if(OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listItem.erase(iter);
			}
			else if (OBJ_SELECT == iEvent)
			{
				if (pEquip->Alter_Activation())
				{
					//장비 창이 켜져있을 경우에만 장비가 껴지게끔 
					if (m_pTarget)
					{
						if (static_cast<CItem*>(*iter)->Alter_ItemCount() > 0)
						{
							//해당 아이템 타입에 맞는 장비를 가져옴
							bool	bEquip = false; //착용가능 부위
							CEquip::ID eEquipType = CEquip::ID::END;
							switch (static_cast<CItem*>(*iter)->Get_Kind())
							{
							case CItem::ID::HP:
							case CItem::ID::MP:
							case CItem::ID::SP:
								break;
							case CItem::ID::ARMOR1:
							case CItem::ID::ARMOR2:
								eEquipType = CEquip::ID::ARMOR;
								bEquip = true;
								break;
							case CItem::ID::SWORD1:
							case CItem::ID::SWORD2:
								eEquipType = CEquip::ID::HAND;
								bEquip = true;
								break;
							case CItem::ID::SHOES1:
							case CItem::ID::SHOES2:
								eEquipType = CEquip::ID::FOOT;
								bEquip = true;
								break;
							case CItem::ID::RING1:
							case CItem::ID::RING2:
								eEquipType = CEquip::ID::ARMS;
								bEquip = true;
								break;
							case CItem::ID::HAT1:
							case CItem::ID::HAT2:
								eEquipType = CEquip::ID::HEAD;
								bEquip = true;
								break;
							case CItem::ID::SEED:
								break;
							}
							if (bEquip)
							{
								CSoundMgr::Get_Instance()->MyPlaySound(L"SwordEquip.wav", CSoundMgr::CHANNELID::EFFECT);
								CObj*& pItem = static_cast<CEquip*>(pEquip)->Alter_Item(eEquipType);
								INFO_UNIT tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
								if (pItem)
								{
									// 아이템이 있는 경우 캐릭터에 있는 능력치를 지워주고 감
									static_cast<CItem*>((pItem))->Alter_Equip() = false;
									tUnit.iAtt -= static_cast<CItem*>(pItem)->Alter_Item().iAtt;
									tUnit.iMaxHp -= static_cast<CItem*>(pItem)->Alter_Item().iHp;
									tUnit.iHp = (tUnit.iHp > tUnit.iMaxHp) ? tUnit.iMaxHp : tUnit.iHp;
								}
								//없다면 바로 넣어줌
								static_cast<CItem*>((*iter))->Alter_Equip() = true;
								tUnit.iAtt += static_cast<CItem*>((*iter))->Alter_Item().iAtt;
								tUnit.iMaxHp += static_cast<CItem*>((*iter))->Alter_Item().iHp;
								pItem = (*iter);
								static_cast<CUnit*>(m_pTarget)->Set_Unit(tUnit);
							}
						}
					}
				}
				else if (pStore->Alter_Activation())
				{
					//판매
					if (m_pTarget)
					{
						if (static_cast<CItem*>(*iter)->Alter_ItemCount() > 0)
						{
							if (false == static_cast<CItem*>((*iter))->Alter_Equip())
							{
								CSoundMgr::Get_Instance()->MyPlaySound(L"Sell.wav", CSoundMgr::CHANNELID::NPC);

								INFO_UNIT tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
								tUnit.iGold += static_cast<CItem*>(*iter)->Alter_Item().iGold;
								static_cast<CUnit*>(m_pTarget)->Set_Unit(tUnit);
								static_cast<CItem*>(*iter)->Alter_ItemCount() -= 1;
							}
							else
							{
								
								//착용중인 장비는 판매 불가
								CSoundMgr::Get_Instance()->MyPlaySound(L"over.mp3", CSoundMgr::CHANNELID::NPC);
							}
						}
					}
				}
				else
				{

				}
				++iter;
			}
			else ++iter;
		}
	}
	return 0;
}

void CInventory::LateUpdate()
{
	if (m_bActivation)
	{
		int x = 50 + 343 + 25 + 10, y = 100 + 45;
		for (auto& pItem : m_listItem)
		{
			auto& tDraw = pItem->Alter_Draw();
			tDraw.fx = x;
			tDraw.fy = y;
			pItem->LateUpdate();
			y += 25;
		}
	}
}

void CInventory::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	TCHAR szInfo[100];
	INFO_UNIT tUnit;
	if (dynamic_cast<CUnit*>(m_pTarget))
		tUnit = static_cast<CUnit*>(m_pTarget)->Get_Unit();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Inven_Info");
	int x = 50 + 343 + 25;
	int y = 100;
	GdiTransparentBlt(hDC, x, y, 343, 398, hMemDC,
		0, 0, 343, 398, RGB(255, 0, 255));

	RECT rt = { x + 35, y + 380 ,  x + 90, y + 390 };
	swprintf_s(szInfo, L"%d", 12-m_listItem.size());
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	rt = { x + 240, y + 380 ,  x + 320, y + 390 };
	swprintf_s(szInfo, L"%d", static_cast<CUnit*>(m_pTarget)->Get_Unit().iGold);
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);

	for (auto& pItem : m_listItem)
	{
		pItem->Render(hDC);
	}
}

void CInventory::Release()
{
	for (auto& pItem : m_listItem)
	{
		SAFE_DELETE(pItem);
	}
	m_listItem.clear();
}

void CInventory::LateInit()
{
}

void CInventory::AddItem(CObj * _pObj)
{
	m_listItem.emplace_back(_pObj);
}
