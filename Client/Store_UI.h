#pragma once
#include "Obj.h"

class CObj;
class CStore_UI :
	public CObj
{
public:
	CStore_UI();
	virtual ~CStore_UI();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	virtual void Store_Open();
	virtual void Store_Close();

protected:
	list<CObj*> m_listItem;
};

 