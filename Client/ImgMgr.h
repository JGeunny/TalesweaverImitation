#pragma once

typedef struct tagImgSize
{
	int x;
	int y;
	int cx;
	int cy;
}IMGSIZE;

class CImgMgr
{
	DECLARE_SINGLETON(CImgMgr)
private:
	bool Initialize();
public:
	void Release();

public:
	const HDC& GetImgDC(const TCHAR* pImageKey);
	void	   AddImage(const LPCWSTR _pFileName, const TCHAR* pImageKey);

	void	   EraseImgDC(const TCHAR* pImageKey);

public:
	HDC CreateDC_Image(const LPCWSTR _pFileName);
private:
	HDC						m_hDC;
	map<const TCHAR*, HDC>  m_mapBmp;
	WCHAR					m_szPath[100];
};