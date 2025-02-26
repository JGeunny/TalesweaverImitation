#pragma once

class CStatePattern;
class CStateMgr
{
public:
	CStateMgr(CStatePattern* _pState);
	virtual ~CStateMgr();

public:
	virtual void Set_State(CStatePattern* _pState);
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
protected:
	CStatePattern* m_pState;
};

