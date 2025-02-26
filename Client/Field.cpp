#include "stdafx.h"
#include "Field.h"
#include "ObjMgr.h"
#include "ObjMgrBuffer.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "MissionClear.h"
#include "Player.h"

#include "SceneMgr.h"

#include "AbstractFactory.h"
#include "Slime.h"

#include "SoundMgr.h"

#include "WoodInfo.h"

CField::CField()
	:m_iMissionState(0)
{
}


CField::~CField()
{
	Release();
}

void CField::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Field.wav");
	//CImgMgr::Get_Instance()->AddImage(L"Map/Field.bmp", L"Field");
	g_iTileX = 106;
	g_iTileY = 56;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::FIELD);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	CObj* pSlimeKing = CAbstractFactory<CSlime>::Create_Unit(TEAM_2,500, 500, 0, L"슬라임 킹", 120, 5000,0,1, 1000);
	POINTFLOAT ptSize = {200,200};
	POINTFLOAT ptImageSize = { 1000,1000 };
	static_cast<CSlime*>(pSlimeKing)->Set_Size(ptSize, ptImageSize);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT, pSlimeKing);


	CObj* pInfo = CAbstractFactory<CWoodInfo>::Create(TEAM_MOUSE);
	static_cast<CWoodInfo*>(pInfo)->Set_Info(L"모든 슬라임을 처치하세요~");
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pInfo);
}

int CField::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//던전1로 넘어감
	{ 
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_DUN1);
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
		if ((pObj->Get_Team() != TEAM_MOUSE)
			&& (pObj->Get_Team() != TEAM_TILE)
			&& (pObj->Get_Team() != TEAM_1)
			)
		{
			++iEnemyCount;
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
			CSceneMgr::g_iNextStage = 1;
			return 0;
		}
	}
	return 0;
}

void CField::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();

}

void CField::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Field");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CField::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Field");
}

void CField::LateInit()
{
}
