#pragma once
#include "Obj.h"
class CInventory :
	public CObj
{
public:
	CInventory();
	virtual ~CInventory();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	void AddItem(CObj* _pObj);
	int Get_InvenSize() { return m_listItem.size(); }
	list<CObj*>& Alter_ListItem() {return m_listItem;}
protected:
	list<CObj*> m_listItem;
};

