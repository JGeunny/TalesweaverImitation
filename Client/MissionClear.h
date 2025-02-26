#pragma once
#include "Obj.h"
class CMissionClear :
	public CObj
{
public:
	CMissionClear();
	virtual ~CMissionClear();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	void MoveFrame();

	void Set_ClearImage(bool _bClearImage) { m_bClearImage = _bClearImage; }

protected:
	bool m_bSizeUp;
	bool m_bClearImage;
};

