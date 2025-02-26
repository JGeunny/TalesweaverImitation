#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "ImgMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)
CTileMgr::CTileMgr()
	: m_bHide(false)
{
	CImgMgr::Get_Instance()->AddImage(L"Tile/Edit.bmp", L"Tile_Edit");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_0.bmp", L"Tile_0");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_1.bmp", L"Tile_1");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_2.bmp", L"Tile_2");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_3.bmp", L"Tile_3");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_4.bmp", L"Tile_4");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_5.bmp", L"Tile_5");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_6.bmp", L"Tile_6");
	CImgMgr::Get_Instance()->AddImage(L"Tile/Tile_7.bmp", L"Tile_7");
}


CTileMgr::~CTileMgr()
{
	Release();
}
void CTileMgr::Initialize()
{
	Release();
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//		0	64 = 0 + 32   = 32
			//		1	64 = 64 + 32  = 96
			//		2	64 = 128 + 32 = 160
			float fx = (j * TILECX) + (TILECX * 0.5f);
			float fY = (i * TILECY) + (TILECY * 0.5f);

			CObj* pObj = CAbstractFactory<CTile>::Create(TEAM_TILE, fx, fY);
			m_vecTile.emplace_back(pObj);
		}
	}
}
void CTileMgr::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown('N'))
		m_bHide = !m_bHide;
}

void CTileMgr::LateUpdate()
{

}

void CTileMgr::Render(HDC hDC)
{
	if (m_bHide) return;
	// 컬링 : 일정 범위 안에 존재하는 오브젝트에 대해서만 연산 처리하는 최적화 기법. 
	// 좌 
	int iScrollX = (int)CScrollMgr::Alter_Scroll().x;
	int iScrollY = (int)CScrollMgr::Alter_Scroll().y;
	
	int iCullX = abs(iScrollX) / TILECX;
	int iCullY = abs(iScrollY) / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 2; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (TILEX * i);
			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
			{
				return;
			}
			m_vecTile[iIndex]->Render(hDC);
		}
	}
	// 	for (auto& pTile : m_vecTile)
	// 	{
	// 		pTile->Render(hDC);
	// 	}
}

void CTileMgr::Release()
{
	for (auto& pTile : m_vecTile)
	{
		SAFE_DELETE(pTile);
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::PickTile(POINT & pt, int iDrawID, int iOption, TCHAR* _pFrameKey)
{
	int x = pt.x / TILECX;
	int y = pt.y / TILECY;
	int iIndex = x + (TILEX * y);
	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
	{
		return;
	}
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_FrameKey(_pFrameKey);


}

void CTileMgr::SaveData(CMyEdit::STATE _eState)
{
	TCHAR szFileName[100];
	swprintf_s(szFileName, L"../Data/Tile_%d.dat", _eState);
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWND, L"세이브 실패!", L"CTileMgr::SaveData()", MB_OK);
		return;
	}
	int iDrawID = 0, iOption = 0;
	TCHAR szFrameKey[100];
	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();
		lstrcpy(szFrameKey, dynamic_cast<CTile*>(pTile)->Get_FrameKey());

		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO_DRAW), &dwByte, nullptr);
		//WriteFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);
		WriteFile(hFile, &szFrameKey, sizeof(szFrameKey), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWND, L"세이브 성공!", L"CTileMgr::SaveData()", MB_OK);
}

void CTileMgr::LoadData(CMyEdit::STATE _eState)
{
	TCHAR szFileName[100];
	swprintf_s(szFileName, L"../Data/Tile_%d.dat", _eState);
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWND, L"로드 실패!", L"CTileMgr::LoadData()", MB_OK);
		return;
	}
	int iDrawID = 0, iOption = 0;
	TCHAR szFrameKey[100];
	INFO_DRAW tInfo{};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO_DRAW), &dwByte, nullptr);
		//ReadFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);
		ReadFile(hFile, &szFrameKey, sizeof(szFrameKey), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}
		CObj* pObj = CAbstractFactory<CTile>::Create(TEAM_TILE, tInfo.fx, tInfo.fy);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);
		dynamic_cast<CTile*>(pObj)->Set_FrameKey(szFrameKey);

		m_vecTile.emplace_back(pObj);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWND, L"로드 성공!", L"CTileMgr::LoadData()", MB_OK);
}
