#include "stdafx.h"
#include "BeAttacked.h"

#include "ImgMgr.h"

#include "SoundMgr.h"

CBeAttacked::CBeAttacked()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"Hit.mp3", CSoundMgr::CHANNELID::HIT);
}


CBeAttacked::~CBeAttacked()
{
	Release();
}

void CBeAttacked::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Effect/DmgFont.bmp", L"DmgFont");
	//CImgMgr::Get_Instance()->AddImage(L"Effect/Crash.bmp", L"Crash");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 300;
	m_tDraw.fSpeed = 5;

	//Crash를 위한 애니메
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();
	m_fDist = 0;
}

int CBeAttacked::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	m_tDraw.fy -= m_tDraw.fSpeed;
	m_fDist += m_tDraw.fSpeed;
	return OBJ_NOEVENT;
}

void CBeAttacked::LateUpdate()
{
	CObj::MoveFrame();
}

void CBeAttacked::Render(HDC hDC)
{
	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"DmgFont");

	char szAtt[100];
	_itoa_s(m_iAtt, szAtt, 10);
	for (int i = 0; i < m_iNumCount; ++i)
	{
		int iAttNum = szAtt[i] - 48;
		GdiTransparentBlt(hDC, int(tRect.left + i*m_tDraw.fcx - m_iNumCount * m_tDraw.fcx * 0.5), tRect.top,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
			(int)m_tDraw.fcx * iAttNum, 0,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			RGB(0, 0, 0));
	}

	INFO_DRAW tDraw = m_tDraw;
	tDraw.fy += m_fDist;
	tDraw.fcx = 127;
	tDraw.fcy = 123;
	tRect = tDraw.Get_Rect();
	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Crash");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		0,
		127, 123,
		RGB(255, 0, 255));
}

void CBeAttacked::Release()
{
}

void CBeAttacked::LateInit()
{
	m_iNumCount = int(log10(m_iAtt)) + 1;
	m_tDraw.fcx = 23;
	m_tDraw.fcy = 30;

}
