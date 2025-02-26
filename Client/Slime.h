#pragma once
#include "Monster.h"
class CSlime :
	public CMonster
{
public:
	CSlime();
	virtual ~CSlime();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void Control();
	virtual void LateInit();


public:
	void Set_Size(POINTFLOAT _ptCrushSize, POINTFLOAT _ptImageSize);
public:
	virtual void SceneChange();

	POINTFLOAT	m_ptSize;
};

