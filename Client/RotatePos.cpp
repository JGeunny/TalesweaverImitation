#include "stdafx.h"
#include "RotatePos.h"

CRotatePos::CRotatePos()
{
}

CRotatePos::~CRotatePos()
{
	Clear();
}

void CRotatePos::Set_StdPos(float _fx, float _fy)
{
	Set_StdPos(POINTFLOAT() = { _fx, _fy });
}

void CRotatePos::Set_StdPos(POINTFLOAT & _ptStdPos)
{
	m_ptStdPos = _ptStdPos;
}

void CRotatePos::Render(HDC & _hDC, int _opt)
{
	bool bCheckFront;
	for (auto& ptPos : m_ListPos)
	{
		bCheckFront = false;
		for (auto& pPosFront : m_ListFront)
		{
			if (pPosFront == &ptPos)
			{
				bCheckFront = true;
				break;
			}
		}
		if (bCheckFront)
			MoveToEx(_hDC, (LONG)ptPos.x, (LONG)ptPos.y, nullptr);
		else
			LineTo(_hDC, (LONG)ptPos.x, (LONG)ptPos.y);
	}
}

const list<POINTFLOAT>& CRotatePos::Line(float _fAngle, POINTFLOAT & _ptDstPos, POINTFLOAT & _ptSrcPos, int _opt)
{
	float fRadian = _fAngle / 180 * PI;
	float fRadian_Std = fRadian + GetRadian(_ptSrcPos, m_ptStdPos);
	POINTFLOAT ptDstPos_Std = GetPointR(fRadian_Std, _ptSrcPos, m_ptStdPos);

	float fRadian_Dst = fRadian + GetRadian(_ptDstPos, _ptSrcPos);
	POINTFLOAT ptDstPos = GetPointR(fRadian_Dst, _ptDstPos, _ptSrcPos);
	if (0 == _opt)
	{
		m_ListPos.emplace_back(ptDstPos_Std);
		m_ListFront.emplace_back(&m_ListPos.back());
	}
	POINTFLOAT ptDistPos = { ptDstPos_Std.x- _ptSrcPos.x, ptDstPos_Std.y- _ptSrcPos.y };
	ptDstPos = { ptDstPos.x + ptDistPos.x, ptDstPos.y + ptDistPos.y };
	m_ListPos.emplace_back(ptDstPos);

	return m_ListPos;
}

const list<POINTFLOAT>& CRotatePos::Rect(float _fAngle, RECT & _rtRect, int _opt)
{
	POINTFLOAT ptPos1 = { (float)_rtRect.left, (float)_rtRect.top };
	POINTFLOAT ptPos2 = { (float)_rtRect.right, (float)_rtRect.top };
	POINTFLOAT ptPos3 = { (float)_rtRect.left, (float)_rtRect.bottom };
	POINTFLOAT ptPos4 = { (float)_rtRect.right, (float)_rtRect.bottom };
	Line(_fAngle, ptPos2, ptPos1, 0);
	Line(_fAngle, ptPos4, ptPos2, 1);
	Line(_fAngle, ptPos3, ptPos4, 1);
	Line(_fAngle, ptPos1, ptPos3, 1);

	return m_ListPos;
}

const list<POINTFLOAT>& CRotatePos::ListPos(float _fAngle, list<POINTFLOAT> _ListPos, int _opt)
{
	POINTFLOAT ptPrePos;
	int	iFrontOpt = 0;
	for (auto& ptThisPos : _ListPos)
	{
		if (&ptThisPos == &_ListPos.front())
			ptPrePos = ptThisPos;
		else
		{
			Line(_fAngle, ptThisPos, ptPrePos, iFrontOpt);
			iFrontOpt = 1;
			ptPrePos = ptThisPos;
		}
	}
	_ListPos.clear();

	return m_ListPos;
}

void CRotatePos::Clear()
{
	m_ListPos.clear();
	m_ListFront.clear();
}

POINTFLOAT CRotatePos::GetPointR(float _fRadian, POINTFLOAT & _ptDstPos, POINTFLOAT & _ptSrcPos)
{
	if (_fRadian == 0)
		return _ptDstPos;
	POINTFLOAT ptWH = { _ptDstPos.x - _ptSrcPos.x , _ptDstPos.y - _ptSrcPos.y };
	float fDist = sqrtf(ptWH.x*ptWH.x + ptWH.y*ptWH.y);

	ptWH.x = Roundf_N(_ptSrcPos.x + cosf(_fRadian) * fDist, ROUND_N);
	ptWH.y = Roundf_N(_ptSrcPos.y - sinf(_fRadian) * fDist, ROUND_N);
	
	return ptWH;

}

float CRotatePos::GetRadian(POINTFLOAT & _ptDstPos, POINTFLOAT & _ptSrcPos)
{
	POINTFLOAT ptWH = { _ptDstPos.x - _ptSrcPos.x , _ptDstPos.y - _ptSrcPos.y };
	float fDist = sqrtf(ptWH.x*ptWH.x + ptWH.y*ptWH.y);
	float fRadian = 0;
	if (fDist != 0)
		fRadian = Roundf_N(acosf(ptWH.x / fDist), 3 + ROUND_N);
	if (ptWH.y > 0)
		fRadian = 2* PI - fRadian;
	return fRadian;
}

POINTFLOAT CRotatePos::GetSpeed(float _fAngle, float _fSpeed)
{
	float fRadian = _fAngle / 180 * PI;
	POINTFLOAT ptWH = {};
	ptWH.x = Roundf_N(cosf(fRadian) * _fSpeed, ROUND_N);
	ptWH.y = Roundf_N(sinf(fRadian) * _fSpeed, ROUND_N);

	return ptWH;
}

POINTFLOAT CRotatePos::GetSpeedR(float _fRadian, float _fSpeed)
{
	POINTFLOAT ptWH = {};
	ptWH.x = Roundf_N(cosf(_fRadian) * _fSpeed, ROUND_N);
	ptWH.y = Roundf_N(sinf(_fRadian) * _fSpeed, ROUND_N);

	return ptWH;
}

float CRotatePos::Roundf_N(float x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}
