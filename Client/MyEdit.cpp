#include "stdafx.h"
#include "MyEdit.h"

#include "ImgMgr.h"
#include "TileMgr.h"
#include "ScrollMgr.h"

#include "SceneMgr.h"


CMyEdit::CMyEdit()
	:m_bHide(false)
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	/*CImgMgr::Get_Instance()->AddImage(L"Map/Boss.bmp", L"Boss");
	CImgMgr::Get_Instance()->AddImage(L"Map/Dun1.bmp", L"Dun1");
	CImgMgr::Get_Instance()->AddImage(L"Map/Dun2.bmp", L"Dun2");
	CImgMgr::Get_Instance()->AddImage(L"Map/Field.bmp", L"Field");
	CImgMgr::Get_Instance()->AddImage(L"Map/Store.bmp", L"Store");
	CImgMgr::Get_Instance()->AddImage(L"Map/Town.bmp", L"Town");
	CImgMgr::Get_Instance()->AddImage(L"Map/FinishStage.bmp", L"FinishStage");
	CImgMgr::Get_Instance()->AddImage(L"Map/FinishStageBackGround.bmp", L"FinishStageBackGround");*/

	//CTileMgr::Get_Instance()->Initialize();

	m_pFrameKey_Tile = L"Tile_0";
	m_eCurState = CMyEdit::END;
	m_eNextState = CMyEdit::TOWN;
}

int CMyEdit::Update()
{
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		CScrollMgr::Set_ScrollX(20);
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
		CScrollMgr::Set_ScrollX(-20);
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
		CScrollMgr::Set_ScrollY(-20);
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
		CScrollMgr::Set_ScrollY(20);
	if (CKeyMgr::Get_Instance()->KeyDown('F'))
		m_eNextState = CMyEdit::FINISH;


	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		if (false == m_bHide)
		{
			RECT tRectSave = { 0, 33,  50, 60 };
			RECT tRectLoad = { 50, 33,  100, 60 };
			RECT tRectExit = { 100, 33,  150, 60 };
			RECT tRectTownMap = { 0, 60, 150, 170 };
			RECT tRectStoreMap = { 0, 170, 150, 290 };
			RECT tRectFieldMap = { 0, 290, 150, 370 };
			RECT tRectDun1Map = { 0, 370, 150, 450 };
			RECT tRectDun2Map = { 0, 450, 150, 520 };
			RECT tRectBossMap = { 0, 520, 150, 600 };

			if (PtInRect(&tRectSave, pt))
			{
				CTileMgr::Get_Instance()->SaveData(m_eCurState);
			}
			else if (PtInRect(&tRectLoad, pt))
			{
				CTileMgr::Get_Instance()->Release();
				CTileMgr::Get_Instance()->LoadData(m_eCurState);
			}
			else if (PtInRect(&tRectExit, pt))
			{
				CScrollMgr::Alter_Scroll().x = 0;
				CScrollMgr::Alter_Scroll().y = 0;
				CTileMgr::Get_Instance()->Release();
				g_iTileX = 100;
				g_iTileY = 100;
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
			}
			else if (PtInRect(&tRectTownMap, pt))
				m_eNextState = CMyEdit::TOWN;
			else if (PtInRect(&tRectStoreMap, pt))
				m_eNextState = CMyEdit::STORE;
			else if (PtInRect(&tRectFieldMap, pt))
				m_eNextState = CMyEdit::FIELD;
			else if (PtInRect(&tRectDun1Map, pt))
				m_eNextState = CMyEdit::DUN1;
			else if (PtInRect(&tRectDun2Map, pt))
				m_eNextState = CMyEdit::DUN2;
			else if (PtInRect(&tRectBossMap, pt))
				m_eNextState = CMyEdit::BOSS;

		}

		int iScrollX = (int)CScrollMgr::Alter_Scroll().x;
		int iScrollY = (int)CScrollMgr::Alter_Scroll().y;
		pt.x -= iScrollX;
		pt.y -= iScrollY;
		CTileMgr::Get_Instance()->PickTile(pt, 1, 1, m_pFrameKey_Tile);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('K'))
	{
		CTileMgr::Get_Instance()->SaveData(m_eCurState);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		CTileMgr::Get_Instance()->Release();
		CTileMgr::Get_Instance()->LoadData(m_eCurState);
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_TAB))
	{
		m_bHide = !m_bHide;
	}
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
		m_pFrameKey_Tile = L"Tile_0";
	else if (CKeyMgr::Get_Instance()->KeyDown('2'))
		m_pFrameKey_Tile = L"Tile_1";
	else if (CKeyMgr::Get_Instance()->KeyDown('3'))
		m_pFrameKey_Tile = L"Tile_2";
	else if (CKeyMgr::Get_Instance()->KeyDown('4'))
		m_pFrameKey_Tile = L"Tile_3";
	else if (CKeyMgr::Get_Instance()->KeyDown('5'))
		m_pFrameKey_Tile = L"Tile_4";
	else if (CKeyMgr::Get_Instance()->KeyDown('6'))
		m_pFrameKey_Tile = L"Tile_5";
	else if (CKeyMgr::Get_Instance()->KeyDown('7'))
		m_pFrameKey_Tile = L"Tile_6";
	else if (CKeyMgr::Get_Instance()->KeyDown('8'))
		m_pFrameKey_Tile = L"Tile_7";

	
		
	
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyEdit::LateUpdate()
{
	MapChange();
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyEdit::Render(HDC hDC)
{
	POINTFLOAT pt = CScrollMgr::Alter_Scroll();
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey);
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, -(int)pt.x, -(int)pt.y, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);

	if (false == m_bHide)
	{
		hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Tile_Edit");
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CImgMgr::Get_Instance()->GetImgDC(m_pFrameKey_Tile);
		BitBlt(hDC, 1, 1, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	}

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release()
{
	/*CImgMgr::Get_Instance()->EraseImgDC(L"Boss");
	CImgMgr::Get_Instance()->EraseImgDC(L"Dun1");
	CImgMgr::Get_Instance()->EraseImgDC(L"Dun2");
	CImgMgr::Get_Instance()->EraseImgDC(L"Field");
	CImgMgr::Get_Instance()->EraseImgDC(L"Store");
	CImgMgr::Get_Instance()->EraseImgDC(L"Town");*/
}

void CMyEdit::MapChange()
{
	if (m_eCurState != m_eNextState)
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CTileMgr::Get_Instance()->Release();
		switch (m_eNextState)
		{
		case CMyEdit::TOWN:
			m_pFrameKey = L"Town";
			g_iTileX = 53;
			g_iTileY = 40;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::STORE:
			m_pFrameKey = L"Store";
			g_iTileX = 42;
			g_iTileY = 33;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::FIELD:
			m_pFrameKey = L"Field";
			g_iTileX = 106;
			g_iTileY = 56;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::DUN1:
			m_pFrameKey = L"Dun1";
			g_iTileX = 83;
			g_iTileY = 43;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::DUN2:
			m_pFrameKey = L"Dun2";
			g_iTileX = 113;
			g_iTileY = 57;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::BOSS:
			m_pFrameKey = L"Boss";
			g_iTileX = 130;
			g_iTileY = 68;
			CTileMgr::Get_Instance()->Initialize();
			break;
		case CMyEdit::FINISH:
			m_pFrameKey = L"FinishStage";
			g_iTileX = 50;
			g_iTileY = 22;
			CTileMgr::Get_Instance()->Initialize();
			break;
		}
		m_eCurState = m_eNextState;
	}
}
