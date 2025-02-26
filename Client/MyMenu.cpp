#include "stdafx.h"
#include "MyMenu.h"
#include "ImgMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Menu.mp3");

	CSceneMgr::g_iNextStage = 0;
	CImgMgr::Get_Instance()->AddImage(L"Menu/Menu.bmp", L"BackGround_Menu");
	CImgMgr::Get_Instance()->AddImage(L"Menu/Edit.bmp", L"Edit");
	CImgMgr::Get_Instance()->AddImage(L"Menu/Exit.bmp", L"Exit");
	CImgMgr::Get_Instance()->AddImage(L"Menu/Start.bmp", L"Start");

	CScrollMgr::ReInitialize();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}

	CObj* pObj = CAbstractFactory<CMyButton>::Create(TEAM_MOUSE,400.f, 404.f);
	dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUUI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(TEAM_MOUSE, 400.f, 479.f);
	dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUUI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(TEAM_MOUSE, 690.f, 50.f);
	dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUUI, pObj);

	CSceneMgr::g_tPlayerUnitInfo = INFO_UNIT(L"·¹°ñ¶ó½º", 80, 550, 300);
	CSceneMgr::g_tPlayerUnitInfo.iHp = 9999;
	CSceneMgr::g_tPlayerUnitInfo.iMaxHp = 9999;
	CSceneMgr::g_tPlayerUnitInfo.iGold = 1000000;	
}

int CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyMenu::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"BackGround_Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MENUUI);
	CImgMgr::Get_Instance()->EraseImgDC(L"BackGround_Menu");
	CImgMgr::Get_Instance()->EraseImgDC(L"Edit");
	CImgMgr::Get_Instance()->EraseImgDC(L"Exit");
	CImgMgr::Get_Instance()->EraseImgDC(L"Start");
}
