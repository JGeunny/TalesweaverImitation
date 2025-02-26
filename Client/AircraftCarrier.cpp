#include "stdafx.h"
#include "AircraftCarrier.h"
#include "Turret.h"
#include "GrenadeTurret.h"
#include "MissileTurret.h"
#include "ImgMgr.h"
#include "ObjMgrBuffer.h"
#include "Explosion.h"

CAircraftCarrier::CAircraftCarrier()
	:m_fRunSpeed(-2)
	, m_bRunEnd(false)
{
	//m_bHideHpBar = true;
	memset(m_tFramePerson, 0, sizeof(m_tFramePerson));
	memset(m_tDrawPerson, 0, sizeof(m_tDrawPerson));
	m_bObjState[OBJ_STATEID::OVERPOWER] = true;
}

CAircraftCarrier::~CAircraftCarrier()
{
}

void CAircraftCarrier::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Boss/BossLive.bmp", L"BossLive");
	CImgMgr::Get_Instance()->AddImage(L"Boss/BossDead.bmp", L"BossDead");

	CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson1.bmp", L"AirshipPerson1");
	CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson2.bmp", L"AirshipPerson2");
	CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson3.bmp", L"AirshipPerson3");
	CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson4.bmp", L"AirshipPerson4");


	m_pFrameKey = L"BossLive";
	
	DWORD dwNowTime = GetTickCount();
	for (auto& tFrame : m_tFramePerson)
	{
		tFrame.dwFrameSpeed = 200;
		tFrame.dwFrameTime = dwNowTime;
	}
	m_pFrameKeyPerson[0] = L"AirshipPerson1";
	m_pFrameKeyPerson[1] = L"AirshipPerson2";
	m_pFrameKeyPerson[2] = L"AirshipPerson3";
	m_pFrameKeyPerson[3] = L"AirshipPerson4";

	m_tFramePerson[0].iFrameEnd = 3;
	m_tFramePerson[1].iFrameEnd = 2;
	m_tFramePerson[2].iFrameEnd = 19;
	m_tFramePerson[3].iFrameEnd = 6;

	m_tDrawPerson[0].fx = -240;
	m_tDrawPerson[0].fy = 5;
	m_tDrawPerson[0].fcx = 48;
	m_tDrawPerson[0].fcy = 46;

	m_tDrawPerson[1].fx = 264;
	m_tDrawPerson[1].fy = 13;
	m_tDrawPerson[1].fcx = 32;
	m_tDrawPerson[1].fcy = 32;

	m_tDrawPerson[2].fx = 229;
	m_tDrawPerson[2].fy = 3;
	m_tDrawPerson[2].fcx = 40;
	m_tDrawPerson[2].fcy = 44;

	m_tDrawPerson[3].fx = 192;
	m_tDrawPerson[3].fy = 3;
	m_tDrawPerson[3].fcx = 45;
	m_tDrawPerson[3].fcy = 43;

	m_tDraw.fSpeed = 2;

	//포탑 1
	m_tDrawSlaves[0].fx = -505;
	m_tDrawSlaves[0].fy = 15;

	m_tDrawSlaves[1].fx = -600;
	m_tDrawSlaves[1].fy = 15;

	//수류탄 포탑
	m_tDrawSlaves[2].fx = -400;
	m_tDrawSlaves[2].fy = 15;

	//미사일 포탑
	m_tDrawSlaves[3].fx = 100;
	m_tDrawSlaves[3].fy = 15;
}

