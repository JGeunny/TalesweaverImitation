#include "stdafx.h"
#include "Logo.h"
#include "ImgMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"wild.mp3");
	m_dwNextTime = GetTickCount();
	m_iNextLogo = 0;
	m_iNextMaxTime = 80;
	//CImgMgr::Get_Instance()->AddImage(L"Logo/MyLogo.bmp", L"Logo");
}

int CLogo::Update()
{
	return 0;
}

void CLogo::LateUpdate()
{
	if (m_iNextLogo > 50)
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0 + WINCX * m_iNextLogo, 0, SRCCOPY);

	int iNextMaxTime = m_iNextMaxTime;
	if (m_iNextLogo < 2)
		iNextMaxTime = 1500;
	if (m_dwNextTime + iNextMaxTime < GetTickCount())
	{
		++m_iNextLogo;
		m_dwNextTime = GetTickCount();
	}
}

void CLogo::Release()
{
	CImgMgr::Get_Instance()->EraseImgDC(L"Logo");
}
