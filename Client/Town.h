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
	INFO_DRAW m_tNextStage;	// ���� ���������� ���� ���� ����
	INFO_DRAW m_tStore;		// ������ ���� ���� ����

	CObj*	m_pSelectPlayer;
};

 