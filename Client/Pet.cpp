#include "stdafx.h"
#include "Pet.h"
#include "Unit.h"
#include "ImgMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "Wield.h"

CPet::CPet()
{
}

CPet::~CPet()
{
}

void CPet::Initialize()
{
	CUnit::Initialize();
	m_tDraw.fSpeed = 6;
	m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();

	CImgMgr::Get_Instance()->AddImage(L"Pet/Normal_Left.bmp", L"Normal_Left");
	CImgMgr::Get_Instance()->AddImage(L"Pet/Normal_Right.bmp", L"Normal_Right");
	m_pFrameKey = L"Normal_Right";
	m_eCurState = UNIT_STATEID::END;
	m_eNextState = UNIT_STATEID::IDLE;
	

	m_pFrameKey = L"Normal_Right";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Right";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Right";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Left";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Left";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Left";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Right";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Normal_Right";
	m_listImgDir.emplace_back(m_pFrameKey);

	//35*29  96*105
	m_tDraw.fcx = 96;
	m_tDraw.fcy = 105;
}

int CPet::Update()
{
	if (m_bUnit_State[UNIT_STATEID::DEAD])
		return OBJ_DEAD;

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		if (false == m_bDeadSound)
		{
			m_bDeadSound = true;
			CSoundMgr::Get_Instance()->MyPlaySound(L"rogue_death1.wav", CSoundMgr::CHANNELID::EFFECT);
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
		if (fDist < 100 + m_pTarget->Get_Info().fcx *0.5)
		{
			if (m_dwObjTime[OBJ_TIMEID::SKILL] + 300 < m_dwNowTime)
			{
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
					CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", 60));
				m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
				m_eNextState = UNIT_STATEID::ATTACK;
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
				if (fDist > 100 + m_pTarget->Get_Info().fcx *0.5)
				{
					m_tDraw.Fn_Move();
					m_eNextState = UNIT_STATEID::FOLLOW;
				}
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
		if (fDist > 800)
		{
			m_tDraw.fx = tDrawMaster.fx - 180;
			m_tDraw.fy = tDrawMaster.fy;
			m_eNextState = UNIT_STATEID::IDLE;
		}
		else if (fDist > 180)
		{
			m_tDraw.Fn_Move();
			m_eNextState = UNIT_STATEID::FOLLOW;
		}
		else
		{
			m_eNextState = UNIT_STATEID::IDLE;
		}
	}
	return OBJ_NOEVENT;
}

void CPet::LateUpdate()
{
	CUnit::LateUpdate();
	CUnit::FSM();
}

void CPet::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 96;
	tDraw.fcy = 105;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)96 * m_tFrame.iFrameStart,
		(int)105 * m_tFrame.iFrameScene,
		(int)96, (int)105,
		RGB(255, 0, 255));
}

void CPet::Release()
{
}

void CPet::Control()
{
}

void CPet::LateInit()
{
}

void CPet::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case UNIT_STATEID::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 34;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::FOLLOW:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 150;
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
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 12;
			m_tFrame.dwFrameSpeed = 60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 350;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_eCurState = m_eNextState;
	}
}
