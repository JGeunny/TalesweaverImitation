#include "stdafx.h"
#include "Bullet.h"

#include "ImgMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Skill/Bullet_Orange_20.bmp", L"Bullet_Orange_20");
	CSkill::Initialize();
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 2000;
	m_tDraw.fSpeed = 15;
	m_tDraw.fcx = 27;
	m_tDraw.fcy = 27;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	
}

int CBullet::Update()
{
	int Event = CSkill::Update();
	if(Event == OBJ_DEAD) return Event;
	//if (nullptr == m_pTarget) return OBJ_DEAD;

	if (m_pTarget)
	{
		if (m_pTarget->Get_Team() == m_iTeam)
		{
			Set_Target(nullptr);
			return OBJ_NOEVENT;
		}
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);
	}

	m_tDraw.Fn_Move();

	return Event;
}

void CBullet::LateUpdate()
{
	//CObj::MoveFrame();
	//this->SceneChange();
	//this->Set_ImgDir(m_tDraw.fAngle);
}

void CBullet::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	RECT tRect = m_tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Bullet_Orange_20");
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)m_tDraw.fcx, (int)m_tDraw.fcy, hMemDC,
		0,0, 27, 27,
		RGB(255, 0, 255));
}

void CBullet::Release()
{
}

