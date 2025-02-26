#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();
public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	list<TCHAR*> m_listText;

	int			m_iY;
};

