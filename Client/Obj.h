#pragma once

#include "KeyMgr.h"
#include "ObjMgr.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
	virtual void LateInit();

	virtual void Control() {};
	virtual void LiveTime();

public:
	virtual void MessageTo(int _iEvent);

public:
	virtual void Render_Scroll(HDC hDC);
	virtual void Render_Info(HDC hDC) {}
public:
	const float& Get_RecogDist() const {return m_fRecogDist;}
	void Set_RecogDist(float _fRecogDist) { m_fRecogDist = _fRecogDist; }

	void Set_Speed(float _fSpeed) { m_tDraw.fSpeed = _fSpeed; }
	const float& Get_Speed() const { return m_tDraw.fSpeed;}

	int& Alter_TimeCount(OBJ_TIMEID::ID eId) { return m_iObjTimeCount[eId]; }

	//��ǥ Ÿ����
	void Set_Target(CObj* _pTarget);
	CObj* Get_Target(){ return m_pTarget; }
	void Clear_Target();

	//���� ����
	void Set_Master(CObj* _pMaster);
	CObj* Get_Master() { return m_pMaster; }
	void Clear_Master();

	//�ִ� ���̼�
	void MoveFrame();

	list<CObj*>& Alter_ListTargetedAtMe() { return m_listObjTargetedAtMe; }
	list<CObj*>& Alter_ListObjMySlaves() { return m_listObjMySlaves; }

	void Set_Team(int _iTeam) { m_iTeam = _iTeam; }
	const int& Get_Team() const { return m_iTeam; }

	void Set_Angle(float _fAngle) { m_tDraw.fAngle = _fAngle; }
	const float& Get_Angle() const { return m_tDraw.fAngle; }

	void Set_Pos(float x, float y){
		m_tDraw.fx = x;m_tDraw.fy = y;	}

	void Set_Dead(bool _bDead) { m_bObjState[OBJ_STATEID::DEAD] = _bDead; }
	const bool& Get_Dead() const { return m_bObjState[OBJ_STATEID::DEAD]; }

	bool& Alter_ObjState(OBJ_STATEID::ID _eId) { return m_bObjState[_eId]; }
	INFO_DRAW& Alter_Draw(void) { return m_tDraw; }
	void Set_Info(INFO_DRAW _tDraw) { m_tDraw = _tDraw; }
	const INFO_DRAW& Get_Info(void)const { return m_tDraw; }
	

	RECT* Get_Rect() {m_tRect = m_tDraw.Get_Rect(); return &m_tRect; }

	bool IsRendering();

	//Ȱ��ȭ
	bool& Alter_Activation() { return m_bActivation;}

public:
	//��ų ����
	float& Alter_Angle_Skill() {return m_fAngle_Skill;}
protected:
	bool		m_bIsInit;
	INFO_DRAW	m_tDraw;
	bool		m_bObjState[OBJ_STATEID::END];
	RECT		m_tRect;

	//��ǥ Ÿ����
	list<CObj*>	m_listObjTargetedAtMe;	//���� Ÿ������ ���
	CObj*		m_pTarget;				//���� Ÿ������ ��

	//���� ����
	list<CObj*>	m_listObjMySlaves;		//���� �뿹��
	CObj*		m_pMaster;				//���� ���δ�

	//�� �Ǻ�
	int			m_iTeam;		//�Ʊ� ���� �Ǻ�
	float		m_fRecogDist;	//���� �Ÿ��� ����

	//�ð��� ���� �Ҹ� �� �����ð�
	DWORD		m_dwObjTime[OBJ_TIMEID::END];
	int			m_iObjTimeCount[OBJ_TIMEID::END];

	//�ִϸ��̼�
	FRAME		m_tFrame;

	//ü�� �������� ǥ��
	bool		m_bHideHpBar;

	//Ȱ��ȭ
	bool		m_bActivation;

	//��ũ�� ���� ���� �ƴ��� Ȯ��
	bool		m_bScrollRender;

	//�״� ����
	bool		m_bDeadSound;
	//��ų ����
	float		m_fAngle_Skill;
};


