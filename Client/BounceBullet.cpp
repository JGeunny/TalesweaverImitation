#include "stdafx.h"
#include "BounceBullet.h"

#include "ImgMgr.h"

CBounceBullet::CBounceBullet()
{
}


CBounceBullet::~CBounceBullet()
{
}

void CBounceBullet::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Skill/Skill_Soul.bmp", L"Skill_Soul");
	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 1000;
	m_tDraw.fSpeed = 15;
	m_tDraw.fcx = 100;
	m_tDraw.fcy = 100;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 0;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CBounceBullet::Update()
{
	int Event = CSkill::Update();
	if (Event == OBJ_DEAD) return Event;

	if (m_bSkill_State[SKILL_STATEID::BOUNCE])
	{
		//m_tDraw.fAngle *= -1;
		m_tDraw.fAngle += 90;
		m_bSkill_State[SKILL_STATEID::BOUNCE] = false;
	}
	//BOUNCE
	m_tDraw.Fn_Move();

	return Event;
}

void CBounceBullet::LateUpdate()
{
	CObj::MoveFrame();
	//this->SceneChange();
	this->Set_ImgDir(m_tDraw.fAngle);
}

void CBounceBullet::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fcx = 500.f;
	tDraw.fcy = 400.f;
	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Skill_Soul");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 255, 255));
}

void CBounceBullet::Release()
{
	CBullet::Release();
}
