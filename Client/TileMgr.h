#pragma once
#include "MyEdit.h"
class CObj;
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
	
public:
	void PickTile(POINT& pt, int iDrawID, int iOption, TCHAR* _pFrameKey);
	void SaveData(CMyEdit::STATE _eState = CMyEdit::TOWN);
	void LoadData(CMyEdit::STATE _eState = CMyEdit::TOWN);

	void Hide() { m_bHide = true; }
	void Show() { m_bHide = false; }
public:
	vector<CObj*>& Alter_VecTile() { return m_vecTile; }
private:
	vector<CObj*> m_vecTile;
	bool		  m_bHide;
};

