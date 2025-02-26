#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	enum STATE { TOWN, STORE, FIELD, DUN1, DUN2, BOSS, FINISH, END };
public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void MapChange();
protected:
	TCHAR* m_pFrameKey_Tile;
	TCHAR* m_pFrameKey;
	STATE m_eCurState;
	STATE m_eNextState;

	bool m_bHide;
};

