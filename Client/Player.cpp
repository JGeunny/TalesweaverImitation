#include "stdafx.h"
#include "Player.h"
#include "Skill.h"
#include "Bullet.h"
#include "BounceBullet.h"
#include "Wield.h"
#include "Whirlwind.h"
#include "ThunderWield.h"
#include "Bow.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "ObjMgrBuffer.h"

#include "AbstractFactory.h"
#include "LevelUp.h"
#include "ImgMgr.h"
#include "InterFace.h"
#include "Store_UI.h"

#include "SoundMgr.h"

CPlayer::CPlayer()
	:m_iBaseAttack(0)
	, m_bWhirlWind(false)
	, m_bArrow(false)
{
}

CPlayer::~CPlayer()
{
	//저세상 코드*** 데이터 정보를 유지하기 위해 정보를 저장한다.
	if(m_tUnit.iHp <= 0)
		m_tUnit.Fn_Recovery();
	CSceneMgr::g_tPlayerUnitInfo = m_tUnit;
}

void CPlayer::Initialize()
{
	CUnit::Initialize();
	/*CImgMgr::Get_Instance()->AddImage(L"Player/Player_Down_.bmp", L"Player_Down_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_Left_.bmp", L"Player_Left_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_LeftDown_.bmp", L"Player_LeftDown_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_LeftUp_.bmp", L"Player_LeftUp_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_Right_.bmp", L"Player_Right_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_RightDown_.bmp", L"Player_RightDown_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_RightUp_.bmp", L"Player_RightUp_");
	CImgMgr::Get_Instance()->AddImage(L"Player/Player_Up_.bmp", L"Player_Up_");	*/
	
	m_pFrameKey = L"Player_Down_";

	/*m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 3;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();*/
	m_eCurState = UNIT_STATEID::END;
	m_eNextState = UNIT_STATEID::IDLE;

	m_pFrameKey = L"Player_Right_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_RightUp_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_Up_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_LeftUp_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_Left_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_LeftDown_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_Down_";
	m_listImgDir.emplace_back(m_pFrameKey);
	m_pFrameKey = L"Player_RightDown_";
	m_listImgDir.emplace_back(m_pFrameKey);
	

	m_tDraw.fcx = 50.f;
	m_tDraw.fcy = 80.f;
	m_tDraw.fSpeed = 10;

	m_fRecogDist = 9999;
	
	m_fSliding = 10;
	m_fSpeedBuf = 0;

	m_dwSlidingTime = GetTickCount();
	m_dwObjTime[OBJ_TIMEID::SKILL] = m_dwSlidingTime;

	
}

int CPlayer::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	Control();

	if (m_tUnit.iMaxMp > m_tUnit.iMp)
		m_tUnit.iMp += 3;

	if (m_tUnit.iMaxMp < m_tUnit.iMp)
		m_tUnit.iMp = m_tUnit.iMaxMp;

	if (m_tUnit.Fn_LevelUp())
	{
		m_tUnit.iAtt += 50;
		m_tUnit.iMaxHp += 200;
		m_tUnit.iMaxMp += 100;
		m_tUnit.iMaxExp += 1000 * m_tUnit.iLevel;
		++m_tUnit.iLevel;
		m_tUnit.Fn_Recovery();
		CObjMgrBuffer::Get_Instance()->AddObject(OBJID::EFFECT,CAbstractFactory<CLevelUp>::Create(TEAM_MOUSE, m_tDraw.fx, m_tDraw.fy));
	}
	
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	if (m_bUnit_State[UNIT_STATEID::DOSKILL])
	{
		if (m_bWhirlWind)
		{
			float fAngle = m_tDraw.fAngle;
			m_tDraw.fAngle = m_fAngle_Skill;
			CUnit::LateUpdate();
			m_tDraw.fAngle = fAngle;
			m_fAngle_Skill += 45;
		}
		else if (m_bArrow)
		{
			float fAngle = m_tDraw.fAngle;
			m_tDraw.fAngle = m_fAngle_Skill;
			CUnit::LateUpdate();
			m_tDraw.fAngle = fAngle;
		}
		else
		{
			CUnit::LateUpdate();
		}
	}
	else
	{
		CUnit::LateUpdate();
	}
	
	IsOffset();
	CUnit::FSM();
}

void CPlayer::Render(HDC hDC)
{
	
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 256.f;
	tDraw.fcy = 256.f;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy,	hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart, 
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 0, 255));
	/*m_tRect = m_tDraw.Get_Rect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);*/
}

