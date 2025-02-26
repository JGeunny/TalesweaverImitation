#include "stdafx.h"
#include "MyButton.h"
#include "ImgMgr.h"

#include "SceneMgr.h"
#include "SoundMgr.h"
CMyButton::CMyButton()
	: m_iDrawID(1)
	, m_bButtonOver(false)
{
}

CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_pFrameKey = nullptr;
	m_tDraw.fcx = 115.f;
	m_tDraw.fcy = 24.f;
	m_iDrawID = 0;
}

int CMyButton::Update()
{
	CObj::LateInit();
	return 0;
}

void CMyButton::LateUpdate()
{
	// 여기서 나중에 씬 체인지 할꺼임 
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (PtInRect(&m_tDraw.Get_Rect(), pt))
	{
		if (!m_bButtonOver)
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"BtnOver.wav", CSoundMgr::CHANNELID::UI);
		}
		
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"BtnClick.wav", CSoundMgr::CHANNELID::UI);
			if (!lstrcmp(m_pFrameKey, L"Start"))
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_TOWN);
				return;
			}
			else if (!lstrcmp(m_pFrameKey, L"Exit"))
			{
				DestroyWindow(g_hWND);
			}
			if (!lstrcmp(m_pFrameKey, L"Edit"))
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
				return;
			}
		}
		m_iDrawID = 0;
		m_bButtonOver = true;
	}
	else
	{
		m_iDrawID = 1;
		m_bButtonOver = true;
	}
		
}

void CMyButton::Render(HDC hDC)
{
	RECT rt = m_tDraw.Get_Rect();
	HDC MemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);

	if (!lstrcmp(m_pFrameKey, L"Edit"))
	{
		m_iDrawID = (m_iDrawID == 0) ? 1 : 0;
	}
	GdiTransparentBlt(hDC,
		rt.left, rt.top,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy,
		MemDC,
		(int)m_tDraw.fcx * m_iDrawID, 0,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy,
		RGB(255, 255, 255));
}

void CMyButton::Release()
{
}

void CMyButton::LateInit()
{
	if (!lstrcmp(m_pFrameKey, L"Edit"))
	{
		m_tDraw.fcx = 100.f;
		m_tDraw.fcy = 50.f;
	}
}
 