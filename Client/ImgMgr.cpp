#include "stdafx.h"
#include "ImgMgr.h"

IMPLEMENT_SINGLETON(CImgMgr)
CImgMgr::CImgMgr()
{
	Initialize();
}

CImgMgr::~CImgMgr()
{
	Release();
}

bool CImgMgr::Initialize()
{
	m_hDC = GetDC(g_hWND);

	/*AddImage(L"타이틀", L"Title.bmp");
	AddImage(L"타운", L"Town.bmp");*/

	return true;
}

void CImgMgr::Release()
{
	for (auto& pPair : m_mapBmp)
	{
		if (pPair.second)
		{
			DeleteDC(pPair.second);
		}
	}
	m_mapBmp.clear();
	ReleaseDC(g_hWND, m_hDC);
}

const HDC & CImgMgr::GetImgDC(const TCHAR * pImageKey)
{
	static HDC hDC_Temp = nullptr;
	map<const TCHAR*, HDC>::iterator iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rObj)
	{
		return !lstrcmp(pImageKey, rObj.first);
	});

	if (m_mapBmp.end() == iter)
	{
		return hDC_Temp;
	}
	return iter->second;
}

void CImgMgr::AddImage(const LPCWSTR _pFileName, const TCHAR* pImageKey)
{
	map<const TCHAR*, HDC>::iterator iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rObj)
	{
		return !lstrcmp(pImageKey, rObj.first);
	});

	if (iter == m_mapBmp.end())
	{
		m_mapBmp.emplace(pImageKey, CreateDC_Image(_pFileName));
	}
	else
	{
	//	MessageBox(g_hWND, L"이미 그림이 있음.", L"CBmpMgr::InsertImage()", MB_OK);
	}
}

void CImgMgr::EraseImgDC(const TCHAR * pImageKey)
{
	map<const TCHAR*, HDC>::iterator iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rObj)
	{
		return !lstrcmp(pImageKey, rObj.first);
	});

	if (iter != m_mapBmp.end())
		m_mapBmp.erase(iter);
}

HDC CImgMgr::CreateDC_Image(const LPCWSTR _pFileName)
{
	swprintf_s(m_szPath, L"%s", PATH_IMAGE);
	wcscat_s(m_szPath, 100, _pFileName);

	HBITMAP hBitImage = nullptr;
	HDC memDC = nullptr;

	hBitImage = (HBITMAP)LoadImage(hInst, m_szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	memDC = CreateCompatibleDC(m_hDC);
	SelectObject(memDC, hBitImage);
	DeleteObject(hBitImage);

	return memDC;
}
