#include "stdafx.h"
#include "ThunderWield.h"
#include "Bullet.h"

CThunderWield::CThunderWield()
{
}


CThunderWield::~CThunderWield()
{
	for (auto pCrashObj : m_listObjMySlaves)
		pCrashObj->Set_Dead(true);
	if (m_pMaster)
		static_cast<CUnit*>(m_pMaster)->Alter_UnitState(UNIT_STATEID::DOSKILL) = false;
}

void CThunderWield::Initialize()
{
	CWield::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 2000;
	m_dwObjTime[OBJ_TIMEID::SKILL] = GetTickCount();
}

int CThunderWield::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	if (m_pMaster == nullptr)
		return OBJ_DEAD;

	DWORD m_dwNowTime = GetTickCount();

	CObj::LateInit();
	CObj::LiveTime();

	/*float fDist = 0;
	for (auto pCrashObj : m_listObjMySlaves)
	{
		m_tDraw.fx = m_pMaster->Get_Info().fx;
		m_tDraw.fy = m_pMaster->Get_Info().fy;
		INFO_DRAW tCrash = pCrashObj->Get_Info();
		tCrash.fx = m_tDraw.fx +fDist;
		tCrash.fy = m_tDraw.fy;// +fDist;
		tCrash.fAngle = m_fAngle;
		tCrash.fSpeed = 20;
		tCrash.Fn_Move();
		pCrashObj->Set_Info(tCrash);
		m_fAngle -= 1;

		fDist += 10;
	}*/
	
	return OBJ_NOEVENT;
}

void CThunderWield::LateUpdate()
{
	CWield::LateUpdate();
}

void CThunderWield::Render(HDC hDC)
{
	CWield::Render(hDC);
}

void CThunderWield::Release()
{
	CWield::Release();
}

void CThunderWield::LateInit()
{
	CWield::LateInit();

	m_fAngle = m_tDraw.fAngle - 100;
	for (int i = 0; i < 10; ++i)
	{
		m_fAngle += 20;
		CObj* pCrashObj = CAbstractFactory<CBullet>::Create_Skill(this, 0, L"@", m_tSkill.iAtt, 99999);
		pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 0;
		pCrashObj->Alter_Draw().fAngle = m_fAngle;
		CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
			emplace_back(pCrashObj);
	}
}
 