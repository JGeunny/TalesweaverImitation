#pragma once
#include "Bullet.h"
class CBounceBullet :
	public CBullet
{
public:
	CBounceBullet();
	virtual ~CBounceBullet();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

protected:

};

