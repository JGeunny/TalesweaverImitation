#pragma once
#include "Obj.h"
class CMyFont :
	public CObj
{
public:
	CMyFont();
	virtual ~CMyFont();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	vector<TCHAR*>& Alter_Contents() {return vecContents;}

	vector<TCHAR*>& Alter_ImgKey() { return vecImgKey; }
	//vector<int*>& Alter_ImgScene() { return vecImgScene; }

public:
	vector<TCHAR*> vecContents;//�۾��� �ִ� ����
	vector<TCHAR*> vecImgKey; //�̹����� ����� �̹��� Ű
	//vector<int*> vecImgScene; //� �̹����� ����ٲ��� �����ϴ� Ű
	int	m_iSelect;
	int m_iSelectLen;

	DWORD	m_dwFontTime;
	int		m_iWaitFontTime;


};

