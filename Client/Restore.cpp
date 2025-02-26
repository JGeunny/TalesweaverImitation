#include "stdafx.h"
#include "Restore.h"
#include "ImgMgr.h"
#include "SoundMgr.h"

CRestore::CRestore()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"potion.wav", CSoundMgr::CHANNELID::EFFECT);
}


CRestore::~CRestore()
{
}


void CRestore::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Effect/HpPotion.bmp", L"HpPotion");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);
	//m_iObjTimeCount[OBJ_TIMEID::LIVE] = 300;
	m_tDraw.fSpeed = 5;
	m_tDraw.fcx = 128;
	m_tDraw.fcy = 128;

	//Crash를 위한 애니메
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameTime = GetTickCount();
	m_fDist = 0;
}

int CRestore::Update()
{
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_bObjState[OBJ_STATEID::DEAD] = true;
	}
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	/*m_tDraw.fy -= 2;
	m_fDist += 2;*/
	return OBJ_NOEVENT;
}

void CRestore::LateUpdate()
{
	CObj::MoveFrame();
}

void CRestore::Render(HDC hDC)
{
	RECT tRect = m_tDraw.Get_Rect();
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fy += m_fDist;
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"HpPotion");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		128 * m_tFrame.iFrameStart,
		0,
		128, 128,
		RGB(255, 255, 255));
}

void CRestore::Release()
{
}

void CRestore::LateInit()
{
}
