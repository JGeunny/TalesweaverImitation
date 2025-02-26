#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();
public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void Set_Attack(bool _bAttack) {m_bAttack = _bAttack;}
private:
	int		m_iDrawID;
	DWORD	m_dwNextTime;
	int		m_iNextMaxTime;
	int		m_iNextLogo;

	bool	m_bAttack;
};

