#include "stdafx.h"
#include "Bomb.h"

#include "ImgMgr.h"
#include "Player.h"
#include "ObjMgrBuffer.h"
#include "Explosion.h"
#include "Bullet.h"

CBomb::CBomb()
{
}


CBomb::~CBomb()
{
	for (auto pCrashObj : m_listObjMySlaves)
		pCrashObj->Set_Dead(true);
	if (m_pMaster)
		static_cast<CUnit*>(m_pMaster)->Alter_UnitState(UNIT_STATEID::DOSKILL) = false;
}

void CBomb::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Skill/Grenade.bmp", L"Grenade");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();

	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 1000;
	m_tDraw.fcx = 36.f;
	m_tDraw.fcy = 40.f;
}

int CBomb::Update()
{
	if (m_pMaster == nullptr)
		return OBJ_DEAD;
	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		CObj* pExplosion = CAbstractFactory<CExplosion>::Create(TEAM_MOUSE, m_tDraw.fx, m_tDraw.fy);
		CObjMgrBuffer::Get_Instance()->Get_List()[OBJID::EFFECT].emplace_back(pExplosion);


		m_fAngle = m_tDraw.fAngle;
		INFO_DRAW tDraw = m_tDraw;
		tDraw.fcx = 18;
		tDraw.fcy = 18;
		for (int i = 0; i < 36; ++i)
		{
			m_fAngle += 10;
			CObj* pCrashObj = CAbstractFactory<CBullet>::Create_Skill(m_pMaster, 0, L"@", m_tSkill.iAtt, 1);
			pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 1000;
			pCrashObj->Alter_Draw() = tDraw;
			pCrashObj->Alter_Draw().fAngle = m_fAngle;
			CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
				emplace_back(pCrashObj);
		}

		return OBJ_DEAD;
	}
			

	/*if (false == m_bObjState[OBJ_STATEID::DEAD])
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			if (m_pMaster)
			{
				if (m_bMultiShot)
				{
					m_fAngle = m_tDraw.fAngle - 25;
					for (int i = 0; i < 5; ++i)
					{
						m_fAngle += 10;
						CObj* pCrashObj = CAbstractFactory<CArrow>::Create_Skill(m_pMaster, 0, L"@", m_tSkill.iAtt, 1);
						pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 1000;
						pCrashObj->Alter_Draw().fAngle = m_fAngle;
						CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
							emplace_back(pCrashObj);
					}
				}
				else
				{
					m_fAngle = m_tDraw.fAngle;
					CObj* pCrashObj = CAbstractFactory<CArrow>::Create_Skill(m_pMaster, 0, L"@", m_tSkill.iAtt, 99999);
					pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 1000;
					pCrashObj->Alter_Draw().fAngle = m_fAngle;
					CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
						emplace_back(pCrashObj);
				}
			}
			m_bObjState[OBJ_STATEID::DEAD] = true;
		}
	}
	*/
	CObj::LateInit();
	CObj::LiveTime();

	/*if (dynamic_cast<CPlayer*>(m_pMaster))
	{
		if (m_pMaster->Get_Target())
		{
			INFO_DRAW tTarget = m_pMaster->Get_Target()->Get_Info();	// ¸¶¿ì½º
			m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);
		}
	}*/

	m_tDraw.fSpeed = 12;
	m_tDraw.Fn_Move();

	return OBJ_NOEVENT;
}

void CBomb::LateUpdate()
{
	CObj::MoveFrame();
}

void CBomb::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 36.f;
	tDraw.fcy = 40.f;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Grenade");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		36 * m_tFrame.iFrameStart,
		40 * m_tFrame.iFrameScene,
		36, 40,
		RGB(255, 0, 255));
}

void CBomb::Release()
{
}

void CBomb::LateInit()
{
}
