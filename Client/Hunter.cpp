#include "stdafx.h"
#include "Hunter.h"
#include "Wield.h"
#include "Bullet.h"
#include "BounceBullet.h"
#include "Bow.h"

#include "ImgMgr.h"

#include "SoundMgr.h"

CHunter::CHunter()
{
}

CHunter::~CHunter()
{
}

void CHunter::Initialize()
{
	CUnit::Initialize();
	m_tDraw.fSpeed = 3;
	m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();

	m_pFrameKey = L"MonsterF_LD";
	m_eCurState = UNIT_STATEID::END;
	m_eNextState = UNIT_STATEID::IDLE;
	/*CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_LD.bmp", L"MonsterWizard_LD");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_LU.bmp", L"MonsterWizard_LU");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_RD.bmp", L"MonsterWizard_RD");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_RU.bmp", L"MonsterWizard_RU");*/

	m_pFrameKey = L"MonsterWizard_RD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_RU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_RU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_LU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_LD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_LD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_RD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterWizard_RD";
	m_listImgDir.emplace_back(m_pFrameKey);

	m_tDraw.fcx = 100.f;
	m_tDraw.fcy = 120.f;
}

int CHunter::Update()
{
	if (m_bUnit_State[UNIT_STATEID::DEAD])
		return OBJ_DEAD;

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		if (false == m_bDeadSound)
		{
			m_bDeadSound = true;
			CSoundMgr::Get_Instance()->MyPlaySound(L"Hunterdeath4.wav", CSoundMgr::CHANNELID::EFFECT);

		}
		m_eNextState = UNIT_STATEID::DEAD;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bUnit_State[UNIT_STATEID::DEAD] = true;
		return OBJ_NOEVENT;
	}

	CObj::LateInit();

	DWORD m_dwNowTime = GetTickCount();

	//타겟을 따라가는 부분
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
		if (fDist < 100)
		{
			if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 300 < m_dwNowTime)
				{
					m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
						CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", 60));
					m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
					m_eNextState = UNIT_STATEID::ATTACK;
				}
			}
		}
		else if (fDist < 450)
		{
			if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 1500 < m_dwNowTime)
				{
					m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
						CAbstractFactory<CBow>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));
					m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
					m_eNextState = UNIT_STATEID::ATTACK;
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
				//if (0 == IntersectRect(&RECT(), &tDrawTarget.Get_Rect(), &m_tDraw.Get_Rect()))
				if (fDist > 100)
				{
					m_tDraw.Fn_Move();
					m_eNextState = UNIT_STATEID::FOLLOW;
				}
				/*else
				{
				m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
				CObj::Set_Target(nullptr);
				}*/
			}
		}
	}
	else if (m_pMaster)
	{
		if (m_pMaster->Get_Team() != m_iTeam)
		{
			Set_Master(nullptr);
			return OBJ_NOEVENT;
		}
		INFO_DRAW	tDrawMaster = m_pMaster->Get_Info();
		float fDist = tDrawMaster.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		m_tDraw.Set_Angle(tDrawMaster.fx, tDrawMaster.fy);
		if (fDist > 180)
		{
			m_tDraw.Fn_Move();
			m_eNextState = UNIT_STATEID::FOLLOW;
		}
	}
	else
	{
		if (m_dwObjTime[OBJ_TIMEID::RUN] + 2000 < m_dwNowTime)
		{
			m_dwObjTime[OBJ_TIMEID::RUN] = m_dwNowTime;
			m_tDraw.fAngle = rand() % 361 + 1;
		}
		float fSpeed_Temp = m_tDraw.fSpeed;
		m_tDraw.fSpeed = m_tDraw.fSpeed * 0.5;
		m_tDraw.Fn_Move();
		m_tDraw.fSpeed = fSpeed_Temp;
	}
	return OBJ_NOEVENT;
}

void CHunter::LateUpdate()
{
	CUnit::LateUpdate();
	CUnit::FSM();
}

void CHunter::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 256;
	tDraw.fcy = 256;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 0, 255));
}

void CHunter::Release()
{
}

void CHunter::Control()
{
}

void CHunter::LateInit()
{
	m_tUnit.iGold = 550;
	m_tUnit.iMaxExp = 1050;
}

void CHunter::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case UNIT_STATEID::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 250;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::FOLLOW:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 250;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::SLIDING:
			/*m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();*/
			break;
		case UNIT_STATEID::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 180;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_eCurState = m_eNextState;
	}
}
