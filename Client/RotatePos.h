#ifndef __ROTATEPOS_H__
#define __ROTATEPOS_H__
#pragma once

#define ROUND_N				3
//#define PI				3.1415926536f

class CRotatePos
{
public:
	CRotatePos();
	~CRotatePos();

	void Set_StdPos(float _fx, float _fy);
	void Set_StdPos(POINTFLOAT& _ptStdPos);

	void Render(HDC& _hDC, int _opt = 0);

	const list<POINTFLOAT>&		Line(float _fAngle, POINTFLOAT& _ptDstPos, POINTFLOAT& _ptSrcPos, int _opt = 0);
	const list<POINTFLOAT>&		Rect(float _fAngle, RECT& _rtRect, int _opt = 0);
	const list<POINTFLOAT>&		ListPos(float _fAngle, list<POINTFLOAT> _ListPos, int _opt = 0);
	const list<POINTFLOAT>&		GetListPos() const {return m_ListPos;}
	const list<POINTFLOAT*>&	GetListFront() const { return m_ListFront; }

	void Clear();

	//라디안 방식
	static POINTFLOAT		GetPointR(float _fRadian, POINTFLOAT & _ptDstPos, POINTFLOAT & _ptSrcPos);
	static float			GetRadian(POINTFLOAT& _ptDstPos, POINTFLOAT& _ptSrcPos);
	static POINTFLOAT		GetSpeed(float _fAngle, float _fSpeed);
	static POINTFLOAT		GetSpeedR(float _fRadian, float _fSpeed);
public:
	static float			Roundf_N(float x, int digit);
private:
	POINTFLOAT				m_ptStdPos;
	list<POINTFLOAT>		m_ListPos;
	list<POINTFLOAT*>		m_ListFront;
};

#endif