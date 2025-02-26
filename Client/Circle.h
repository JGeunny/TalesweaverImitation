#pragma once
#include "Obj.h"
class CCircle :
	public CObj
{
public:
	enum MONSTERID {SLIME, MONSTER, HUNTER, END};
public:
	CCircle();
	virtual ~CCircle();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	virtual void Set_MonsterID(CCircle::MONSTERID _eMonsterID)
	{
		m_eMonsterID = _eMonsterID;
	}
public:
	void SceneChange();

protected:
	TCHAR* m_pFrameKey;

	CCircle::MONSTERID m_eMonsterID;
};