void CPlayer::Release()
{
	//SAFE_DELETE(m_pRotatePos);
}

void CPlayer::Control()
{
	if (nullptr == m_pTarget) return;
	if (!m_bUnit_State[UNIT_STATEID::DOSKILL])
	{
		m_bWhirlWind = false;
		m_bArrow = false;
		m_fAngle_Skill = 0;
		m_eNextState = UNIT_STATEID::IDLE;
	}
	else if (false == m_bUnit_State[UNIT_STATEID::BEATTACKED])
	{
		if (m_eNextState != UNIT_STATEID::ATTACK)
			m_eNextState = UNIT_STATEID::IDLE;
	}

	DWORD dwNowTime = GetTickCount();


	if (m_eNextState == UNIT_STATEID::IDLE)
	{
		if (m_bUnit_State[UNIT_STATEID::BEATTACKED])
		{
			m_eNextState = UNIT_STATEID::BEATTACKED;
			m_bUnit_State[UNIT_STATEID::BEATTACKED] = false;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('Q'))	// Q를 썻을 경우 휠윈드 공격
	{
		if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
		{
			m_bWhirlWind = true;
			if (m_tUnit.iMp >= 50)
			{
				m_tUnit.iMp -= 50;
				m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
					CAbstractFactory<CWhirlwind>::Create_Skill(this, 0, L"@", 2 * m_tUnit.iAtt));
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('W'))	// W를 썻을 경우 총알 공격
	{
		if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
		{
			m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
			m_bArrow = true;
			INFO_DRAW tTarget = m_pTarget->Get_Info();
			float fAngle = m_tDraw.fAngle;
			m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);
			/*CObjMgr::Get_Instance()->AddObject(OBJID::SKILL_CRASH,
				CAbstractFactory<CBullet>::Create_Skill(this, m_tDraw.fcx, L"@", 60, 1));*/
			CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
				CAbstractFactory<CBow>::Create_Skill(this, m_tDraw.fcx, L"@", m_tUnit.iAtt, 1));
				//CAbstractFactory<CBow>::Create_Skill(this, m_tDraw.fcx, L"@", 20, 1));
			m_fAngle_Skill = m_tDraw.fAngle;
			m_tDraw.fAngle = fAngle;
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('E'))	// E를 썻을 경우 총알 공격
	{
		if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
		{
			if (m_tUnit.iMp >= 30)
			{
				m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
				m_bArrow = true;
				m_tUnit.iMp -= 30;
				INFO_DRAW tTarget = m_pTarget->Get_Info();
				float fAngle = m_tDraw.fAngle;
				m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);
				/*CObjMgr::Get_Instance()->AddObject(OBJID::SKILL,
					CAbstractFactory<CThunderWield>::Create_Skill(this, m_tDraw.fcx, L"@", 20, 1));*/
				CObj* pObj = CAbstractFactory<CBow>::Create_Skill(this, m_tDraw.fcx, L"@", m_tUnit.iAtt, 1);
				static_cast<CBow*>(pObj)->Set_MultiShot(true);
				CObjMgr::Get_Instance()->AddObject(OBJID::SKILL, pObj);
				m_fAngle_Skill = m_tDraw.fAngle;
				m_tDraw.fAngle = fAngle;
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('A')) // A를 썻을 경우 기본 베기 공격
	{
		if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
		{
			m_eNextState = UNIT_STATEID::ATTACK;
			m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
			INFO_DRAW tTarget = m_pTarget->Get_Info();
			float fAngle = m_tDraw.fAngle;
			m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);

			CObj* pWield = CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", m_tUnit.iAtt);
			static_cast<CSkill*>(pWield)->Alter_Option() = m_iBaseAttack;
			CObjMgr::Get_Instance()->AddObject(OBJID::SKILL, pWield);
			//m_tDraw.fAngle = fAngle;
			m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))//좌클릭 기본 베기 공격
	{
		bool bUIActivate = false;
		list<CObj*> listUI;
		listUI.emplace_back(CInterFace::Get_Instance()->pInterFace[CInterFace::Store_UI]);
		listUI.emplace_back(CInterFace::Get_Instance()->pInterFace[CInterFace::Equip]);
		listUI.emplace_back(CInterFace::Get_Instance()->pInterFace[CInterFace::Inventory]);
		for (auto& pUI : listUI)
		{
			if (pUI)
			{
				if (pUI->Alter_Activation())
					bUIActivate = true;
			}
			pUI = nullptr;
		}
		listUI.clear();
		if (bUIActivate) return;
	
		if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
		{
			m_eNextState = UNIT_STATEID::ATTACK;
			m_bUnit_State[UNIT_STATEID::DOSKILL] = true;
			INFO_DRAW tTarget = m_pTarget->Get_Info();
			float fAngle = m_tDraw.fAngle;
			m_tDraw.Set_Angle(tTarget.fx, tTarget.fy);

			CObj* pWield = CAbstractFactory<CWield>::Create_Skill(this, m_tDraw.fcx, L"@", m_tUnit.iAtt);
			static_cast<CSkill*>(pWield)->Alter_Option() = m_iBaseAttack;
			CObjMgr::Get_Instance()->AddObject(OBJID::SKILL, pWield);
			//m_tDraw.fAngle = fAngle;
			m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_RBUTTON))//우클릭 이동
	{
		m_bUnit_State[UNIT_STATEID::FOLLOW] = true;
		m_tDraw_Target = m_pTarget->Get_Info();
		m_tDraw.Set_Angle(m_tDraw_Target.fx, m_tDraw_Target.fy);
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_SPACE))//우클릭 이동
	{
		if (false == m_bUnit_State[UNIT_STATEID::SLIDING])
		{
			if (m_dwSlidingTime + 1000 < dwNowTime)
			{
				m_bUnit_State[UNIT_STATEID::SLIDING] = true;
				m_fSpeedBuf = m_tDraw.fSpeed;
				m_tDraw.fSpeed += m_fSliding;

				m_dwSlidingTime = dwNowTime;
				m_iSliding_Count = 0;
			}
		}
	}

	if (m_bUnit_State[UNIT_STATEID::SLIDING])
	{
		if(m_iSliding_Count == 0)
			CSoundMgr::Get_Instance()->MyPlaySound(L"charge.wav", CSoundMgr::CHANNELID::EFFECT);

		m_eNextState = UNIT_STATEID::SLIDING;

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
			if (0 == PtInRect(&m_tDraw_Target.Get_Rect(), m_tDraw.Get_Point()))
			{
				m_eNextState = UNIT_STATEID::FOLLOW;

				m_tDraw.Fn_Move();
			}
			else
			{
				m_bUnit_State[UNIT_STATEID::FOLLOW] = false;
				m_eNextState = UNIT_STATEID::IDLE;
			}
		}
	}
	/*if (false == m_bUnit_State[UNIT_STATEID::DOSKILL])
	{
		if(m_eNextState == UNIT_STATEID::ATTACK)
			m_eNextState = UNIT_STATEID::IDLE;
	}*/
}

