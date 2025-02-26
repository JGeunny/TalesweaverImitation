#pragma once

class CObj;
class CInterFace
{
	DECLARE_SINGLETON(CInterFace)
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();
public:
	enum ID { PlayerInfo, BossInfo, Score, PlayerStatus,
		Inventory, Store_UI, Player_Slot, Equip, END
	};
public:
	vector<CObj*> m_vecUI;

	CObj* pInterFace[CInterFace::END];
};

