#include "stdafx.h"
#include "Score.h"

#include "ImgMgr.h"
#include "Player.h"


CScore::CScore()
{
}


CScore::~CScore()
{
	Release();
}

void CScore::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Effect/DmgFont.bmp", L"DmgFont");
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);
	m_tDraw.fSpeed = 5;
	m_fDist = 0;
}

int CScore::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	m_iScore = 0;
	if (m_pTarget)
	{
		if (dynamic_cast<CPlayer*>(m_pTarget))
		{
			INFO_UNIT tUnit = static_cast<CPlayer*>(m_pTarget)->Get_Unit();
			m_iScore = tUnit.iGold;
			m_iNumCount = int(log10(m_iScore)) + 1;
		}
	}

	m_tDraw.fy -= m_tDraw.fSpeed;
	m_fDist += m_tDraw.fSpeed;
	return OBJ_NOEVENT;
}

void CScore::LateUpdate()
{
	CObj::MoveFrame();
}

void CScore::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;

	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"DmgFont");

	char szScore[10000];
	_itoa_s(m_iScore, szScore, 10);
	for (int i = 0; i < m_iNumCount; ++i)
	{
		int iScoreNum = szScore[i] - 48;
		GdiTransparentBlt(hDC, int(WINCX * 0.5 + i*m_tDraw.fcx - m_iNumCount * m_tDraw.fcx * 0.5), (int)m_tDraw.fcy,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
			(int)m_tDraw.fcx * iScoreNum, 0,
			(int)m_tDraw.fcx, (int)m_tDraw.fcy,
			RGB(0, 0, 0));
	}
}

void CScore::Release()
{
}

void CScore::LateInit()
{
	m_iNumCount = int(log10(m_iScore)) + 1;
	m_tDraw.fcx = 23;
	m_tDraw.fcy = 30;
}