void CPlayer::LateInit()
{
	if(false == CObjMgr::Get_Instance()->Get_List(OBJID::MOUSE)->empty())
		CObj::Set_Target(CObjMgr::Get_Instance()->Get_List(OBJID::MOUSE)->front());

	//저세상 코드*** 데이터 정보를 유지하기 위해 정보를 불러온다.
	m_tUnit = CSceneMgr::g_tPlayerUnitInfo;

	m_tUnit.iCritical = 200;
	m_tDraw.fAngle = 250;
}

void CPlayer::IsOffset()
{
	POINTFLOAT ptOffset = { WINCX*0.5, WINCY*0.5 };
	POINTFLOAT& ptScroll = CScrollMgr::Alter_Scroll();

	POINTFLOAT ptSpeed = m_tDraw.Get_Speed();
	if (ptOffset.x < m_tDraw.fx + ptScroll.x + 180)
		CScrollMgr::Set_ScrollX(-abs(ptSpeed.x));
	if (ptOffset.x > m_tDraw.fx + ptScroll.x - 180)
		CScrollMgr::Set_ScrollX(abs(ptSpeed.x));

	if (ptOffset.y < m_tDraw.fy + ptScroll.y - 150)
		CScrollMgr::Set_ScrollY(abs(ptSpeed.y));
	if (ptOffset.y > m_tDraw.fy + ptScroll.y + 150)
		CScrollMgr::Set_ScrollY(-abs(ptSpeed.y));
}

void CPlayer::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case UNIT_STATEID::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 5;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::FOLLOW:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::SLIDING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case UNIT_STATEID::ATTACK:
			m_iBaseAttack = m_iBaseAttack % 2;
			if (m_iBaseAttack == 0)
			{
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 8;
				m_tFrame.iFrameScene = 2;
				m_tFrame.dwFrameSpeed = 40;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.iFrameScene = 0;
				m_tFrame.dwFrameSpeed = 40;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			++m_iBaseAttack;
			break;
		case UNIT_STATEID::BEATTACKED:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}
