#pragma once
#include "Scene.h"

class CStore :
	public CScene
{
public:
	CStore();
	virtual ~CStore();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	INFO_DRAW m_tTown;		// 마을에 가기 위한 영역
	INFO_DRAW m_tStore;		// 상점을 열기 위한 영역

	CObj*	m_pSelectPlayer;

	bool m_bReady;
	bool m_bOpenStore;
};

