#include "stdafx.h"
#include "Skill.h"
#include "SoundMgr.h"

CSkill::CSkill()
	:m_iOption(0)
{

}

CSkill::~CSkill()
{
}

void CSkill::Initialize()
{
	m_tDraw.Initialize(300, 400, 50, 50, 10, 0);
	m_iObjTimeCount[OBJ_TIMEID::LIVE] = 200;

	m_dwValidityTime = 500;
}

int CSkill::Update()
{
	if (m_bObjState[OBJ_STATEID::DEAD])
		return OBJ_DEAD;
	CObj::LateInit();
	CObj::LiveTime();

	return OBJ_NOEVENT;
}

void CSkill::LateUpdate()
{
}

void CSkill::Render(HDC hDC)
{
	/*RECT rt = m_tDraw.Get_Rect();
	Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);*/
}

void CSkill::Release()
{
//	SAFE_DELETE(m_pRotatePos);
	m_mapUnitAttackTime.clear();

}

void CSkill::LateInit()
{
}

void CSkill::Set_ImgDir(float _fAngle)
{
	int iAngle = int(m_tDraw.fAngle + 45) % 360;
	if (iAngle < 0)
		iAngle = 360 + iAngle;

	int iDir = iAngle / 45;
	switch (iDir)
	{
	case 0:
		m_tFrame.iFrameStart = 6;
		m_tFrame.iFrameEnd = 6;
		break;
	case 1:
		m_tFrame.iFrameStart = 5;
		m_tFrame.iFrameEnd = 5;
		break;
	case 2:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		break;
	case 3:
		m_tFrame.iFrameStart = 2;
		m_tFrame.iFrameEnd = 2;
		break;
	case 4:
		m_tFrame.iFrameStart = 3;
		m_tFrame.iFrameEnd = 3;
		break;
	case 5:
		m_tFrame.iFrameStart = 4;
		m_tFrame.iFrameEnd = 4;
		break;
	case 6:
		m_tFrame.iFrameStart = 1;
		m_tFrame.iFrameEnd = 1;
		break;
	case 7:
		m_tFrame.iFrameStart = 7;
		m_tFrame.iFrameEnd = 7;
		break;
	}
	/*if (0 > iDir || m_listImgDir.size() <= iDir)
	{
	}
	else
		m_pFrameKey = m_listImgDir[iDir];*/
}

//또공격 했는지 체크 하고 만약 때린뒤 m_dwValidityTime 시간이 지났다면 또 때릴수있음
bool CSkill::IsHit_Unit(CObj * pUnit)
{
	DWORD dwNow = GetTickCount();
	bool IsHit = false;
	if (m_mapUnitAttackTime.find(pUnit) != m_mapUnitAttackTime.end())
	{
		if (m_mapUnitAttackTime[pUnit] + m_dwValidityTime > dwNow)
		{
			IsHit = false;
		}
		else
		{
			m_mapUnitAttackTime[pUnit] = dwNow;
			IsHit = true;
		}
	}
	else
	{
		m_mapUnitAttackTime.insert(map<CObj*, DWORD>::value_type(pUnit, dwNow));
		IsHit = true;
	}
	return IsHit;
}
