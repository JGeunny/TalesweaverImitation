#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
public:
	CLoading();
	virtual ~CLoading();

public:
	enum STATE { LOGO, MAP, UNIT, SKILL, EFFECT, UI, END};

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iNextLoading;
	TCHAR	m_szLoadingInfo[30];
	CLoading::STATE m_eState;

};

