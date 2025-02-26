#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Airplane.h"

#include "Mouse.h"
#include "Hunter.h"

//Unit
#include "Player.h"
#include "Monster.h"
#include "Boss.h"
#include "Slime.h"

#include "Turret.h"

//Tile
#include "Wall.h"

#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"

#include "TileMgr.h"

#include "Tile.h"

#include "ScrollMgr.h"

#include "PlayerInfo.h"
#include "BossInfo.h"
#include "Score.h"
#include "PlayerStatus.h"
#include "Inventory.h"

#include "ObjMgrBuffer.h"

IMPLEMENT_SINGLETON(CObjMgr)
CObjMgr::CObjMgr()
{
	
}


CObjMgr::~CObjMgr()
{
	Release();
}

bool CObjMgr::Initialize()
{
	vector<CObj*> vecTile = CTileMgr::Get_Instance()->Alter_VecTile();

	for (auto& pTile : vecTile)
	{
		TCHAR* pFrameKey = static_cast<CTile*>(pTile)->Get_FrameKey();
		if (!lstrcmp(pFrameKey, L"Tile_2"))//T	//�÷��̾�
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObj* pObj = CAbstractFactory<CPlayer>::Create_Unit(TEAM_1, tDraw.fx, tDraw.fy, 0, L"�÷��̾�", 80, 80000);
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, pObj);
			CScrollMgr::Alter_Scroll().x = float(- tDraw.fx + WINCX * 0.5);
			CScrollMgr::Alter_Scroll().y = float(- tDraw.fy + WINCY * 0.5);
			
			for (auto& pUI : m_ObjList[OBJID::UI])
			{
				if (dynamic_cast<CPlayerInfo*>(pUI))
					static_cast<CPlayerInfo*>(pUI)->Set_Target(pObj);
				if (dynamic_cast<CScore*>(pUI))
					static_cast<CScore*>(pUI)->Set_Target(pObj);
				if (dynamic_cast<CPlayerStatus*>(pUI))
					static_cast<CPlayerStatus*>(pUI)->Set_Target(pObj);
				if (dynamic_cast<CInventory*>(pUI))
					static_cast<CInventory*>(pUI)->Set_Target(pObj);
			}	
		}
		else if (!lstrcmp(pFrameKey, L"Tile_3"))//S	//NPC
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CSlime>::Create_Unit(TEAM_1, tDraw.fx, tDraw.fy, 0, L"������", 0, 500));
		}
		else if (!lstrcmp(pFrameKey, L"Tile_4"))//F	//������
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CSlime>::Create_Unit(TEAM_2, tDraw.fx, tDraw.fy, 0, L"������", 0, 500));
		}
		else if (!lstrcmp(pFrameKey, L"Tile_5"))//DI //����
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CMonster>::Create_Unit(TEAM_2, tDraw.fx, tDraw.fy, 0, L"����"));
		}
		else if (!lstrcmp(pFrameKey, L"Tile_6"))//DII //Ȱ��³�
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, CAbstractFactory<CHunter>::Create_Unit(TEAM_2, tDraw.fx, tDraw.fy, 0, L"����"));
		}
		else if (!lstrcmp(pFrameKey, L"Tile_7"))//B
		{
			INFO_DRAW tDraw = pTile->Get_Info();
			CObj* pObj = CAbstractFactory<CBoss>::Create_Unit(TEAM_2, tDraw.fx, tDraw.fy, 0, L"Ÿ�뽺", 80, 16000,0,1,9999);
			CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, pObj);
			INFO_UNIT tUnit = static_cast<CUnit*>(pObj)->Get_Unit();
			tUnit.iMaxExp = 75750;
			static_cast<CUnit*>(pObj)->Set_Unit(tUnit);
			for (auto& pUI : m_ObjList[OBJID::UI])
			{
				if (dynamic_cast<CBossInfo*>(pUI))
					static_cast<CBossInfo*>(pUI)->Set_Target(pObj);
			}
		}
	}
	return true;
}

void CObjMgr::AddObject(OBJID::ID eID, CObj * pObj)
{
	m_ObjList[eID].emplace_back(pObj);
}

int CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (list<CObj*>::iterator& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (iEvent == OBJ_DEAD)
			{
				delete *iter;
				*iter = nullptr;
				iter = m_ObjList[i].erase(iter);
			}
			else ++iter;
		}
	}
	CObjMgrBuffer::Get_Instance()->Update();
	return 0;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->LateUpdate();
			if (m_ObjList[i].empty())
				break;
		}
	}
	//�浹 ó��
	//CCollisionMgr::CollisionRect(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::CollisionRect(m_ObjList[OBJID::MOUSE], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::CollisionSphere(m_ObjList[OBJID::MOUSE], m_ObjList[OBJID::MONSTER]);

	//��ų�� ���� ���
	//CCollisionMgr::CollisionRect(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::SKILL_CRASH]);

	
	
	//���� �����̱�
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::TILE]);
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::WALL], m_ObjList[OBJID::TILE]);
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::TILE], m_ObjList[OBJID::UNIT]);

	//���󰡱�
	CCollisionMgr::Follow_Enemy(m_ObjList[OBJID::UNIT]);

	//��ų ���� ���� �̴� �� ƨ���
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::SKILL_CRASH], m_ObjList[OBJID::TILE]);

	//���� �� ������ ó��
	CCollisionMgr::CollisionRectAttack(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::SKILL_CRASH]);
	CCollisionMgr::CollisionRectAttack(m_ObjList[OBJID::BUILDING], m_ObjList[OBJID::SKILL_CRASH]);

	//���� �ε�ĥ�� �Ѿ� ƨ���
	//CCollisionMgr::CollisionRectWallAndAttack(m_ObjList[OBJID::WALL], m_ObjList[OBJID::SKILL_CRASH]);
	
	//�������� ó��
	//CPhysics2D::GravityObj(m_ObjList[OBJID::PLAYER], m_PointList);

	//���ֳ��� �浹
	CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::UNIT]);
	CCollisionMgr::CollisionRectMapEx(CTileMgr::Get_Instance()->Alter_VecTile(), m_ObjList[OBJID::UNIT]);

	//������ �ǹ��� ����
	CCollisionMgr::CollisionRectEx(m_ObjList[OBJID::BUILDING], m_ObjList[OBJID::UNIT]);

	//�ǹ� Ÿ����
	CCollisionMgr::Follow_Building_Enemy(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::BUILDING]);
	CCollisionMgr::Follow_Building_Enemy(m_ObjList[OBJID::BUILDING], m_ObjList[OBJID::UNIT]);

	//���콺���� ���������� ���콺 ��� �ٲ��
	if (false == m_ObjList[OBJID::MOUSE].empty())
		CCollisionMgr::CollisionMouseOnUnit(m_ObjList[OBJID::UNIT], m_ObjList[OBJID::MOUSE].front());
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Render_Scroll(hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			if (pObj)
			{
				delete pObj;
				pObj = nullptr;
			}
		}
		m_ObjList[i].clear();
	}
}

void CObjMgr::DeleteID(OBJID::ID eID)
{
	for (auto& pObj : m_ObjList[eID])
	{
		SAFE_DELETE(pObj);
	}
	m_ObjList[eID].clear();
}

void CObjMgr::RecogDistAllID(OBJID::ID eID)
{
	for (auto& pObj : m_ObjList[eID])
	{
		if(nullptr == dynamic_cast<CTurret*>(pObj))
			pObj->Set_RecogDist(9999);
	}
}
