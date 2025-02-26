#include "stdafx.h"
#include "TurretB.h"
#include "ImgMgr.h"
#include "Explosion.h"
#include "ObjMgrBuffer.h"

#include "SoundMgr.h"

CTurretB::CTurretB()
{
}


CTurretB::~CTurretB()
{
}

void CTurretB::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Boss/Rocket/Red_Bomb_Explosion_Effect.bmp", L"Red_Bomb_Explosion_Effect");
	//CImgMgr::Get_Instance()->AddImage(L"Boss/Rocket/Rocket.bmp", L"Rocket");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Rocket/Cannon.bmp", L"Cannon");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Rocket/TurretB_gg.bmp", L"TurretB_gg");

	m_pFrameKey = L"Cannon";
	//πÃªÁ¿œ ≈Õ∑ø
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tDraw.fcx = 200;
	m_tDraw.fcy = 200;

	m_fRecogDist = 400;

	m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();
}

int CTurretB::Update()
{
	CObj::LateInit();
	if (m_bObjState[UNIT_STATEID::DEAD])
		return OBJ_DEAD;
	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		if (m_bExplosion)
		{
			CObj* pExplosion = CAbstractFactory<CExplosion>::Create(TEAM_MOUSE, m_tDraw.fx, m_tDraw.fy);
			CObjMgrBuffer::Get_Instance()->Get_List()[OBJID::EFFECT].emplace_back(pExplosion);
			m_bExplosion = false;
		}
		return OBJ_NOEVENT;
	}
	m_bExplosion = true;

	DWORD m_dwNowTime = GetTickCount();
	if (m_pTarget)
	{
		if (m_pTarget->Get_Team() == m_iTeam)
		{
			Set_Target(nullptr);
			return OBJ_NOEVENT;
		}
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);

		if (fDist <= m_fRecogDist)
		{
			m_eNextState = UNIT_STATEID::ATTACK;
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 500 < m_dwNowTime)
				{
					CSoundMgr::Get_Instance()->MyPlaySound(L"dragbull.wav", CSoundMgr::CHANNELID::EFFECT);
					m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();
					CObj* pBullet = CAbstractFactory<CBullet>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1);
					auto& tDraw = static_cast<CBullet*>(pBullet)->Alter_Draw();
					tDraw.fx = m_tDraw.fx;
					tDraw.fy = m_tDraw.fy - 80;
					tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
					pBullet->Set_Target(m_pTarget);
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH, pBullet);
				}
			}
		}
		else
		{
			m_eNextState = UNIT_STATEID::IDLE;
		}

	}
	return 0;
}

void CTurretB::LateUpdate()
{
	CTurretB::MoveFrame();
	CUnit::FSM();
}

void CTurretB::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	RECT tRect = tDraw.Get_Rect();

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"TurretB_gg");
		GdiTransparentBlt(hDC, tRect.left, tRect.top,
			(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
			(int)0,
			(int)0,
			(int)96, (int)66,
			RGB(255, 255, 255));
	}
	else
	{
		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
		GdiTransparentBlt(hDC, tRect.left, tRect.top,
			(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
			(int)192 * m_tFrame.iFrameStart,
			(int)170 * m_tFrame.iFrameScene,
			(int)192, (int)170,
			RGB(0, 0, 0));
	}

	//Rectangle(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
}

void CTurretB::Release()
{
}

void CTurretB::MoveFrame()
{
	if (m_eCurState == UNIT_STATEID::ATTACK)
	{	
		m_iFrameDir = 1;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart += m_iFrameDir;
				m_tFrame.dwFrameTime = GetTickCount();
			}
		}
	}
	else
	{
		m_iFrameDir = -1;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			if (m_tFrame.iFrameStart > 0)
			{
				m_tFrame.iFrameStart += m_iFrameDir;
				m_tFrame.dwFrameTime = GetTickCount();
			}
		}
	}
}
