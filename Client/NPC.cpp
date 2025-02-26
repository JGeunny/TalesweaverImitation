#include "stdafx.h"
#include "NPC.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"

#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"
#include "MyFont.h"

#include "KeyMgr.h"
#include "SceneMgr.h"

#include "SoundMgr.h"

CNPC::CNPC()
	:m_bReady(false)
{
}


CNPC::~CNPC()
{
}

void CNPC::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"Npc/Linda.bmp", L"Linda");
	CImgMgr::Get_Instance()->AddImage(L"Npc/F_Button.bmp", L"F_Button");
	//128*128 12
	m_pFrameKey = L"Linda";
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameStart = 0;

	m_tDraw.fcx = 64;
	m_tDraw.fcy = 128;
}

int CNPC::Update()
{
	m_bReady = false;
	if (m_pTarget)
	{
		INFO_DRAW	tDrawTarget = m_pTarget->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tDraw.fx, m_tDraw.fy);
		if (fDist < 150)
		{
			m_bReady = true;
		}
	}

	if (m_bReady)
	{
		if(CKeyMgr::Get_Instance()->KeyDown('F'))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"BenyaClick1.wav", CSoundMgr::CHANNELID::NPC);
			TCHAR* pText = nullptr;
			switch (CSceneMgr::g_iNextStage)
			{
			case 0:
			{
				CObj* pFont = CAbstractFactory<CMyFont>::Create(TEAM_MOUSE);
				auto& vecText = static_cast<CMyFont*>(pFont)->Alter_Contents();
				pText = new TCHAR[100];
				lstrcpy(pText, L"마을 밖에 슬라임이 있어서 집에 갈수 없어요.... 도와주세요!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"밖에 슬라임이 많이 있다고?! ㅇㅋ 도와드림!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"정말 감사합니다!");
				vecText.emplace_back(pText);

				auto& vecImgKey = static_cast<CMyFont*>(pFont)->Alter_ImgKey();
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"PlayerUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);

				CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pFont);
				break;
			}
			case 1:
			{
				CObj* pFont = CAbstractFactory<CMyFont>::Create(TEAM_MOUSE);
				auto& vecText = static_cast<CMyFont*>(pFont)->Alter_Contents();
				pText = new TCHAR[100];
				lstrcpy(pText, L"동굴안에 적들이 모여있어요 도와주세요!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"ㅇㅋ 도와드림!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"정말 감사합니다!");
				vecText.emplace_back(pText);

				auto& vecImgKey = static_cast<CMyFont*>(pFont)->Alter_ImgKey();
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"PlayerUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);

				CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pFont);
				break;
			}
			case 2:
			{
				CObj* pFont = CAbstractFactory<CMyFont>::Create(TEAM_MOUSE);
				auto& vecText = static_cast<CMyFont*>(pFont)->Alter_Contents();
				pText = new TCHAR[100];
				lstrcpy(pText, L"적들이 우리 마을을 공격하기 위해서 비행선을 띄웠어요!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"ㅇㅋ 도와드림!");
				vecText.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"정말 감사합니다!");
				vecText.emplace_back(pText);

				auto& vecImgKey = static_cast<CMyFont*>(pFont)->Alter_ImgKey();
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"PlayerUI");
				vecImgKey.emplace_back(pText);
				pText = new TCHAR[100];
				lstrcpy(pText, L"RediaUI");
				vecImgKey.emplace_back(pText);

				CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pFont);
				break;
			}
			default:
				break;
			}
			

			//리디아와 대화하기
		}
	}

	return 0;
}

void CNPC::LateUpdate()
{
	CUnit::LateUpdate();
	CObj::MoveFrame();
	CUnit::FSM();
}

void CNPC::Render(HDC hDC)
{
	INFO_DRAW tDraw = m_tDraw;
	tDraw.fx += 32;
	tDraw.fcx = 128;
	tDraw.fcy = 128;
	RECT tRect = tDraw.Get_Rect();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	GdiTransparentBlt(hDC, tRect.left, tRect.top,
		(int)tDraw.fcx, (int)tDraw.fcy, hMemDC,
		(int)tDraw.fcx * m_tFrame.iFrameStart,
		(int)tDraw.fcy * m_tFrame.iFrameScene,
		(int)tDraw.fcx, (int)tDraw.fcy,
		RGB(0, 0, 0));
	/*m_tRect = m_tDraw.Get_Rect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);*/

	if (m_pTarget && m_bReady)
	{
		INFO_DRAW tDraw = m_pTarget->Get_Info();
		if (m_bScrollRender)
		{
			POINTFLOAT ptStroll = CScrollMgr::Alter_Scroll();
			tDraw.fx += ptStroll.x;
			tDraw.fy += ptStroll.y;
		}
		RECT rt = tDraw.Get_Rect();
		rt.bottom = rt.top;
		rt.top -= 50;
		rt.left += 5;
		

		HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"F_Button");
		GdiTransparentBlt(hDC, rt.left, rt.top,
			40, 43, hMemDC,
			0,0,
			40, 43,
			RGB(255, 0, 255));
		/*TCHAR szInfo[100];
		swprintf_s(szInfo, L"[F]");
		DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);*/
	}

}

void CNPC::Release()
{
}

void CNPC::Control()
{
}

void CNPC::LateInit()
{
}
