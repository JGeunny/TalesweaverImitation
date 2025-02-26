#pragma once
#include "Obj.h"
class CPlayerInfo :
	public CObj
{
public:
	CPlayerInfo();
	virtual ~CPlayerInfo();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

};

