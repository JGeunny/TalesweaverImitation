#include "stdafx.h"
#include "GrenadeTurret.h"
#include "ImgMgr.h"

#include "Bomb.h"
#include "Explosion.h"
#include "ImgMgr.h"
#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"

#include "SoundMgr.h"

CGrenadeTurret::CGrenadeTurret()
{
}


CGrenadeTurret::~CGrenadeTurret()
{
	Release();
}

void CGrenadeTurret::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/MachineGunTurret.bmp", L"MachineGunTurret");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/MissileTurret.bmp", L"MissileTurret");
	CImgMgr::Get_Instance()->AddImage(L"Boss/Turret/GrenadeTurret.bmp", L"GrenadeTurret");

	m_pFrameKey = L"GrenadeTurret";
	//¼ö·ùÅº ÅÍ·¿
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tDraw.fcx = 99;
	m_tDraw.fcy = 100;

	m_fRecogDist = 1500;
}

int CGrenadeTurret::Update()
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
		if (m_tFrame.iFrameStart == 10)
		{
			if (m_dwObjTime[OBJ_TIMEID::SKILL] + m_tFrame.dwFrameSpeed < m_dwNowTime)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"gadiattack.wav",CSoundMgr::CHANNELID::EFFECT);
				CObj* pBomb = CAbstractFactory<CBomb>::Create_Skill(this, 30, L"@", 60, 1);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL, pBomb);
				/*m_tDraw.fx += 20;
				CObj* pBullet = CAbstractFactory<CBullet>::Create_Skill(this, 30, L"@", 60, 1);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH, pBullet);
				pBullet->Alter_Draw().fcx = 15;
				pBullet->Alter_Draw().fcy = 15;
				m_tDraw.fx -= 40;
				pBullet = CAbstractFactory<CBullet>::Create_Skill(this, 30, L"@", 60, 1);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH, pBullet);
				pBullet->Alter_Draw().fcx = 15;
				pBullet->Alter_Draw().fcy = 15;
				m_tDraw.fx += 20;*/

				m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
				m_eNextState = UNIT_STATEID::ATTACK;
			}
		}
	}
	return OBJ_NOEVENT;
}

void CGrenadeTurret::LateUpdate()
{
	CObj::MoveFrame();
}

void CGrenadeTurret::Render(HDC hDC)
{
	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		m_tFrame.iFrameStart = 11;
	}
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 99;
	tDraw.fcy = 100;
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

void CGrenadeTurret::Release()
{
}
