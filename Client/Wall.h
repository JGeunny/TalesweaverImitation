#pragma once
#include "Tile.h"
class CWall :
	public CTile
{
public:
	CWall();
	virtual ~CWall();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();
protected:

};

