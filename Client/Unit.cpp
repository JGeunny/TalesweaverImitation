#include "stdafx.h"
#include "Unit.h"
#include "ImgMgr.h"

CUnit::CUnit()
{
}

CUnit::~CUnit()
{
	m_listImgDir.clear();
	m_listImgDir.shrink_to_fit();
}

void CUnit::Initialize()
{
	m_tDraw.Initialize(400, 300, 50, 50, 5, 0);
	CImgMgr::Get_Instance()->AddImage(L"ui/Small_HpBarEmpty.bmp", L"Small_HpBarEmpty");
	CImgMgr::Get_Instance()->AddImage(L"ui/Small_HpBar.bmp", L"Small_HpBar");
}

void CUnit::LateUpdate()
{
	m_bUnit_State[UNIT_STATEID::BEATTACKED] = false;
	if (m_iBeAttacked_Hp > m_tUnit.iHp)
	{
		//공격 받았음
		m_bUnit_State[UNIT_STATEID::BEATTACKED] = true;
	}
	m_iBeAttacked_Hp = m_tUnit.iHp;
	CObj::MoveFrame();
	this->SceneChange();
	this->Set_ImgDir(m_tDraw.fAngle);
}

void CUnit::FSM()
{
	//IDLE 상태에서 공격을 한다면
	if (m_eCurState != m_eNextState)
	{
		for (auto& bFSM : m_bUnit_State)
			bFSM  = false;
		m_bUnit_State[m_eNextState] = true;
		m_eCurState = m_eNextState;
	}
	/*if (m_pTarget)
	{
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		m_tDraw.Set_Angle(tDrawTarget.fx, tDrawTarget.fy);

		//기본 상태 아무것도 안함
		m_bUnit_State[UNIT_STATEID::IDLE] = true;
		
		//1. 이동 부분
		if (m_fRecogDist >= fDist)// 타겟이 사정거리 안에 있으면 움직인다.
			m_bUnit_State[UNIT_STATEID::FOLLOW] = true;
		//대쉬기는 인지거리의 1 ~ 3/4 사이에서만 사용한다.
		if (m_fRecogDist >= fDist  && m_fRecogDist * 0.75 <= fDist)
			m_bUnit_State[UNIT_STATEID::SLIDING] = true;

		//2. 공격 대상이 있는가?
		m_bUnit_State[UNIT_STATEID::ATTACK] = true;
	}*/
}

void CUnit::Render_Info(HDC hDC)
{
	/*TCHAR szHpInfo[30];
	swprintf_s(szHpInfo, L"체력:%d/%d 경험치 %d/%d", m_tUnit.iHp, m_tUnit.iMaxHp, m_tUnit.iExp, m_tUnit.iMaxExp);
	TextOut(hDC, (int)m_tDraw.fx - 8 * lstrlen(m_tUnit.szName), int(m_tDraw.fy - m_tDraw.fcy*0.5), m_tUnit.szName, lstrlen(m_tUnit.szName));
	TextOut(hDC, (int)m_tDraw.fx - 8 * lstrlen(m_tUnit.szName), int(m_tDraw.fy - m_tDraw.fcy*0.5 - 16), szHpInfo, lstrlen(szHpInfo));*/

	if (false == m_bHideHpBar)
	{
		/*HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Small_HpBarEmpty");
		GdiTransparentBlt(hDC, (int)m_tDraw.fx - 52 * 0.5, (int)m_tDraw.fy + (int)m_tDraw.fcy * 0.5, 52, 5, hMemDC,
			0, 0, 52, 5, RGB(255, 0, 255));

		hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Small_HpBar");
		GdiTransparentBlt(hDC, int(m_tDraw.fx - 52 * 0.5 + 1), int(m_tDraw.fy + m_tDraw.fcy * 0.5 + 1), int(50 * m_tUnit.iHp / m_tUnit.iMaxHp), 3, hMemDC,
			0, 0, 50, 3, RGB(255, 0, 255));*/

		if (false == m_bObjState[OBJ_STATEID::OVERPOWER])
		{
			Rectangle(hDC, (int)m_tDraw.fx - m_tDraw.fcx * 0.5 - 10, (int)m_tDraw.fy + (int)m_tDraw.fcy * 0.5, (int)m_tDraw.fx - m_tDraw.fcx * 0.5, (int)m_tDraw.fy + (int)m_tDraw.fcy * 0.5 + 5);
			HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Small_HpBarEmpty");
			GdiTransparentBlt(hDC, (int)m_tDraw.fx - m_tDraw.fcx * 0.5, (int)m_tDraw.fy + (int)m_tDraw.fcy * 0.5, m_tDraw.fcx, 5, hMemDC,
				0, 0, 52, 5, RGB(255, 0, 255));

			hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Small_HpBar");
			GdiTransparentBlt(hDC, int(m_tDraw.fx - m_tDraw.fcx * 0.5 + 1), int(m_tDraw.fy + m_tDraw.fcy * 0.5 + 1), int(m_tDraw.fcx * m_tUnit.iHp / m_tUnit.iMaxHp), 3, hMemDC,
				0, 0, 50, 3, RGB(255, 0, 255));
		}
	}
}

void CUnit::Set_ImgDir(float _fAngle)
{
	int iAngle = int(m_tDraw.fAngle + 45) % 360;
	if (iAngle < 0)
		iAngle = 360 + iAngle;

	int iDir = iAngle / 45;
	if (0 > iDir || m_listImgDir.size() <= iDir){}
	else m_pFrameKey = m_listImgDir[iDir];
}
