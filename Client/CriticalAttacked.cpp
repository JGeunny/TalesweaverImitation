#include "stdafx.h"
#include "CriticalAttacked.h"

#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CCriticalAttacked::CCriticalAttacked()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"Hit.wav", CSoundMgr::CHANNELID::HIT);
	CScrollMgr::Get_Instance()->DoShackIt();
}


CCriticalAttacked::~CCriticalAttacked() 
{
	Release();
}

void CCriticalAttacked::Initialize()
{
	CBeAttacked::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 300;
	m_tDraw.fSpeed = 8;
}

int CCriticalAttacked::Update()
{
	return CBeAttacked::Update();
}

void CCriticalAttacked::LateUpdate()
{
	CBeAttacked::LateUpdate();
}

void CCriticalAttacked::Render(HDC hDC)
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
			23 * iAttNum, 0,
			23, 30,
			RGB(0, 0, 0));
	}

	INFO_DRAW tDraw = m_tDraw;
	tDraw.fy += m_fDist;
	tDraw.fcx = 127;
	tDraw.fcy = 123;
	tRect = tDraw.Get_Rect();
	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Crash2");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		0,
		127, 123,
		RGB(255, 255, 255));
}

void CCriticalAttacked::Release()
{
	CBeAttacked::Release();
}

void CCriticalAttacked::LateInit()
{
	m_iNumCount = int(log10(m_iAtt)) + 1;
	m_tDraw.fcx = 43;
	m_tDraw.fcy = 50;
}
