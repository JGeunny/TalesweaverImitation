#include "stdafx.h"
#include "BossState.h"
#include "Boss.h"

CBossState::CBossState(CObj * _pObj)
	:CStatePattern(_pObj)
{
}

CBossState::~CBossState()
{
}

void CBossState::Initialize()
{
}

int CBossState::Update()
{
	CObj* m_pTarget = m_pObj->Get_Target();
	INFO_DRAW& m_tDraw = m_pObj->Alter_Draw();
	INFO_UNIT& m_tUnit = static_cast<CUnit*>(m_pObj)->Alter_UnitInfo();
	DWORD dwNowTime = GetTickCount();

	//타겟을 따라가는 부분
	/*if (m_pTarget)
	{
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);

		if (m_tUnit.iHp <= m_tUnit.iMaxHp * 0.25)
		{
			m_tDraw.fSpeed = m_fSpeedBuf;

			if (fDist > m_fRecogDist)
			{
				m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
				CObj::Set_Target(nullptr);
			}
			if (m_bUnit_State[UNIT_STATEID::FOLLOW])
			{
				m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
				m_tDraw.fAngle += 90;
				if (0 == IntersectRect(&RECT(), &tDrawTarget.Get_Rect(), &m_tDraw.Get_Rect()))
				{
					m_tDraw.Fn_Move();
				}
				else
				{
					m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
					CObj::Set_Target(nullptr);
				}
			}
		}
		else
		{
			if (fDist < 100)
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 500 < dwNowTime)
				{
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
						CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", 60));
					m_dwObjTime[OBJ_TIMEID::SKILL] = dwNowTime;
				}
			}
			else if (fDist < 150)
			{
				if (m_dwObjTime[OBJ_TIMEID::SKILL] + 50 < dwNowTime)
				{
					CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH,
						CAbstractFactory<CBounceBullet>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));
					m_dwObjTime[OBJ_TIMEID::SKILL] = dwNowTime;
				}
			}
			else if (fDist > m_fRecogDist)
			{
				m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
				CObj::Set_Target(nullptr);
			}
			else if (fDist < 500)
			{
				if (m_tUnit.iHp <= m_tUnit.iMaxHp * 0.5)
				{
					if (false == m_bUnit_State[UNIT_STATEID::SLIDING])
					{
						if (m_dwSlidingTime + 1500 < dwNowTime)
						{
							m_bUnit_State[UNIT_STATEID::SLIDING] = true;
							m_fSpeedBuf = m_tDraw.fSpeed;
							m_tDraw.fSpeed += m_fSliding;

							m_dwSlidingTime = dwNowTime;
							m_iSliding_Count = 0;
						}
					}
				}
			}

			if (m_bUnit_State[UNIT_STATEID::SLIDING])
			{
				m_tDraw.Fn_Move();

				++m_iSliding_Count;
				if (m_iSliding_Count > 10)
				{
					m_bUnit_State[UNIT_STATEID::SLIDING] = false;
					m_tDraw.fSpeed = m_fSpeedBuf;
				}
			}
			else
			{
				if (m_bUnit_State[UNIT_STATEID::FOLLOW])
				{
					m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
					if (0 == IntersectRect(&RECT(), &tDrawTarget.Get_Rect(), &m_tDraw.Get_Rect()))
					{
						m_tDraw.Fn_Move();
					}
					else
					{
						m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
						CObj::Set_Target(nullptr);
					}
				}
			}
		}
	}*/
	return OBJ_NOEVENT;
}

void CBossState::LateUpdate()
{
}

void CBossState::Render(HDC hDC)
{
}

void CBossState::Release()
{
}
