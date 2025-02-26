#pragma once
#include "Obj.h"
class CAirplane :
	public CObj
{
public:
	CAirplane();
	virtual ~CAirplane();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
};

