#pragma once
#include "Wield.h"
class CThunderWield :
	public CWield
{
public:
	CThunderWield();
	virtual ~CThunderWield();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

protected:
	CRotatePos* m_pRotatePos;
	float		m_fAngle;
};

