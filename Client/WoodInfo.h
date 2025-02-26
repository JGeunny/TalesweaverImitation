#pragma once
#include "Obj.h"
class CWoodInfo :
	public CObj
{
public:
	CWoodInfo();
	virtual ~CWoodInfo();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	void Set_Info(TCHAR* _szInfo)
	{
		lstrcpy(m_szInfo, _szInfo);
	}
protected:
	TCHAR m_szInfo[100];
	INFO_DRAW m_tDraw_Wood;
	DWORD	m_dwTime;
};

