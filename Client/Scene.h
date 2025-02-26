#pragma once

#include "FieldMap.h"
#include "ObjMgr.h"

class CAstar;
class CScene 
{
public:
	CScene();
	virtual ~CScene();

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
	CAstar* Get_Astar() { return m_pAstar; }

	void Set_Speed(float _fSpeed) { m_tDraw.fSpeed = _fSpeed; }
	const float& Get_Speed() const { return m_tDraw.fSpeed; }

	void Set_LiveTime(int _iLiveTime) { m_iLiveTime = _iLiveTime; }
	const int& Get_LiveTime() const { return m_iLiveTime; }

	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	const CObj* Get_Target() const { return m_pTarget; }

	void Set_Team(int _iTeam) { m_iTeam = _iTeam; }
	const int& Get_Team() const { return m_iTeam; }

	void Set_Angle(float _fAngle) { m_tDraw.fAngle = _fAngle; }
	const float& Get_Angle() const { return m_tDraw.fAngle; }

	void Set_Pos(float x, float y) {
		m_tDraw.fx = x; m_tDraw.fy = y;
	}

	void Set_Dead(bool _bDead) { m_bObjState[OBJ_STATEID::DEAD] = _bDead; }
	const bool& Get_Dead() const { return m_bObjState[OBJ_STATEID::DEAD]; }

	void Set_Info(INFO_DRAW _tDraw) { m_tDraw = _tDraw; }
	const INFO_DRAW& Get_Info(void)const { return m_tDraw; }

	RECT* Get_Rect() { return &m_tDraw.Get_Rect(); }

protected:
	CFieldMap*	m_pFieldMap;
	bool		m_bIsInit;
	INFO_DRAW	m_tDraw;
	bool		m_bObjState[OBJ_STATEID::END];

	//타게팅
	CObj*		m_pTarget;
	INFO_DRAW	m_tDraw_Target;
	//적 판별
	int			m_iTeam;		//아군 적군 판별
	float		m_fRecogDist;	//인지 거리를 설정
								//시간에 따른 소멸 및 유지시간
	DWORD		m_dwOldTime;
	int			m_iLiveTime;

	CAstar*		m_pAstar;
	list<POS*>	m_ListFindPath;
};

