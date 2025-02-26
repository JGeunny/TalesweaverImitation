#pragma once
#include "Obj.h"
class CEquip :
	public CObj
{
public:
	CEquip();
	virtual ~CEquip();

public:
	enum ID {HEAD, ARMOR, ARMS, HAND, FOOT, END};
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	CObj*& Alter_Item(CEquip::ID _eItem)
	{
		return m_pItem[_eItem];
	}
protected:
	CObj* m_pItem[CEquip::ID::END];
	RECT m_rtItem[CEquip::ID::END];
};

