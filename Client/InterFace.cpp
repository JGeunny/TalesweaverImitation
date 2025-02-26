#include "stdafx.h"
#include "InterFace.h"
#include "Obj.h"
#include "PlayerInfo.h"
#include "BossInfo.h"
#include "Score.h"
#include "MissionClear.h"
#include "PlayerStatus.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

#include "Inventory.h"
#include "Store_UI.h"
#include "Player_Slot.h"
#include "Equip.h"

IMPLEMENT_SINGLETON(CInterFace)
CInterFace::CInterFace()
{
	Initialize();
}

CInterFace::~CInterFace()
{
	Release();
}

void CInterFace::Initialize()
{
	
	CObj* pUI = CAbstractFactory<CPlayerInfo>::Create(TEAM_MOUSE,0, 0);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI);
	pInterFace[CInterFace::PlayerInfo] = pUI;

	pUI = CAbstractFactory<CBossInfo>::Create(TEAM_MOUSE, 0, 0);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI);
	pInterFace[CInterFace::BossInfo] = pUI;

	pUI = CAbstractFactory<CScore>::Create(TEAM_MOUSE, 0, 0);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI);
	pInterFace[CInterFace::Score] = pUI;

	pUI = CAbstractFactory<CPlayerStatus>::Create(TEAM_MOUSE, 0, 0);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI);
	pInterFace[CInterFace::PlayerStatus] = pUI;

	pUI = CAbstractFactory<CInventory>::Create(TEAM_MOUSE, 0, 0);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI);
	pInterFace[CInterFace::Inventory] = pUI;

	CObj* pUI2 = CAbstractFactory<CStore_UI>::Create(TEAM_MOUSE, 0, 0);
	pUI2->Set_Target(pUI);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI2);
	pInterFace[CInterFace::Store_UI] = pUI2;

	pUI2 = CAbstractFactory<CPlayer_Slot>::Create(TEAM_MOUSE, 0, 0);
	pUI2->Set_Target(pUI);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI2);
	pInterFace[CInterFace::Player_Slot] = pUI2;

	pUI2 = CAbstractFactory<CEquip>::Create(TEAM_MOUSE, 0, 0);
	pUI2->Set_Target(pUI);
	CObjMgr::Get_Instance()->AddObject(OBJID::UI, pUI2);
	pInterFace[CInterFace::Equip] = pUI2;
}

int CInterFace::Update()
{
	for (auto& iter = m_vecUI.begin(); iter != m_vecUI.end();)
	{
		int iEvent = (*iter)->Update();
		if (iEvent == OBJ_DEAD)
		{
			delete *iter;
			*iter = nullptr;
			m_vecUI.erase(iter++);
		}
		else ++iter;
	}
	return 0;
}

void CInterFace::LateUpdate()
{
	for (auto pUI : m_vecUI)
	{
		pUI->LateUpdate();
	}
}

void CInterFace::Render(HDC hDC)
{
	for (auto pUI : m_vecUI)
	{
		pUI->Render(hDC);
	}
}

void CInterFace::Release()
{
	for (auto pUI : m_vecUI)
	{
		SAFE_DELETE(pUI);
	}
	m_vecUI.clear();
	m_vecUI.shrink_to_fit();
}

void CInterFace::LateInit()
{
}
