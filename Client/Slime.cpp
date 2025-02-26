#include "stdafx.h"
#include "Slime.h"

#include "ImgMgr.h"

#include "BounceBullet.h"
#include "SoundMgr.h"

CSlime::CSlime()
{
}


CSlime::~CSlime()
{
	Release();
}

void CSlime::Initialize()
{
	CUnit::Initialize();
	/*CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_LD.bmp", L"MonsterJelly_LD");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_LU.bmp", L"MonsterJelly_LU");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_RD.bmp", L"MonsterJelly_RD");
	CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_RU.bmp", L"MonsterJelly_RU");*/

	m_pFrameKey = L"MonsterJelly_LD";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eNextState = UNIT_STATEID::IDLE;

	m_pFrameKey = L"MonsterJelly_RD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_RU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_RU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_LU";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_LD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_LD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_RD";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"MonsterJelly_RD";
	m_listImgDir.emplace_back(m_pFrameKey);

	m_tDraw.fcx = 50.f;
	m_tDraw.fcy = 50.f;

	m_ptSize.x = 256;
	m_ptSize.y = 256;

	m_fRecogDist = 300;
}

int CSlime::Update()
{
	if (m_bUnit_State[UNIT_STATEID::DEAD])
		return OBJ_DEAD;

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		if (false == m_bDeadSound)
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"LarvaDeath.wav", CSoundMgr::CHANNELID::EFFECT);
			m_bDeadSound = true;
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
		if (fDist <= 100 + m_tDraw.fcx *0.5)
		{
			if (m_dwObjTime[OBJ_TIMEID::SKILL] + 500 < m_dwNowTime)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Ball.wav", CSoundMgr::CHANNELID::EFFECT);
				/*CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH,
					CAbstractFactory<CBounceBullet>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));
				m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;*/
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH,
					CAbstractFactory<CBullet>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));
				m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwNowTime;
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
				if(fDist > 100 + m_tDraw.fcx *0.5)
				{
					m_tDraw.Fn_Move();
					m_eNextState = UNIT_STATEID::FOLLOW;
				}
				else
				{
					m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
					CObj::Set_Target(nullptr);
					m_eNextState = UNIT_STATEID::IDLE;
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
		if (fDist > 180)
		{
			m_tDraw.Fn_Move();
			m_eNextState = UNIT_STATEID::FOLLOW;
		}
	}
	return OBJ_NOEVENT;
}

void CSlime::LateUpdate()
{
	CUnit::LateUpdate();
	CUnit::FSM();
}

void CSlime::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = m_ptSize.x;
	tDraw.fcy = m_ptSize.y;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)256 * m_tFrame.iFrameStart,
		(int)256 * m_tFrame.iFrameScene,
		(int)256, (int)256,
		RGB(255, 0, 255));
}

void CSlime::Release()
{
	CMonster::Release();
}

void CSlime::Control()
{
	CMonster::Control();
}

void CSlime::LateInit()
{
	m_tUnit.iGold = 100;
}

void CSlime::Set_Size(POINTFLOAT _ptCrushSize, POINTFLOAT _ptImageSize)
{
	m_tDraw.fcx = _ptCrushSize.x;
	m_tDraw.fcy = _ptCrushSize.y;
	m_ptSize = _ptImageSize;
}

void CSlime::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case UNIT_STATEID::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::FOLLOW:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
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
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_eCurState = m_eNextState;
	}
}

