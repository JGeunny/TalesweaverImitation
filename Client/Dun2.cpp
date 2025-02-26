#include "stdafx.h"
#include "Dun2.h"
#include "ObjMgr.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "ObjMgrBuffer.h"
#include "MissionClear.h"
#include "Player.h"
#include "SceneMgr.h"

#include "TurretB.h"
#include "Circle.h"
#include "SoundMgr.h"

#include "WoodInfo.h"

CDun2::CDun2()
	:m_iMissionState(0)
{
}


CDun2::~CDun2()
{
	Release();
}

void CDun2::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Dun.mp3");
	//CImgMgr::Get_Instance()->AddImage(L"Map/Dun2.bmp", L"Dun2");
	g_iTileX = 113;
	g_iTileY = 57;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::DUN2);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	CObjMgrBuffer::Get_Instance()->
		AddObject(OBJID::ID::BUILDING, CAbstractFactory<CTurretB>::Create_Unit(TEAM_1, 1100, 1100, 0, L"포토캐논", 100, 16000));
	
	CObjMgrBuffer::Get_Instance()->
		AddObject(OBJID::ID::BUILDING, CAbstractFactory<CTurretB>::Create_Unit(TEAM_1, 1400, 1300, 0, L"포토캐논", 100, 16000));
	
	int x = 1100, y = 900 ;
	CObj* pObj = CAbstractFactory<CCircle>::Create(TEAM_1, x, y);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::SLIME);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, x + 150, y + 100);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, x + 300, y + 200);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, x + 450, y + 300);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, x + 600, y + 400);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);


	CObjMgrBuffer::Get_Instance()->
		AddObject(OBJID::ID::BUILDING, CAbstractFactory<CTurretB>::Create_Unit(TEAM_2, 2100, 500, 0, L"포토캐논", 100, 16000));

	CObjMgrBuffer::Get_Instance()->
		AddObject(OBJID::ID::BUILDING, CAbstractFactory<CTurretB>::Create_Unit(TEAM_2, 2400, 700, 0, L"포토캐논", 100, 16000));

	x = 1900, y = 500;
	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, x, y);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::SLIME);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, x + 150, y + 100);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, x + 300, y + 200);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, x + 450, y + 300);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, x + 600, y + 400);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	CObj* pInfo = CAbstractFactory<CWoodInfo>::Create(TEAM_MOUSE);
	static_cast<CWoodInfo*>(pInfo)->Set_Info(L"모든 포토캐논을 파괴하세요~");
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pInfo);
}

int CDun2::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->RecogDistAllID(OBJID::UNIT);

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//보스로 넘어감
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
		return 0;
	}

	if (0 != m_iMissionState)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	//던전1로 넘어감
		{
			CScrollMgr::Alter_Scroll().x = 0;
			CScrollMgr::Alter_Scroll().y = 0;
			CTileMgr::Get_Instance()->Release();
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_TOWN);
			return 0;
		}
	}
	//적 유닛이 없을 경우 미션 클리어
	//플레이어가 죽을 경우 미션 페일
	int iPlayerCount = 0;
	int iEnemyCount = 0;
	auto& listUnit = *CObjMgr::Get_Instance()->Get_List(OBJID::UNIT);
	for (auto& pObj : listUnit)
	{
		if ((pObj->Get_Team() == TEAM_1))
		{
			if (dynamic_cast<CPlayer*>(pObj))
			{
				++iPlayerCount;
			}
		}
	}
	auto& listBuilding = *CObjMgr::Get_Instance()->Get_List(OBJID::BUILDING);
	for (auto& pObj : listBuilding)
	{
		if ((pObj->Get_Team() != TEAM_MOUSE)
			&& (pObj->Get_Team() != TEAM_TILE)
			&& (pObj->Get_Team() != TEAM_1)
			)
		{
			if (dynamic_cast<CTurretB*>(pObj))
			{
				if (false == pObj->Get_Dead())
				{
					++iEnemyCount;
				}
			}
		}
	}

	if (0 == m_iMissionState)
	{
		//플레이어가 없는 경우 미션 페일
		if (iPlayerCount == 0)
		{
			CObj* pUI = CAbstractFactory<CMissionClear>::Create(TEAM_MOUSE, 0, 0);
			static_cast<CMissionClear*>(pUI)->Set_ClearImage(false);
			CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UI, pUI);
			m_iMissionState = 2;
			return 0;
		}
		//적이 없는 경우 미션 클리어
		if (iEnemyCount == 0)
		{
			CObj* pUI = CAbstractFactory<CMissionClear>::Create(TEAM_MOUSE, 0, 0);
			CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UI, pUI);
			m_iMissionState = 1;
			CSceneMgr::g_iNextStage = 2;
			return 0;
		}
	}
	return 0;
}

void CDun2::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CDun2::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Dun2");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CDun2::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Dun2");
}

void CDun2::LateInit()
{
}
