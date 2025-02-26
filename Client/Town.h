#pragma once
#include "Scene.h"

class CTown :
	public CScene
{
public:
	CTown();
	virtual ~CTown();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	INFO_DRAW m_tNextStage;	// 다음 스테이지에 가기 위한 영역
	INFO_DRAW m_tStore;		// 상점에 가기 위한 영역

	CObj*	m_pSelectPlayer;
};

 