#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"
CObj::CObj()
	:m_pTarget(nullptr)
	, m_pMaster(nullptr)
	, m_bIsInit(false)
	, m_iTeam(0)
	, m_fRecogDist(300)
	, m_bHideHpBar(false)
	, m_bActivation(true)
	, m_bScrollRender(false)
	, m_bDeadSound(false)
	, m_fAngle_Skill(0)
{
	ZeroMemory(m_bObjState, sizeof(m_bObjState));
}

CObj::~CObj()
{
	MessageTo(OBJ_DEAD);
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		DWORD dwNowTime = GetTickCount();
		m_bIsInit = true;
		for (int i = 0; i < OBJ_TIMEID::END; ++i)
		{
			if (0 != m_iObjTimeCount[i])
				m_dwObjTime[i] = dwNowTime;
		}
		this->LateInit();
	}
}

void CObj::LiveTime()
{
	DWORD dwNowTime = GetTickCount();
	for (int i = 0; i < OBJ_TIMEID::END; ++i)
	{
		if (0 == m_iObjTimeCount[i]) continue;
		switch (i)
		{
		case OBJ_TIMEID::LIVE:
			if(m_dwObjTime[i] + m_iObjTimeCount[i] < dwNowTime)
				Set_Dead(true);
			break;
		default:
			if (m_dwObjTime[i] + m_iObjTimeCount[i] < dwNowTime)
				m_dwObjTime[i] = GetTickCount();
			break;
		}
	}
}

void CObj::MessageTo(int _iEvent)
{
	if (_iEvent & OBJ_DEAD)
	{	
		Clear_Target();
		for (auto& pObjTargetedAtMe : m_listObjTargetedAtMe)
		{
			if(pObjTargetedAtMe)
				pObjTargetedAtMe->Set_Target(nullptr);
		}
		m_listObjTargetedAtMe.clear();

		Clear_Master();
		for (auto& pObjMySlaves : m_listObjMySlaves)
		{
			if (pObjMySlaves)
				pObjMySlaves->Set_Master(nullptr);
		}
		m_listObjMySlaves.clear();
	}
}

void CObj::Render_Scroll(HDC hDC)
{
	m_bScrollRender = true;
	if (m_bActivation)
	{
		DWORD dwColor = RGB(255, 255, 255);
		switch (m_iTeam)//팀에 따른 색깔 처리
		{
		case TEAM_1:
			dwColor = RGB(50, 50, 255);
			break;
		case TEAM_2:
			dwColor = RGB(255, 0, 0);
			break;
		case TEAM_3:
			dwColor = RGB(155, 0, 255);
			break;
		case TEAM_4:
			dwColor = RGB(255, 100, 255);
			break;
		case TEAM_TILE:
			dwColor = RGB(100, 100, 100);
			break;
		}
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(dwColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		if (TEAM_MOUSE == m_iTeam) //좌표가 스크롤 위치에 있는 놈들을 무조건 0,0 기준으로 보이게 하기 위해
		{
			POINTFLOAT ptStroll = CScrollMgr::Alter_Scroll();
			INFO_DRAW tDraw = m_tDraw;
			m_tDraw.fx += ptStroll.x;
			m_tDraw.fy += ptStroll.y;

			if (IsRendering())
			{
				this->Render(hDC);
				//this->Render_Info(hDC);
			}
			m_tDraw = tDraw;
		}
		else
		{
			POINTFLOAT ptStroll = CScrollMgr::Alter_Scroll();
			INFO_DRAW tDraw = m_tDraw;
			m_tDraw.fx += ptStroll.x;
			m_tDraw.fy += ptStroll.y;

			if (IsRendering())
			{
				this->Render(hDC);
				this->Render_Info(hDC);
			}

			m_tDraw = tDraw;
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	m_bScrollRender = false;
}

void CObj::Set_Target(CObj * _pTarget)
{
	if (m_pTarget == _pTarget) return;

	Clear_Target();
	if (_pTarget)
	{
		bool isOverlap = false;
		list<CObj*>& listTargetAtMe = _pTarget->Alter_ListTargetedAtMe();
		for (auto& pObj : listTargetAtMe)
		{
			if (pObj == this)
			{
				isOverlap = true;
				break;
			}
		}
		if (false == isOverlap)
			listTargetAtMe.emplace_back(this);
	}
	m_pTarget = _pTarget;
}

void CObj::Clear_Target()
{
	if (m_pTarget)
	{
		list<CObj*>& listTargetAtMe = m_pTarget->Alter_ListTargetedAtMe();
		for (auto& iter = listTargetAtMe.begin(); iter != listTargetAtMe.end();)
		{
			if (this == (*iter))
			{
				*iter = nullptr;
			}
			else ++iter;
		}
		m_pTarget = nullptr;
	}
}

void CObj::Set_Master(CObj * _pMaster)
{
	if (m_pMaster == _pMaster) return;

	Clear_Master();
	if (_pMaster)
	{
		bool isOverlap = false;
		list<CObj*>& listObjMySlaves = _pMaster->Alter_ListObjMySlaves();
		for (auto& pObj : listObjMySlaves)
		{
			if (pObj == this)
			{
				isOverlap = true;
				break;
			}
		}
		if (false == isOverlap)
			listObjMySlaves.emplace_back(this);
	}
	m_pMaster = _pMaster;
}

void CObj::Clear_Master()
{
	if (m_pMaster)
	{
		list<CObj*>& listObjMySlaves = m_pMaster->Alter_ListObjMySlaves();
		for (auto& iter = listObjMySlaves.begin(); iter != listObjMySlaves.end();)
		{
			if (this == (*iter))
			{
				*iter = nullptr;
			}
			else ++iter;
		}
		m_pMaster = nullptr;
	}
}

//애니 메이션
void CObj::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}

bool CObj::IsRendering()
{
	// 컬링 : 일정 범위 안에 존재하는 오브젝트에 대해서만 연산 처리하는 최적화 기법.
	// 좌
	int iScrollX = (int)CScrollMgr::Alter_Scroll().x;
	int iScrollY = (int)CScrollMgr::Alter_Scroll().y;

	int iCullX = abs(iScrollX) / TILECX;
	int iCullY = abs(iScrollY) / TILECY;
	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;
	RECT rtScreen = { iCullX, iCullY, iCullEndX, iCullEndY };
	POINT pt = m_tDraw.Get_Point();

	return (0 == PtInRect(&rtScreen, pt));
}
