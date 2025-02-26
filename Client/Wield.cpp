#include "stdafx.h"
#include "Wield.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Unit.h"
#include "SoundMgr.h"

CWield::CWield()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"ATTACK.wav", CSoundMgr::CHANNELID::EFFECT);
}

CWield::~CWield()
{
	for (auto pCrashObj : m_listObjMySlaves)
		pCrashObj->Set_Dead(true);
	if (m_pMaster)
		static_cast<CUnit*>(m_pMaster)->Alter_UnitState(UNIT_STATEID::DOSKILL) = false;
}

void CWield::Initialize()
{
	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 200;
	m_tDraw.fcx = 200;
	m_tDraw.fcy = 200;
}

int CWield::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	if (m_pMaster == nullptr)
		return OBJ_DEAD;

	CObj::LateInit();
	CObj::LiveTime();

	for (auto pCrashObj : m_listObjMySlaves)
	{
		m_tDraw.fx = m_pMaster->Get_Info().fx;
		m_tDraw.fy = m_pMaster->Get_Info().fy;
		INFO_DRAW tCrash = pCrashObj->Get_Info();
		tCrash.fx = m_tDraw.fx;
		tCrash.fy = m_tDraw.fy;
		tCrash.fAngle = m_fAngle;
		tCrash.fSpeed = m_tDraw.fcx * 0.5f;
		tCrash.Fn_Move();
		pCrashObj->Set_Info(tCrash);
		if (m_iOption == 0)
			m_fAngle -= m_tDraw.fSpeed * 2;
		else
			m_fAngle += m_tDraw.fSpeed * 2;
	}
	return OBJ_NOEVENT;
}

void CWield::LateUpdate()
{
}

void CWield::Render(HDC hDC)
{
	//CSkill::Render(hDC);
}

void CWield::Release()
{
}

void CWield::LateInit()
{
	CObj* pCrashObj = CAbstractFactory<CSkill>::Create_Skill(this, 0, L"@", m_tSkill.iAtt, 99999);
	pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 0;
	CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
		emplace_back(pCrashObj);

	m_fAngle = pCrashObj->Get_Info().fAngle;
	if(m_iOption == 0)
		m_fAngle += 45;
	else
		m_fAngle -= 45;

}
