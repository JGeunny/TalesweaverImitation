#include "stdafx.h"
#include "Whirlwind.h"
#include "Unit.h"
#include "ImgMgr.h"
#include "SoundMgr.h"

CWhirlwind::CWhirlwind()
{
	//CSoundMgr::Get_Instance()->MyPlaySound(L"whirlwind1.wav", CSoundMgr::CHANNELID::EFFECT);
	CSoundMgr::Get_Instance()->MyPlaySound(L"MultiAttack3.wav", CSoundMgr::CHANNELID::EFFECT);
}

CWhirlwind::~CWhirlwind()
{
	for (auto pCrashObj : m_listObjMySlaves)
		pCrashObj->Set_Dead(true);
	if (m_pMaster)
		static_cast<CUnit*>(m_pMaster)->Alter_UnitState(UNIT_STATEID::DOSKILL) = false;
}

void CWhirlwind::Initialize()
{
	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 2000;
	m_tDraw.fcx = 200;
	m_tDraw.fcy = 200;

	m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 17;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 35;
	m_tFrame.dwFrameTime = GetTickCount();
	
	CImgMgr::Get_Instance()->AddImage(L"Skill/Skill_WhirlWind.bmp", L"Skill_WhirlWind");
	//CImgMgr::Get_Instance()->AddImage(L"Skill/Skill_Jail.bmp", L"Skill_Jail");
	//CImgMgr::Get_Instance()->AddImage(L"Skill/MultiAttack.bmp", L"MultiAttack");
}

int CWhirlwind::Update()
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
		m_fAngle -= m_tDraw.fSpeed * 3;
	}
	return OBJ_NOEVENT;
}

void CWhirlwind::LateUpdate()
{
	CObj::MoveFrame();
	//this->SceneChange();
	//this->Set_ImgDir(m_tDraw.fAngle);
}

void CWhirlwind::Render(HDC hDC)
{
	//CSkill::Render(hDC);
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 117 * 1.5;
	tDraw.fcy = 98 * 1.5;
	/*tDraw.fcx = 512.f;
	tDraw.fcy = 512.f;*/
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Skill_WhirlWind");
	//HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"MultiAttack");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)117 * m_tFrame.iFrameStart,
		(int)98 * m_tFrame.iFrameScene,
		(int)117, (int)98,
		RGB(0, 0, 0));
}

void CWhirlwind::Release()
{
}

void CWhirlwind::LateInit()
{
	CObj* pCrashObj = CAbstractFactory<CSkill>::Create_Skill(this, 0, L"@", m_tSkill.iAtt, 99999);
	pCrashObj->Alter_TimeCount(OBJ_TIMEID::LIVE) = 0;
	CObjMgr::Get_Instance()->Get_List(OBJID::SKILL_CRASH)->
		emplace_back(pCrashObj);

	m_fAngle = pCrashObj->Get_Info().fAngle;
}
