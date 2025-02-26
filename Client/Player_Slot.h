#pragma once
#include "Obj.h"
class CPlayer_Slot :
	public CObj
{
public:
	CPlayer_Slot();
	virtual ~CPlayer_Slot();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	CObj* m_pItem_Hp;
	CObj* m_pItem_Pet;
};

