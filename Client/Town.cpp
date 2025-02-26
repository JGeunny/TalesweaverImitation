#include "stdafx.h"
#include "Town.h"
#include "ObjMgr.h"
#include "ObjMgrBuffer.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "InterFace.h"
#include "MissionClear.h"
#include "Player.h"
#include "NPC.h"
#include "Circle.h"
#include "SceneMgr.h"

#include "TurretB.h"
#include "AbstractFactory.h"

#include "SoundMgr.h"

#include "Pet.h"

CTown::CTown()
	:m_pSelectPlayer(nullptr)
{
}


CTown::~CTown()
{
	Release();
}

void CTown::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Town.wav");

	CScrollMgr::ReInitialize();
	//CImgMgr::Get_Instance()->AddImage(L"Map/Town.bmp", L"Town");
	g_iTileX = 53;
	g_iTileY = 40;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::TOWN);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	
	CObjMgr::Get_Instance()->Initialize();
	
	m_pSelectPlayer = new CPlayer;// 플레이어를 찾음
	auto& listObj = *CObjMgr::Get_Instance()->Get_List(OBJID::UNIT);
	for (auto& pUnit : listObj)
	{
		pUnit->Set_Team(TEAM_1);

		if (dynamic_cast<CPlayer*>(pUnit))
		{
			m_pSelectPlayer->Set_Target(pUnit);
		}	
	}

	CObj* pNpc = CAbstractFactory<CNPC>::Create_Unit(TEAM_1, 1100, 530, 0, L"리디아", 100, 8000);
	pNpc->Set_Target(m_pSelectPlayer->Get_Target());
	CObjMgrBuffer::Get_Instance()->
		AddObject(OBJID::ID::BUILDING, pNpc);

/*	CObjMgrBuffer::Get_Instance()->
	AddObject(OBJID::ID::BUILDING, CAbstractFactory<CTurretB>::Create_Unit(TEAM_2, 500, 500, 0, L"포토캐논", 100, 8000));*/

	/*CObj* pObj =  CAbstractFactory<CPet>::Create_Unit(TEAM_2, 500, 500, 0, L"커비", 100, 8000);
	pObj->Set_Master(m_pSelectPlayer->Get_Target());
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::ID::UNIT, pObj);*/

	// 다음 스테이지에 가기 위한 영역
	m_tNextStage.fx = 1500;
	m_tNextStage.fy = 200;
	m_tNextStage.fcx = 100;
	m_tNextStage.fcy = 100;
	
	// 상점에 가기위한 영역
	m_tStore.fx = 400;
	m_tStore.fy = 400;
	m_tStore.fcx = 100;
	m_tStore.fcy = 100;
}

int CTown::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//스토어로 넘어감
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STORE);
		return 0;
	}

	if (m_pSelectPlayer)
	{
		CObj* pPlayer = m_pSelectPlayer->Get_Target();
		if (pPlayer)
		{
			if (IntersectRect(&RECT(), pPlayer->Get_Rect(), &m_tStore.Get_Rect()))
			{
				CScrollMgr::Alter_Scroll().x = 0;
				CScrollMgr::Alter_Scroll().y = 0;
				CTileMgr::Get_Instance()->Release();
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STORE);
				return 0;
			}
			if (IntersectRect(&RECT(), pPlayer->Get_Rect(), &m_tNextStage.Get_Rect()))
			{
				CScrollMgr::Alter_Scroll().x = 0;
				CScrollMgr::Alter_Scroll().y = 0;
				CTileMgr::Get_Instance()->Release();

				CSceneMgr::SCENEID eSelectScene;
				switch(CSceneMgr::g_iNextStage)
				{
				case 1:
					eSelectScene = CSceneMgr::SCENE_DUN1;
					break;
				case 2:
					eSelectScene = CSceneMgr::SCENE_BOSS;
					break;
				default:
					eSelectScene = CSceneMgr::SCENE_FIELD;
					break;
				}
				CSceneMgr::Get_Instance()->SceneChange(eSelectScene);
				return 0;
			}
		}
	}
	return 0;
}

void CTown::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CTown::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Town");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	/*INFO_DRAW tTrigger = m_tStore;
	tTrigger.fx += (int)pt.x;
	tTrigger.fy += (int)pt.y;
	RECT rt = tTrigger.Get_Rect();
	Rectangle(hDC, rt.left, rt.top , rt.right, rt.bottom);*/
}

void CTown::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Town");
	SAFE_DELETE(m_pSelectPlayer);
}

void CTown::LateInit()
{
}