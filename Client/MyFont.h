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
	vector<TCHAR*> vecContents;//글씨를 넣는 변수
	vector<TCHAR*> vecImgKey; //이미지를 띄워줄 이미지 키
	//vector<int*> vecImgScene; //어떤 이미지를 띄워줄껀지 결정하는 키
	int	m_iSelect;
	int m_iSelectLen;

	DWORD	m_dwFontTime;
	int		m_iWaitFontTime;


};

