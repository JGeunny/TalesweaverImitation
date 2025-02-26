#pragma once

class CObj;
class CController
{
public:
	CController();
	~CController();
private:
	bool Initialize();

public:
	static CController* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CController;
		}
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete  m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Set_Target(CObj* pObj);
	void Set_Mouse(CObj* pObj);
	CObj* Get_Target();
	CObj* Get_Mouse();
public:
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
private:
	static CController* m_pInstance;
	CObj*				m_pTarget;
	CObj*				m_pMouse;
};