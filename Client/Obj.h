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

	//목표 타게팅
	void Set_Target(CObj* _pTarget);
	CObj* Get_Target(){ return m_pTarget; }
	void Clear_Target();

	//주인 설정
	void Set_Master(CObj* _pMaster);
	CObj* Get_Master() { return m_pMaster; }
	void Clear_Master();

	//애니 메이션
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

	//활성화
	bool& Alter_Activation() { return m_bActivation;}

public:
	//스킬 각도
	float& Alter_Angle_Skill() {return m_fAngle_Skill;}
protected:
	bool		m_bIsInit;
	INFO_DRAW	m_tDraw;
	bool		m_bObjState[OBJ_STATEID::END];
	RECT		m_tRect;

	//목표 타게팅
	list<CObj*>	m_listObjTargetedAtMe;	//나를 타겟팅한 놈들
	CObj*		m_pTarget;				//내가 타겟팅한 놈

	//주인 설정
	list<CObj*>	m_listObjMySlaves;		//나의 노예들
	CObj*		m_pMaster;				//나의 주인님

	//적 판별
	int			m_iTeam;		//아군 적군 판별
	float		m_fRecogDist;	//인지 거리를 설정

	//시간에 따른 소멸 및 유지시간
	DWORD		m_dwObjTime[OBJ_TIMEID::END];
	int			m_iObjTimeCount[OBJ_TIMEID::END];

	//애니메이션
	FRAME		m_tFrame;

	//체력 게이지바 표시
	bool		m_bHideHpBar;

	//활성화
	bool		m_bActivation;

	//스크롤 랜더 인지 아닌지 확인
	bool		m_bScrollRender;

	//죽는 사운드
	bool		m_bDeadSound;
	//스킬 각도
	float		m_fAngle_Skill;
};


