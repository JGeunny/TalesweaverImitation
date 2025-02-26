#pragma once

class CObj;
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

public:
	static void ReInitialize() { 
		m_ptScroll.x = 0; m_ptScroll.y = 0; m_bHorizontalScroll = false;
	}
	static void Set_ScrollX(float _fSpeed) { m_ptScroll.x += _fSpeed; }
	static void Set_ScrollY(float _fSpeed) { m_ptScroll.y -= _fSpeed; }
	static POINTFLOAT& Alter_Scroll() {return m_ptScroll;}
	static void ScrollObj(list<CObj*>& rSrc);
	static void ScrollLock();
	static void Set_HorizontalScroll(bool _bHorizon) 
	{
		m_bHorizontalScroll = _bHorizon;
	}
public:
	static POINTFLOAT m_ptScroll;

public:
	bool Initialize();
	void LateUpdate();
	void Render(HDC hDC);

public:
	void Release();

public:
	void DoShackIt();

public:
	//애니 메이션
	void MoveFrame();
private:
	//애니메이션
	FRAME		m_tFrame;

	static bool	m_bShakeIt;
	DWORD		m_dwShackItTime;
	int			m_iMovement;
	int			m_iSpeed;

	static bool m_bHorizontalScroll;
};

