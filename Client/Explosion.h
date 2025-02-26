#pragma once
#include "Obj.h"
class CExplosion :
	public CObj
{
public:
	CExplosion();
	virtual ~CExplosion();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	void MoveFrame();
};

