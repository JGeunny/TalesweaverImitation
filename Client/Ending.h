#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	list<TCHAR*> m_listText;

	int			m_iY;
};

