#include "stdafx.h"
#include "MainGame.h"
#include "Mouse.h"
#include "ImgMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	m_hDC = GetDC(g_hWND);

	CImgMgr::Get_Instance()->AddImage(L"ui/mouse.bmp", L"Mouse");
	CImgMgr::Get_Instance()->AddImage(L"ui/Mouse_Attack.bmp", L"Mouse_Attack");
	CImgMgr::Get_Instance()->AddImage(L"Back.bmp", L"Back");
	CImgMgr::Get_Instance()->AddImage(L"BackBuffer.bmp", L"BackBuffer");

	CObj* pObj = CAbstractFactory<CMouse>::Create(TEAM_MOUSE);
	CObjMgr::Get_Instance()->AddObject(OBJID::MOUSE, pObj);

	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOADING);

	srand(unsigned(time(NULL)));

	
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
	CScrollMgr::ScrollLock();
	CScrollMgr::Get_Instance()->LateUpdate();
}

void CMainGame::Render()
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Back");
	HDC hBack = CImgMgr::Get_Instance()->GetImgDC(L"BackBuffer");
	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	SetBkMode(hBack, TRANSPARENT);
	SetTextColor(hBack, RGB(255, 255, 255));
	HFONT hFont = CreateFont(12, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	HFONT saveFont = (HFONT)SelectObject(hBack, hFont);
	
	CSceneMgr::Get_Instance()->Render(hBack);
	CScrollMgr::Get_Instance()->Render(hBack);
	//FrameInfo(hBack);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hBack, saveFont));
}

void CMainGame::Release()
{
	ReleaseDC(g_hWND, m_hDC);
	CObjMgr::Destroy_Instance();
	CImgMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
}

void CMainGame::FrameInfo(HDC _hDC)
{
	static UINT oldTime = GetTickCount();
	static float FrameCount;
	static float Fps = 0;

	int nowTime, delTIme;
	TCHAR szFps[12];
	memset(szFps, 0, sizeof(szFps));

	nowTime = GetTickCount();
	delTIme = nowTime - oldTime;
	++FrameCount;

	if (delTIme > 999)
	{
		FrameCount = (FrameCount * 1000) / delTIme;
		oldTime = nowTime;
		Fps = FrameCount;
		FrameCount = 0;
	}

	TCHAR info[32] = L"";
	swprintf_s(info, L"메인 프레임:  %f", Fps);
	TextOut(_hDC, 0, 0, info, lstrlen(info));
}
