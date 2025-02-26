#include "stdafx.h"
#include "Turret.h"

#include "Explosion.h"
#include "ImgMgr.h"
#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"

#include "SoundMgr.h"

CTurret::CTurret()
	:m_bExplosion(false)
{
}


CTurret::~CTurret()
{
}

void CTurret::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/MachineGunTurret.bmp", L"MachineGunTurret");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/MissileTurret.bmp", L"MissileTurret");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/GrenadeTurret.bmp", L"GrenadeTurret");

	m_pFrameKey = L"MachineGunTurret";
	//∏”Ω≈∞« ≈Õ∑ø
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tDraw.fcx = 60;
	m_tDraw.fcy = 85;

	m_fRecogDist = 1500;
}

int CTurret::Update()
{
	if (m_bObjState[UNIT_STATEID::DEAD])
		return OBJ_DEAD;
	if (m_pMaster == nullptr)
	{
		m_bObjState[UNIT_STATEID::DEAD] = true;
		return OBJ_NOEVENT;
	}
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
	
	CObj::LateInit();

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
		if (m_tFrame.iFrameStart == 2)
		{
			if (m_dwObjTime[OBJ_TIMEID::SKILL] + m_tFrame.dwFrameSpeed < m_dwNowTime)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"blastcan8.wav", CSoundMgr::CHANNELID::EFFECT);
				m_tDraw.fx += 20;
				CObj* pBullet = CAbstractFactory<CBullet>::Create_Skill(this, 30, L"@", 60, 1);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH, pBullet);
				pBullet->Alter_Draw().fcx = 15;
				pBullet->Alter_Draw().fcy = 15;
				m_tDraw.fx -= 40;
				pBullet = CAbstractFactory<CBullet>::Create_Skill(this, 30, L"@", 60, 1);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH, pBullet);
				pBullet->Alter_Draw().fcx = 15;
				pBullet->Alter_Draw().fcy = 15;
				m_tDraw.fx += 20;

				m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
				m_eNextState = UNIT_STATEID::ATTACK;
			}
		}
	}
	return OBJ_NOEVENT;
}

void CTurret::LateUpdate()
{
	CObj::MoveFrame();
}

void CTurret::Render(HDC hDC)
{
	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		m_tFrame.iFrameStart = 6;
	}
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 60;
	tDraw.fcy = 85;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 0, 255));

	//Rectangle(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
}

void CTurret::Release()
{
}
