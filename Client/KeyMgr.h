#pragma once
#define VK_MAX 0xff
class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
public:
	enum ID {BASE, SPECIAL, END};
public:
	bool KeyPressing(int iKey);
	bool KeyDown(int iKey, CKeyMgr::ID _eMod = BASE);
	bool KeyUp(int iKey, CKeyMgr::ID _eMod = BASE);
	void KeyUpdate();
private:
	bool m_bKeyState[CKeyMgr::END][VK_MAX];
};

