#include "stdafx.h"
#include "Scene.h"
#include "Astar.h"
#include "ObjMgr.h"

CScene::CScene()
	:m_pTarget(nullptr)
	, m_bIsInit(false)
	, m_iTeam(0)
	, m_fRecogDist(300)
	, m_pFieldMap(nullptr)
	, m_pAstar(nullptr)
{
	ZeroMemory(m_bObjState, sizeof(m_bObjState));
}


CScene::~CScene()
{
}

void CScene::LateInit()
{
	if (false == m_bIsInit)
	{
		m_bIsInit = true;
		this->LateInit();
	}
}

void CScene::LiveTime()
{
	if (m_iLiveTime != 0)
	{
		if (m_dwOldTime + m_iLiveTime < GetTickCount())
		{
			Set_Dead(true);
		}
	}
}
