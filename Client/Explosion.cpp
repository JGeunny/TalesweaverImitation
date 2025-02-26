#include "stdafx.h"
#include "Explosion.h"
#include "ImgMgr.h"
#include "SoundMgr.h"

CExplosion::CExplosion()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"pscdth00.wav",CSoundMgr::CHANNELID::EXPLO);
}


CExplosion::~CExplosion()
{
}

void CExplosion::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Effect/Explosion.bmp", L"Explosion");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);

	//Crash를 위한 애니메
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CExplosion::Update()
{
	if (m_tFrame.iFrameScene >= 4 && m_tFrame.iFrameStart >= 4)
		m_bObjState[OBJ_STATEID::DEAD] = true;
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();
	return OBJ_NOEVENT;
}

void CExplosion::LateUpdate()
{
	CExplosion::MoveFrame();
}

void CExplosion::Render(HDC hDC)
{
	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Explosion");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
		64 * m_tFrame.iFrameStart,
		64 * m_tFrame.iFrameScene,
		64, 64,
		RGB(255, 0, 255));
}

void CExplosion::Release()
{
}

void CExplosion::LateInit()
{
	m_tDraw.fcx = 128;
	m_tDraw.fcy = 128; 
}

void CExplosion::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		++m_tFrame.iFrameScene;
		m_tFrame.iFrameStart = 0;
	}
	if (m_tFrame.iFrameScene > 4)
	{
		m_tFrame.iFrameScene = 0;
	}
}
