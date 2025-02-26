#pragma once
#include "Obj.h"
class CUnit :
	public CObj
{
public:
	CUnit();
	virtual ~CUnit();

public:
	//enum ESTATE { IDLE, WALK, SLIDING, ATT, BEATTED, HIT, DIE, END };

public:
	virtual void Initialize();
	virtual int Update() = 0;
	virtual void LateUpdate();
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
	virtual void FSM();// ���� ���� ���(�⺻���� �ΰ�����)
public:
	virtual void Render_Info(HDC hDC);
public:
	INFO_UNIT& Alter_UnitInfo() { return m_tUnit; }
	bool& Alter_UnitState(UNIT_STATEID::ID _eId) { return m_bUnit_State[_eId]; }

public:
	const INFO_UNIT& Get_Unit() const { return m_tUnit; }
	void Set_Unit(INFO_UNIT _tUnit) { m_tUnit = _tUnit;}

public:
	void Set_FrameKey(TCHAR* _pFrameKey) {m_pFrameKey = _pFrameKey;}
	TCHAR* Get_FrameKey() { return m_pFrameKey; }

public:
	virtual void Set_ImgDir(float _fAngle);
	virtual void SceneChange() {};

protected:
	INFO_UNIT	m_tUnit;
	bool		m_bUnit_State[UNIT_STATEID::END];
	int			m_iBeAttacked_Hp;//HP�� ���̸� �̿��Ͽ� �������� ���Դ��� �Ǻ�

	//�ִϸ��̼�
	vector<TCHAR*> m_listImgDir;	//������, ������ ��, ��, ���� ��, ���� -> �ݽð�������� 8�� �ֱ�
	TCHAR* m_pFrameKey;
	UNIT_STATEID::ID m_eCurState;
	UNIT_STATEID::ID m_eNextState;
};