int CAircraftCarrier::Update()
{
	if (m_bObjState[UNIT_STATEID::DEAD])
		return OBJ_DEAD;

	CObj::LateInit();
	DWORD m_dwNowTime = GetTickCount();

	if (m_bObjState[OBJ_STATEID::DEAD])
	{
		//m_pFrameKey = L"BossDead";
		if (m_dwObjTime[OBJ_TIMEID::DEAD] + 100 < m_dwNowTime)
		{
			POINTFLOAT pt = { m_tDraw.fx, m_tDraw.fy };
			pt.x += (rand() % 1000) - 500;
			pt.y += (rand() % 150) - 75;
			CObj* pExplosion = CAbstractFactory<CExplosion>::Create(TEAM_MOUSE, pt.x, pt.y);
			CObjMgrBuffer::Get_Instance()->Get_List()[OBJID::EFFECT].emplace_back(pExplosion);
			m_dwObjTime[OBJ_TIMEID::DEAD] = GetTickCount();
		}
		return OBJ_NOEVENT;
	}
	if (1200 < m_tDraw.fx)
		m_tDraw.fSpeed = -1 * abs(m_tDraw.fSpeed);
	if (800 > m_tDraw.fx)
		m_tDraw.fSpeed = abs(m_tDraw.fSpeed);
	m_tDraw.fx += m_tDraw.fSpeed;


	int i = 0;
	int j = 0;
	for (auto& pSlaves : m_listObjMySlaves)
	{
		if (pSlaves != nullptr)
		{
			INFO_DRAW& rDraw_Slaves = pSlaves->Alter_Draw();
			rDraw_Slaves.fx = m_tDraw.fx + m_tDrawSlaves[i].fx;
			rDraw_Slaves.fy = m_tDraw.fy + m_tDrawSlaves[i].fy;
			if (m_bObjState[OBJ_STATEID::OVERPOWER] == true)
			{
				if (pSlaves->Get_Dead())
					++j;
			}
		}
		++i;
	}

	if (false == m_bObjState[OBJ_STATEID::RUN])
	{
		if (j >= 4)
		{
			m_bObjState[OBJ_STATEID::OVERPOWER] = false;
			m_bObjState[OBJ_STATEID::RUN] = true;
			m_bRunEnd = false;
			m_dwObjTime[OBJ_TIMEID::RUN] = m_dwNowTime;
		}
	}

	if (m_dwObjTime[OBJ_TIMEID::RUN] + 6000 < m_dwNowTime)
	{
		if (true == m_bObjState[OBJ_STATEID::RUN])
		{
			m_tDraw.fy += m_fRunSpeed;
			if (false == m_bRunEnd)
			{
				m_fRunSpeed = -1 * abs(m_fRunSpeed);
				if (m_tDraw.fy < -150)
				{
					m_bRunEnd = true;

					// 회복
					m_bObjState[OBJ_STATEID::OVERPOWER] = true;
					for (auto& pSlaves : m_listObjMySlaves)
					{
						pSlaves->Set_Dead(false);
						INFO_UNIT tUnit = static_cast<CUnit*>(pSlaves)->Get_Unit();
						tUnit.Fn_Recovery();
						static_cast<CUnit*>(pSlaves)->Set_Unit(tUnit);
					}
				}
			}
			if (true == m_bRunEnd)
			{
				m_fRunSpeed = abs(m_fRunSpeed);
				if (m_tDraw.fy > 75)
				{
					m_tDraw.fy = 75;
					m_bRunEnd = false;
					m_bObjState[OBJ_STATEID::RUN] = false;
				}
			}
		}
	}
	
	/*if (m_bObjState[OBJ_STATEID::OVERPOWER] == false)//회복
	{
		if (m_dwObjTime[OBJ_TIMEID::RECOVERY] + 6000 < m_dwNowTime)
		{
			m_bObjState[OBJ_STATEID::OVERPOWER] = true;
			for (auto& pSlaves : m_listObjMySlaves)
			{
				pSlaves->Set_Dead(false);
				INFO_UNIT tUnit = static_cast<CUnit*>(pSlaves)->Get_Unit();
				tUnit.Fn_Recovery();
				static_cast<CUnit*>(pSlaves)->Set_Unit(tUnit);
			}
		}
	}*/
	return OBJ_NOEVENT;
}

void CAircraftCarrier::LateUpdate()
{
	CAircraftCarrier::MoveFrameAircraft();
}

void CAircraftCarrier::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fx -= 200;
	tDraw.fcx = 1300;
	tDraw.fcy = 150;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(255, 0, 255));

	for (int i = 0; i < 4; ++i)
	{
		tDraw = m_tDraw;
		tDraw.fx += m_tDrawPerson[i].fx;
		tDraw.fy += m_tDrawPerson[i].fy;
		tDraw.fcx = m_tDrawPerson[i].fcx;
		tDraw.fcy = m_tDrawPerson[i].fcy;
		tRect = tDraw.Get_Rect();
		hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKeyPerson[i]);
		GdiTransparentBlt(hDC, tRect.left, tRect.top,
			(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
			(int)tDraw.fcx * m_tFramePerson[i].iFrameStart,
			(int)tDraw.fcy * m_tFramePerson[i].iFrameScene,
			(int)tDraw.fcx, (int)tDraw.fcy,
			RGB(255, 0, 255));
	}
}

void CAircraftCarrier::Release()
{
}

void CAircraftCarrier::LateInit()
{
	m_tDraw.fx = 1000;
	m_tDraw.fy = 75;
	m_tDraw.fcx = 600;
	m_tDraw.fcy = 130;
	m_tUnit.iGold = 777777;

	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT,
		CAbstractFactory<CTurret>::Create_Unit_Slave(this, 500, 500, 0, L"비행선의 기관포1", 80, 1600));
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT,
		CAbstractFactory<CTurret>::Create_Unit_Slave(this, 500, 500, 0, L"비행선의 기관포2", 80, 1600));
	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT,
		CAbstractFactory<CGrenadeTurret>::Create_Unit_Slave(this, 500, 500, 0, L"비행선의 수류탄 포탑", 80, 1600));

	CObjMgrBuffer::Get_Instance()->AddObject(OBJID::UNIT,
		CAbstractFactory<CMissileTurret>::Create_Unit_Slave(this, 500, 500, 0, L"비행선의 미사일 포탑", 80, 1600));
}

void CAircraftCarrier::MoveFrameAircraft()
{
	DWORD dwNowTime = GetTickCount();
	for (auto& tFrame : m_tFramePerson)
	{
		if (tFrame.dwFrameTime + tFrame.dwFrameSpeed < dwNowTime)
		{
			++tFrame.iFrameStart;
			tFrame.dwFrameTime = GetTickCount();
		}

		if (tFrame.iFrameStart > tFrame.iFrameEnd)
			tFrame.iFrameStart = 0;
	}
}