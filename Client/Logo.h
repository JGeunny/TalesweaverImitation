#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dwNextTime;
	int		m_iNextMaxTime;
	int		m_iNextLogo;
};

