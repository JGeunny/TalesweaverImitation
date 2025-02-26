#pragma once

class CObj;
class CStatePattern
{
public:
	CStatePattern(CObj* _pObj);
	virtual ~CStatePattern();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	void Set_Obj(CObj* _pObj);

protected:
	CObj* m_pObj;
};

