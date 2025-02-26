#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)
CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::KeyPressing(int iKey)
{
	//0x0000
	//0x0001
	//0x8000
	//0x8001
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		return true;
	}
	return false;
}

bool CKeyMgr::KeyDown(int iKey, CKeyMgr::ID _eMod)
{
	if ((GetAsyncKeyState(iKey) & 0x8000))
	{
		if (!m_bKeyState[_eMod][iKey] && (GetAsyncKeyState(iKey) & 0x8000))
		{
			m_bKeyState[_eMod][iKey] = !m_bKeyState[iKey];
			return true;
		}
	}
	return false;
}

bool CKeyMgr::KeyUp(int iKey, CKeyMgr::ID _eMod)
{
	if (m_bKeyState[_eMod][iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[_eMod][iKey] = !m_bKeyState[iKey];
		return true;
	}
	return false;
}

void CKeyMgr::KeyUpdate()
{
	for (int j = 0; j < CKeyMgr::END; ++j)
	{
		for (int i = 0; i < VK_MAX; ++i)
		{
			if (m_bKeyState[j][i] && !(GetAsyncKeyState(i) & 0x8000))
				m_bKeyState[j][i] = !m_bKeyState[j][i];
			if (!m_bKeyState[j][i] && (GetAsyncKeyState(i) & 0x8000))
				m_bKeyState[j][i] = !m_bKeyState[j][i];
		}
	}
}
