#include "stdafx.h"
#include "Bow.h"
#include "Arrow.h"
#include "ImgMgr.h"
#include "Player.h"

#include "SoundMgr.h"

CBow::CBow()
	:m_bMultiShot(false)
{
}


CBow::~CBow()
{	
	for (auto pCrashObj : m_listObjMySlaves)
		pCrashObj->Set_Dead(true);
	if (m_pMaster)
		static_cast<CUnit*>(m_pMaster)->Alter_UnitState(UNIT_STATEID::DOSKILL) = false;
}

void CBow::Initialize()
{
	/*CImgMgr::Get_Instance()->AddImage(L"Skill/BOW_LEFT.bmp", L"BOW_LEFT");
	CImgMgr::Get_Instance()->AddImage(L"Skill/BOW_RIGHT.bmp", L"BOW_RIGHT");*/
	m_pFrameKey = L"BOW_RIGHT";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameScene = 4;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 0;
	m_tDraw.fcx = 96.f;
	m_tDraw.fcy = 90.7f;
}

int CBow::Update()
{
	if (m_pMaster == nullptr)
		return OBJ_DEAD;
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	if (false == m_bObjState[OBJ_STATEID::DEAD])
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			if (m_pMaster)
			{
				if (dynamic_cast<CUnit*>(m_pMaster))
				{
					
					if (m_bMultiShot)
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"multi5.wav", CSoundMgr::CHANNELID::EFFECT);
						INFO_UNIT tUnit = static_cast<CUnit*>(m_pMaster)->Get_Unit();
						INFO_UNIT tUnit_Temp = tUnit;
						tUnit.iCritical /= 5;
						static_cast<CUnit*>(m_pMaster)->Set_Unit(tUnit);
						m_pMaster->Alter_Angle_Skill() = m_tDraw.fAngle;
						
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
						static_cast<CUnit*>(m_pMaster)->Set_Unit(tUnit_Temp);
					}
					else
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"bow1.wav", CSoundMgr::CHANNELID::EFFECT);
						m_fAngle = m_tDraw.fAngle;
						m_pMaster->Alter_Angle_Skill() = m_tDraw.fAngle;
						CObj* pCrashObj = CAbstractFactory<CArrow>::Create_Skill(m_pMaster, 0, L"@", m_tSkill.iAtt, 99999);
						pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 1000;
						pCrashObj->Alter_Draw().fAngle = m_fAngle;
						CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
							emplace_back(pCrashObj);
					}
				}
			}
			m_bObjState[OBJ_STATEID::DEAD] = true;
		}
	}
	
	CObj::LateInit();
	CObj::LiveTime();

	m_tDraw = m_pMaster->Get_Info();

	if (dynamic_cast<CPlayer*>(m_pMaster))
	{
		if (m_pMaster->Get_Target())
		{
			INFO_DRAW tTarget = m_pMaster->Get_Target()->Get_Info();	// 마우스
			m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);
		}
	}
	
	m_tDraw.fSpeed = 50;
	m_tDraw.Fn_Move();

	return OBJ_NOEVENT;
}

void CBow::LateUpdate()
{
	CObj::MoveFrame();
	CBow::Set_ImgDir(m_tDraw.fAngle);
}

void CBow::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 96.f;
	tDraw.fcy = 90.7f;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(0, 255, 255));
}

void CBow::Release()
{
}

void CBow::LateInit()
{

}

void CBow::Set_ImgDir(float _fAngle)
{
	int iAngle = int(m_tDraw.fAngle + 0) % 360;
	if (iAngle < 0)
		iAngle = 360 + iAngle;
	//18
	int iDir = iAngle / 20;

	m_tFrame.iFrameEnd = 3;
	switch (iDir)
	{
	case 0:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 4;
		break;
	case 1:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 3;
		break;
	case 2:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 2;
		break;
	case 3:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 1;
		break;
	case 4://오른쪽임
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 0;
		break;
	case 5://왼쪽임
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 0;
		break;
	case 6:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 1;
		break;
	case 7:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 2;
		break;
	case 8:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 3;
		break;
	case 9:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 4;
		break;
	case 10:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 5;
		break;
	case 11:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 6;
		break;
	case 12:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 7;
		break;
	case 13:
		m_pFrameKey = L"BOW_LEFT";
		m_tFrame.iFrameScene = 8;
		break;
	case 14:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 8;
		break;
	case 15://오른쪽 밑
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 7;
		break;
	case 16:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 6;
		break;
	case 17:
		m_pFrameKey = L"BOW_RIGHT";
		m_tFrame.iFrameScene = 5;
		break;
	}
}
