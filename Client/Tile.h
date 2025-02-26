#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	int Get_DrawID() { return m_iDrawID; }
	int Get_Option() { return m_iOption; }
	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void Set_Option(int _iOption) { m_iOption = _iOption; }

public:
	void Set_FrameKey(TCHAR* _pFrameKey) { lstrcpy(m_szFrameKey, _pFrameKey);}
	TCHAR* Get_FrameKey() { return m_szFrameKey; }

protected:
	TCHAR m_szFrameKey[100];

	int m_iDrawID;
	int m_iOption;
};

