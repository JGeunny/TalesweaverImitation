#pragma once
#include "Scene.h"
class CBoss_Scene :
	public CScene
{
public:
	CBoss_Scene();
	virtual ~CBoss_Scene();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

private:
	int m_iMissionState;
};

