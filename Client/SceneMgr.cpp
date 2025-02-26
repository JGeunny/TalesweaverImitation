#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Loading.h"
#include "Logo.h"
#include "MyMenu.h"
#include "MyEdit.h"
#include "Town.h"
#include "Store.h"
#include "Field.h"
#include "Dun1.h"
#include "Dun2.h"
#include "Boss_Scene.h"
#include "BossFinish.h"
#include "Ending.h"
#include "InterFace.h"

#include "PlayerStatus.h"
#include "Inventory.h"
#include "Store_UI.h"
#include "Equip.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

//#include "Stage.h"
IMPLEMENT_SINGLETON(CSceneMgr)
int CSceneMgr::g_iNextStage = 0;
INFO_UNIT CSceneMgr::g_tPlayerUnitInfo = INFO_UNIT(L"플레이어", 80, 80000);
CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID)
{
	// State 패턴 
	//FSM을 기반으로 하는 객체의 상태를 표현 
	/*
	유한 상태 기계는 자신이 취할수 있는 유한한 갯수를 가진다.
	그리고 그중 반드시 하나만 취한다.
	현재 상태는 특정 조건이 되면 다른 상태로 변할 수 있다.

	FSM과 상속과 다형성으로 더욱 확장한 디자인 패턴
	*/
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		SAFE_DELETE(m_pScene);
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOADING:
			m_pScene = new CLoading;
			break;
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case CSceneMgr::SCENE_EDIT:
			m_pScene = new CMyEdit;
			break;
		case CSceneMgr::SCENE_TOWN:
			m_pScene = new CTown;
			break;
		case CSceneMgr::SCENE_STORE:
			m_pScene = new CStore;
			break;
		case CSceneMgr::SCENE_FIELD:
			m_pScene = new CField;
			break;
		case CSceneMgr::SCENE_DUN1:
			m_pScene = new CDun1;
			break;
		case CSceneMgr::SCENE_DUN2:
			m_pScene = new CDun2;
			break;
		case CSceneMgr::SCENE_BOSS:
			m_pScene = new CBoss_Scene;
			break;
		case CSceneMgr::SCENE_FINISH:
			m_pScene = new CBossFinish;
			break;
		case CSceneMgr::SCENE_ENDING:
			m_pScene = new CEnding;
			break;
		case CSceneMgr::SCENE_END:
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
	CInterFace::Get_Instance()->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
	CInterFace::Get_Instance()->LateUpdate();

	
	if (CKeyMgr::Get_Instance()->KeyDown('U'))
	{
		CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::PlayerStatus];
		if (pUI)
		{
			auto& bActivation = pUI->Alter_Activation();
			bActivation = !bActivation;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('I'))
	{
		CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::Inventory];
		if (pUI)
		{
			auto& bActivation = pUI->Alter_Activation();
			bActivation = !bActivation;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('P'))
	{
		CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::Equip];
		if (pUI)
		{
			auto& bActivation = pUI->Alter_Activation();
			bActivation = !bActivation;
		}
	}
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
	CInterFace::Get_Instance()->Render(hDC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
	CInterFace::Destroy_Instance();
}
