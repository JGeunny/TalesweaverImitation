#include "stdafx.h"
#include "BossFinish.h"
#include "ObjMgr.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "InterFace.h"
#include "AbstractFactory.h"
#include "AircraftCarrier.h"
#include "Turret.h"
#include "BossInfo.h"

#include "ObjMgrBuffer.h"
#include "MissionClear.h"
#include "Player.h"
#include "Circle.h"

#include "SoundMgr.h"

#include "WoodInfo.h"

CBossFinish::CBossFinish()
	:m_dwBackGroundX(0)
	, m_iMissionState(0)
{
}


CBossFinish::~CBossFinish()
{
	Release();
}

void CBossFinish::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Boss.mp3");
	//CImgMgr::Get_Instance()->AddImage(L"Map/FinishStage.bmp", L"FinishStage");
	//CImgMgr::Get_Instance()->AddImage(L"Map/FinishStageBackGround.bmp", L"FinishStageBackGround");
	CScrollMgr::Set_HorizontalScroll(true);
	g_iTileX = 50;
	g_iTileY = 22;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::FINISH);
	CTileMgr::Get_Instance()->Hide();
	
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	CObj* pObj = CAbstractFactory<CAircraftCarrier>::Create_Unit(TEAM_2, 900, 75, 0, L"적 비행선", 80, 92000);
	CObjMgr::Get_Instance()->AddObject(OBJID::UNIT, pObj);
	auto& listObj = *CObjMgr::Get_Instance()->Get_List(OBJID::UI);
	for (auto& pUI : listObj)
	{
		if (dynamic_cast<CBossInfo*>(pUI))
			static_cast<CBossInfo*>(pUI)->Set_Target(pObj);
	}
	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, 200, 300);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::SLIME);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);
	
	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, 200, 400);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);
	
	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, 200, 500);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, 100, 350);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_1, 100, 450);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);



	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, 1300, 300);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::SLIME);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, 1300, 400);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, 1300, 500);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::MONSTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, 1400, 350);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	pObj = CAbstractFactory<CCircle>::Create(TEAM_2, 1400, 450);
	static_cast<CCircle*>(pObj)->Set_MonsterID(CCircle::HUNTER);
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::CIRCLE, pObj);

	//화면 밖으로 나갔을 경우 몬스터들을 잡아오기 위한 랙트
	m_tDrawGround.fx = 750;
	m_tDrawGround.fy = 430;
	m_tDrawGround.fcx = 1500;
	m_tDrawGround.fcy = 420;

	CObj* pInfo = CAbstractFactory<CWoodInfo>::Create(TEAM_MOUSE);
	static_cast<CWoodInfo*>(pInfo)->Set_Info(L"비행선을 파괴하세요~");
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pInfo);
}

int CBossFinish::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	CObjMgr::Get_Instance()->RecogDistAllID(OBJID::UNIT);

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_ENDING);
	}
	if (0 != m_iMissionState)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	
		{
			CScrollMgr::Alter_Scroll().x = 0;
			CScrollMgr::Alter_Scroll().y = 0;
			CTileMgr::Get_Instance()->Release();
			if (m_iMissionState == 1)
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_ENDING);
			if (m_iMissionState == 2)
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_TOWN);
			return 0;
		}
	}

	//보스가 죽었는지 확인 후 죽었으면 게임 클리어를 띄워줌~
	int iPlayerCount = 0;
	int iEnemyCount = 1;
	auto& listUnit = *CObjMgr::Get_Instance()->Get_List(OBJID::UNIT);
	for (auto& pObj : listUnit)
	{
		if (dynamic_cast<CAircraftCarrier*>(pObj))
		{
			if (pObj->Get_Dead())
			{
				iEnemyCount = 0;
			}
		}
		if (dynamic_cast<CPlayer*>(pObj))
		{
			++iPlayerCount;
		}
	}
	if (0 == m_iMissionState)
	{
		if (0 == iPlayerCount)
		{
			CObj* pUI = CAbstractFactory<CMissionClear>::Create(TEAM_MOUSE, 0, 0);
			static_cast<CMissionClear*>(pUI)->Set_ClearImage(false);
			CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UI, pUI);
			m_iMissionState = 2;
			return 0;
		}
		if (0 == iEnemyCount)
		{
			CObj* pUI = CAbstractFactory<CMissionClear>::Create(TEAM_MOUSE, 0, 0);
			CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UI, pUI);
			m_iMissionState = 1;
			return 0;
		}
	}
	return 0;
}

void CBossFinish::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
	CBossFinish::CatchUnitInField();
}

void CBossFinish::Render(HDC hDC)
{
	/*POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"FinishStageBackGround");
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, pt.x/2, 0, WINCX, WINCY, SRCCOPY);
	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"FinishStage");


	GdiTransparentBlt(hDC, 0, (int)pt.y - 60, WINCX, WINCY + 120, hMemDC, -(int)pt.x, 0, WINCX, WINCY + 120, RGB(255, 0, 255));

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);*/

	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	if (m_dwBackGroundX > 1900 + 1900/2)
		m_dwBackGroundX = 0;
	
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"FinishStageBackGround");
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_dwBackGroundX, 0, WINCX, WINCY, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -1900 + m_dwBackGroundX, 0, WINCX, WINCY, SRCCOPY);
	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"FinishStage");


	GdiTransparentBlt(hDC, 0, (int)pt.y - 60, WINCX, WINCY + 120, hMemDC, -(int)pt.x, 0, WINCX, WINCY + 120, RGB(255,0,255));

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);


	/*INFO_DRAW tTrigger = m_tDrawGround;
	tTrigger.fx += (int)pt.x;
	tTrigger.fy += (int)pt.y;
	RECT rt = tTrigger.Get_Rect();
	Rectangle(hDC, rt.left, rt.top , rt.right, rt.bottom);*/

	m_dwBackGroundX += 3;
}

void CBossFinish::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"FinishStage");
}

void CBossFinish::LateInit()
{
}

void CBossFinish::CatchUnitInField()
{
	//m_tDrawGround
	RECT rt;
	auto& listUnit = *CObjMgr::Get_Instance()->Get_List(OBJID::UNIT);
	for (auto& pUnit : listUnit)
	{
		if (dynamic_cast<CAircraftCarrier*>(pUnit)) continue;
		if (dynamic_cast<CTurret*>(pUnit)) continue;
		INFO_DRAW tDraw =  pUnit->Get_Info();
		if (false == IntersectRect(&rt, &m_tDrawGround.Get_Rect(), &tDraw.Get_Rect()))
		{
			//맵 밖으로 튕겨 나갔을 경우 플레이어일 경우 맵 중앙으로 오고 나머지는 죽임
			if (dynamic_cast<CPlayer*>(pUnit))
			{
				tDraw.fx = m_tDrawGround.fx;
				tDraw.fy = m_tDrawGround.fy;
				pUnit->Set_Info(tDraw);
			}
			else
			{
				pUnit->Set_Dead(true);
			}
		}
	}
}
