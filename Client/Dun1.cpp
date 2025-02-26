#include "stdafx.h"
#include "Dun1.h"
#include "ObjMgr.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "ObjMgrBuffer.h"
#include "MissionClear.h"
#include "Player.h"

#include "SoundMgr.h"

#include "WoodInfo.h"
CDun1::CDun1()
	:m_iMissionState(0)
{
}


CDun1::~CDun1()
{
	Release();
}

void CDun1::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Dun.mp3");
	//CImgMgr::Get_Instance()->AddImage(L"Map/Dun1.bmp", L"Dun1");
	g_iTileX = 83;
	g_iTileY = 43;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::DUN1);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	CObj* pInfo = CAbstractFactory<CWoodInfo>::Create(TEAM_MOUSE);
	static_cast<CWoodInfo*>(pInfo)->Set_Info(L"��� ���� óġ�ϼ���~");
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pInfo);
}

int CDun1::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//����2�� �Ѿ
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_DUN2);
		return 0;
	}

	if (0 != m_iMissionState)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	//����2�� �Ѿ
		{
			CScrollMgr::Alter_Scroll().x = 0;
			CScrollMgr::Alter_Scroll().y = 0;
			CTileMgr::Get_Instance()->Release();
			if(m_iMissionState == 1)
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_DUN2);
			if (m_iMissionState == 2)
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_TOWN);
			return 0;
		}
	}
	//�� ������ ���� ��� �̼� Ŭ����
	//�÷��̾ ���� ��� �̼� ����
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
		//�÷��̾ ���� ��� �̼� ����
		if (iPlayerCount == 0)
		{
			CObj* pUI = CAbstractFactory<CMissionClear>::Create(TEAM_MOUSE, 0, 0);
			static_cast<CMissionClear*>(pUI)->Set_ClearImage(false);
			CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UI, pUI);
			m_iMissionState = 2;
			return 0;
		}
		//���� ���� ��� �̼� Ŭ����
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

void CDun1::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CDun1::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Dun1");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CDun1::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Dun1");
}

void CDun1::LateInit()
{
}
