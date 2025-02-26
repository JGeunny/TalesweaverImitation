#include "stdafx.h"
#include "Boss_Scene.h"
#include "ObjMgr.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "ObjMgrBuffer.h"
#include "MissionClear.h"
#include "Player.h"
#include "Boss.h"

#include "SoundMgr.h"

#include "WoodInfo.h"

CBoss_Scene::CBoss_Scene()
{
}


CBoss_Scene::~CBoss_Scene()
{
	Release();
}

void CBoss_Scene::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Boss.mp3");
	//CImgMgr::Get_Instance()->AddImage(L"Map/Boss.bmp", L"Boss");
	g_iTileX = 130;
	g_iTileY = 68;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::BOSS);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	CObj* pInfo = CAbstractFactory<CWoodInfo>::Create(TEAM_MOUSE);
	static_cast<CWoodInfo*>(pInfo)->Set_Info(L"보리스를 처치하세요~");
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pInfo);
}

int CBoss_Scene::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//스토어로 넘어감
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_FINISH);
		return 0;
	}

	if (0 != m_iMissionState)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	//던전2로 넘어감
		{
			CScrollMgr::Alter_Scroll().x = 0;
			CScrollMgr::Alter_Scroll().y = 0;
			CTileMgr::Get_Instance()->Release();
			if(m_iMissionState ==  1)
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_FINISH);
			if (m_iMissionState == 2)
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
		/*if ((pObj->Get_Team() != TEAM_MOUSE)
			&& (pObj->Get_Team() != TEAM_TILE)
			&& (pObj->Get_Team() != TEAM_1)
			)
		{
			++iEnemyCount;
		}*/
		if ((pObj->Get_Team() == TEAM_2))
		{
			if (dynamic_cast<CBoss*>(pObj))
			{
				++iEnemyCount;
			}
		}
		if ((pObj->Get_Team() == TEAM_1))
		{
			if (dynamic_cast<CPlayer*>(pObj))
			{
				++iPlayerCount;
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
			return 0;
		}
	}
	return 0;
}

void CBoss_Scene::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CBoss_Scene::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Boss");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CBoss_Scene::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Boss");
}

void CBoss_Scene::LateInit()
{
}
