#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();
public:
	void Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void LateInit();

private:
	TCHAR* m_pFrameKey;
	int m_iDrawID;


	bool m_bButtonOver;
};

