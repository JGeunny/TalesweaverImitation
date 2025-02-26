#include "stdafx.h"
#include "Boss.h"
#include "Wield.h"
#include "Bullet.h"
#include "BounceBullet.h"
#include "Shield.h"
#include "ImgMgr.h"
#include "Bow.h"

#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"

#include "SoundMgr.h"
CBoss::CBoss()
	:m_iFrameScene(0)
	, m_bSpeed(false)
	, m_bClone(false)
	, m_bCloneDie(false)
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	CUnit::Initialize();
	m_fRecogDist = 2000;
	m_tDraw.fSpeed = 7;
	m_fSliding = 13;
	m_fSpeedBuf = m_tDraw.fSpeed;

	m_dwSlidingTime = GetTickCount();
	m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwSlidingTime;

	m_dwSpeed = m_dwSlidingTime;

	m_eCurState = UNIT_STATEID::END;
	m_eNextState = UNIT_STATEID::IDLE;
//	CImgMgr::Get_Instance()->AddImage(L"Monster/Boss_Boris.bmp", L"Boss_Boris");

	m_tDraw.fcx = 50.f;
	m_tDraw.fcy = 80.f;
	//220 * 220

	INFO_UNIT tUnit(L"타노스", 250, 16000, 0, 1, 9999);
	m_tUnit = tUnit;
}

int CBoss::Update()
{
	if (m_bUnit_State[UNIT_STATEID::DEAD])
		return OBJ_DEAD;

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		if (!m_bDeadSound)
		{
			m_bDeadSound = true;
			CSoundMgr::Get_Instance()->MyPlaySound(L"death1.wav", CSoundMgr::CHANNELID::EFFECT);
		}
		m_eNextState = UNIT_STATEID::DEAD;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bUnit_State[UNIT_STATEID::DEAD] = true;
		return OBJ_NOEVENT;
	}
	CObj::LateInit();

	DWORD dwNowTime = GetTickCount();

	if (m_bSpeed)
	{
		if (m_dwSpeed + 5000 < dwNowTime)
		{
			m_tDraw.fSpeed = m_fSpeedBuf;
			m_bSpeed = false;
		}
	}

	//타겟을 따라가는 부분
	if (m_pTarget)
	{
		if (false == m_bCloneDie && true == m_bClone && m_bUnit_State[UNIT_STATEID::BEATTACKED])
		{
			if (m_dwDieTime + 1000 < dwNowTime)
			{
				m_bCloneDie = true;
				for (auto& pClone : m_listObjMySlaves)
				{
					if(pClone)
						pClone->Set_Dead(true);
				}
			}
		}
		if (false == m_bClone && m_tUnit.iHp < m_tUnit.iMaxHp*0.5)
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"SummonPatternEnd.wav", CSoundMgr::CHANNELID::EFFECT);

			m_dwDieTime = dwNowTime;
			m_bClone = true;
			float fAngle = 0;
			POINTFLOAT pt = { 0,0 };
			CObj* pCloneBoss = nullptr;

			INFO_DRAW tDrawPlayer = m_pTarget->Alter_Draw();
			tDrawPlayer.fSpeed = 300;
			tDrawPlayer.fAngle = fAngle;
			pt = tDrawPlayer.Get_Speed();
			m_tDraw.fx = tDrawPlayer.fx + pt.x;
			m_tDraw.fy = tDrawPlayer.fy + pt.y;
			fAngle += 30;

			INFO_UNIT tUnit = m_tUnit;
			tUnit.iGold = 0;
			tUnit.iMaxExp = 0;
			for (; fAngle < 360; fAngle += 30)
			{
				tDrawPlayer = m_pTarget->Alter_Draw();
				tDrawPlayer.fSpeed = 300;
				tDrawPlayer.fAngle = fAngle;
				pt = tDrawPlayer.Get_Speed();
				pCloneBoss = CAbstractFactory<CBoss>::Create_Unit(m_iTeam, tDrawPlayer.fx + pt.x, tDrawPlayer.fy + pt.y, 0, L"클론 보스", 80, 999);
				CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT, pCloneBoss);
				static_cast<CBoss*>(pCloneBoss)->Set_Unit(tUnit);
				static_cast<CBoss*>(pCloneBoss)->Alter_Clone() = true;
				pCloneBoss->Set_Master(this);
			}
		}

		if (m_pTarget->Get_Team() == m_iTeam)
		{
			Set_Target(nullptr);
			return OBJ_NOEVENT;
		}
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);


		if (fDist < 100)
		{
			if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 300 < dwNowTime)
				{
					m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
						CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", 60));
					m_dwObjTime[OBJ_TIMEID::SKILL] = dwNowTime;
					m_eNextState = UNIT_STATEID::ATTACK;
				}
			}
		}
		else if (fDist < 450)
		{
			if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 800 < dwNowTime)
				{
					m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
						CAbstractFactory<CBow>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));
					m_dwObjTime[OBJ_TIMEID::SKILL] = dwNowTime;
					m_eNextState = UNIT_STATEID::IDLE;
				}
			}
		}
		else if (fDist > m_fRecogDist)
		{
			m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
			CObj::Set_Target(nullptr);
		}
		else
		{
			if (m_bUnit_State[UNIT_STATEID::FOLLOW])
			{
				m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
				if (fDist > 100)
				{
					m_tDraw.Fn_Move();
					m_eNextState = UNIT_STATEID::FOLLOW;
				}
			}
		}
	}
	return OBJ_NOEVENT;
}

void CBoss::LateUpdate()
{
	CUnit::LateUpdate();
	CUnit::FSM();
}

void CBoss::Render(HDC hDC)
{
	//CMonster::Render(hDC);
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 220;
	tDraw.fcy = 220;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Boss_Boris");
	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		m_iFrameScene = 0;
	}
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * (m_tFrame.iFrameScene + m_iFrameScene),
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(64, 170, 226));
}

void CBoss::Release()
{
}

void CBoss::LateInit()
{
	/*m_tUnit.iGold = 55000;
	m_tUnit.iMaxExp = 75750;*/
}

void CBoss::Set_ImgDir(float _fAngle)
{
	int iAngle = int(m_tDraw.fAngle + 45) % 360;
	if (iAngle < 0)
		iAngle = 360 + iAngle;
	int iDir = iAngle / 45;

	switch (iDir)
	{
	case 0:	// 우
		m_iFrameScene = 24;
		break;
	case 1: // 우상
		m_iFrameScene = 20;
		break;
	case 2: // 상
		m_iFrameScene = 16;
		break;
	case 3: // 좌상
		m_iFrameScene = 12;
		break;
	case 4: // 좌
		m_iFrameScene = 8;
		break;
	case 5: // 좌하
		m_iFrameScene = 4;
		break;
	case 6: // 하
		m_iFrameScene = 0;
		break;
	case 7: // 우하
		m_iFrameScene = 28;
		break;
	}
}

void CBoss::SceneChange()
{
	/*if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{*/
		if (m_eCurState != m_eNextState)
		{
			switch (m_eNextState)
			{
			case UNIT_STATEID::IDLE:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 150;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			case UNIT_STATEID::FOLLOW:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iFrameScene = 1;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			case UNIT_STATEID::SLIDING:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iFrameScene = 1;
				m_tFrame.dwFrameSpeed = 40;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			case UNIT_STATEID::ATTACK:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iFrameScene = 2;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			case UNIT_STATEID::DEAD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iFrameScene = 3;
				m_tFrame.dwFrameSpeed = 400;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			}
			m_eCurState = m_eNextState;
		}
	//}
}
