#include "stdafx.h"
#include "MyFont.h"
#include "KeyMgr.h"
#include "ImgMgr.h"

CMyFont::CMyFont()
	:m_iSelectLen(0)
	, m_iSelect(0)
{
}

CMyFont::~CMyFont()
{
	Release();
}

void CMyFont::Initialize()
{
	//CImgMgr::Get_Instance()->AddImage(L"Effect/MyText.bmp", L"MyText");
	CImgMgr::Get_Instance()->AddImage(L"Effect/MyText.bmp", L"MyText");
	CImgMgr::Get_Instance()->AddImage(L"Effect/RediaUI.bmp", L"RediaUI");
	CImgMgr::Get_Instance()->AddImage(L"Effect/PlayerUI.bmp", L"PlayerUI");
	CImgMgr::Get_Instance()->AddImage(L"Effect/StoreUI.bmp", L"StoreUI");
	//320*360
	m_dwFontTime = GetTickCount();
	m_iWaitFontTime = 60;
}

int CMyFont::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		if (m_iSelectLen >= lstrlen(vecContents[m_iSelect]))
		{
			if (vecContents.size() - 1 > m_iSelect)
			{
				++m_iSelect;
				m_iSelectLen = 0;
			}
			else
			{
				return OBJ_DEAD;
				//종료
			}
		}
		if (m_iSelectLen > 0)
		{
			m_iSelectLen = lstrlen(vecContents[m_iSelect]) - 1;
		}		
	}

	if (m_dwFontTime + m_iWaitFontTime < GetTickCount())
	{
		m_dwFontTime = GetTickCount();
		if (lstrlen(vecContents[m_iSelect]) > m_iSelectLen)
		{
			++m_iSelectLen;
		}
	}
	return 0;
}

void CMyFont::LateUpdate()
{
}

void CMyFont::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(vecImgKey[m_iSelect]);
	GdiTransparentBlt(hDC, 240, 120,
		(int)320, (int)360, hMemDC,
		0, 0,
		(int)320, (int)360,
		RGB(255, 255, 255));

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"MyText");
	/*BitBlt(hDC, 0, 420, 800, 180, hMemDC,
		0, 0, SRCCOPY);*/

	GdiTransparentBlt(hDC, 0, 420,
		(int)800, (int)180, hMemDC,
		0,0,
		(int)800, (int)180,
		RGB(255, 255, 255));

	TCHAR szInfo[100];
	
	RECT rt =m_tDraw.Get_Rect();

	DWORD dwRGB = GetTextColor(hDC);
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD + 100, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움체"));
	HFONT saveFont = (HFONT)SelectObject(hDC, hFont);

	
	if (!lstrcmp(vecImgKey[m_iSelect], L"RediaUI"))
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		swprintf_s(szInfo, L"[리디아]");
	}
	else if (!lstrcmp(vecImgKey[m_iSelect], L"PlayerUI"))
	{
		SetTextColor(hDC, RGB(0, 255, 0));
		swprintf_s(szInfo, L"[레골라스]");
	}
	else if (!lstrcmp(vecImgKey[m_iSelect], L"StoreUI"))
	{
		SetTextColor(hDC, RGB(0, 0, 255));
		swprintf_s(szInfo, L"[상점주인]");
	}
	rt = { 50 + 10, 420 + 27, long(WINCX) - 50,  420 + 65 };
	DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER);
	
	rt = { 50 + 10, 420 + 65, long(WINCX) - 50, long(WINCY) - 50 };
	SetTextColor(hDC, RGB(0, 0, 0));
	swprintf_s(szInfo, L"%s", vecContents[m_iSelect]);
	DrawText(hDC, szInfo, m_iSelectLen, &rt, DT_VCENTER);

	DeleteObject(SelectObject(hDC, saveFont));
	SetTextColor(hDC, dwRGB);
}

void CMyFont::Release()
{
	for (auto& pText : vecContents)
	{
		SAFE_DELETE(pText);
	}
	vecContents.clear();
	vecContents.shrink_to_fit();

	for (auto& pText : vecImgKey)
	{
		SAFE_DELETE(pText);
	}
	vecImgKey.clear();
	vecImgKey.shrink_to_fit();
}

void CMyFont::LateInit()
{
}
