#include "stdafx.h"
#include "Store.h"
#include "ObjMgr.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "ImgMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "Player.h"
#include "InterFace.h"
#include "Store_UI.h"
#include "SoundMgr.h"

#include "ObjMgrBuffer.h"
#include "AbstractFactory.h"
#include "MyFont.h"

CStore::CStore()
	:m_pSelectPlayer(nullptr)
	, m_bReady(false)
	, m_bOpenStore(false)
{
}


CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Store.wav");
	CImgMgr::Get_Instance()->AddImage(L"Npc/F_Button.bmp", L"F_Button");
	//CImgMgr::Get_Instance()->AddImage(L"Map/Store.bmp", L"Store");
	g_iTileX = 42;
	g_iTileY = 33;
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->LoadData(CMyEdit::STORE);
	CTileMgr::Get_Instance()->Hide();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	CObjMgr::Get_Instance()->Initialize();

	m_pSelectPlayer = new CPlayer;// 플레이어를 찾음
	auto& listObj = *CObjMgr::Get_Instance()->Get_List(OBJID::UNIT);
	for (auto& pUnit : listObj)
	{
		if (dynamic_cast<CPlayer*>(pUnit))
		{
			m_pSelectPlayer->Set_Target(pUnit);
		}
	}

	// 마을에 가기 위한 영역
	m_tTown.fx = 1000;
	m_tTown.fy = 800;
	m_tTown.fcx = 100;
	m_tTown.fcy = 100;

	// 상점을 열기 위한 영역
	m_tStore.fx = 900;
	m_tStore.fy = 500;
	m_tStore.fcx = 100;
	m_tStore.fcy = 100;
}

int CStore::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('M'))	//필드로 넘어감
	{
		CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::Store_UI];
		if (pUI)
		{
			static_cast<CStore_UI*>(pUI)->Store_Close();
		}
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_FIELD);
		return 0;
	}

	if (m_pSelectPlayer)
	{
		CObj* pPlayer = m_pSelectPlayer->Get_Target();

		m_bReady = false;
		INFO_DRAW	tDrawTarget = pPlayer->Get_Info();
		float fDist = tDrawTarget.Get_Dist(m_tStore.fx, m_tStore.fy);
		if (fDist < 150)
		{
			m_bReady = true;
		}


		if (pPlayer)
		{
			// 타운으로 나가기
			if (IntersectRect(&RECT(), pPlayer->Get_Rect(), &m_tTown.Get_Rect()))
			{
				CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::Store_UI];
				if (pUI)
				{
					static_cast<CStore_UI*>(pUI)->Store_Close();
				}
				CScrollMgr::Alter_Scroll().x = 0;
				CScrollMgr::Alter_Scroll().y = 0;
				CTileMgr::Get_Instance()->Release();
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_TOWN);
				return 0;
			}


			CObj* pUI = CInterFace::Get_Instance()->pInterFace[CInterFace::Store_UI];
			if (m_bReady)// 대화
			{
				if (CKeyMgr::Get_Instance()->KeyDown('F'))
				{
					CSoundMgr::Get_Instance()->MyPlaySound(L"BenyaClick0.wav", CSoundMgr::CHANNELID::NPC);

					CObj* pFont = CAbstractFactory<CMyFont>::Create(TEAM_MOUSE);
					auto& vecText = static_cast<CMyFont*>(pFont)->Alter_Contents();
					TCHAR* pText = new TCHAR[100];
					lstrcpy(pText, L"어서오세요~ 상점입니다!");
					vecText.emplace_back(pText);
					pText = new TCHAR[100];
					lstrcpy(pText, L"좋은 물건이 많네요!");
					vecText.emplace_back(pText);
					pText = new TCHAR[100];
					lstrcpy(pText, L"감사합니다!");
					vecText.emplace_back(pText);

					auto& vecImgKey = static_cast<CMyFont*>(pFont)->Alter_ImgKey();
					pText = new TCHAR[100];
					lstrcpy(pText, L"StoreUI");
					vecImgKey.emplace_back(pText);
					pText = new TCHAR[100];
					lstrcpy(pText, L"PlayerUI");
					vecImgKey.emplace_back(pText);
					pText = new TCHAR[100];
					lstrcpy(pText, L"StoreUI");
					vecImgKey.emplace_back(pText);

					CObjMgrBuffer::Get_Instance()->AddObject(OBJID::MYFONT, pFont);


					static_cast<CStore_UI*>(pUI)->Store_Open();
					m_bOpenStore = true;
				}
			}
			else
			{
				static_cast<CStore_UI*>(pUI)->Store_Close();
				m_bOpenStore = false;
			}
		}
	}
	return 0;
}

void CStore::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStore::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Store");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, WINCX, WINCY, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	/*INFO_DRAW tTrigger = m_tStore;
	tTrigger.fx += (int)pt.x;
	tTrigger.fy += (int)pt.y;
	RECT rt = tTrigger.Get_Rect();
	Rectangle(hDC, rt.left, rt.top , rt.right, rt.bottom);*/

	if (false == m_bOpenStore)
	{
		if (m_pSelectPlayer->Get_Target() && m_bReady)
		{
			INFO_DRAW tDraw = m_pSelectPlayer->Get_Target()->Get_Info();
			POINTFLOAT ptStroll = CScrollMgr::Alter_Scroll();
			tDraw.fx += ptStroll.x;
			tDraw.fy += ptStroll.y;

			RECT rt = tDraw.Get_Rect();
			rt.bottom = rt.top;
			rt.top -= 50;
			rt.left += 5;


			HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"F_Button");
			GdiTransparentBlt(hDC, rt.left, rt.top,
				40, 43, hMemDC,
				0, 0,
				40, 43,
				RGB(255, 0, 255));
		}
	}
}

void CStore::Release()
{
	//CImgMgr::Get_Instance()->EraseImgDC(L"Store");
	SAFE_DELETE(m_pSelectPlayer);
}

void CStore::LateInit()
{
}
