#pragma once

#include "RotatePos.h"
// 오브젝트 클래스를 위한 그림 그리기 정보 구조체
typedef struct tagInfoDraw
{
	// 좌표. 
	float fx;
	float fy;
	// 크기 
	float fcx;
	float fcy;

	float fSpeed;
	float fAngle;
public:
	tagInfoDraw() :fx(0.f),fy(0.f),fcx(0.f)
		,fcy(0.f), fAngle(0.f), fSpeed(0.f){}

	void Initialize(float _fx, float _fy, float _fcx, float _fcy, float _fSpeed, float _fAngle)
	{
		fx = _fx;
		fy = _fy;
		fcx = _fcx;
		fcy = _fcy;
		fSpeed = _fSpeed;
		fAngle = _fAngle;
	}

public:
	void Set_Angle(float _fx, float _fy)
	{
		fAngle = CRotatePos::GetRadian(POINTFLOAT() = { _fx, _fy }, POINTFLOAT() = { fx, fy }) * 180 / PI;
	}
	float Get_Dist(float _fx, float _fy)
	{
		return sqrtf((fx - _fx)*(fx - _fx) + (fy - _fy)*(fy - _fy));
	}
	void Fn_Move()
	{
		POINTFLOAT ptSpeed = CRotatePos::GetSpeed(fAngle, fSpeed);
		fx += ptSpeed.x;
		fy -= ptSpeed.y;
	}
public:
	POINTFLOAT Get_Speed()
	{
		return CRotatePos::GetSpeed(fAngle, fSpeed);
	}

	RECT Get_Rect()
	{
		return RECT() = { LONG(fx - fcx*0.5), LONG(fy - fcy*0.5), LONG(fx + fcx*0.5), LONG(fy + fcy*0.5) };
	}
	POINT Get_Point()
	{
		return POINT() = { (LONG)fx, (LONG)fy };
	}
	POINTFLOAT Get_PointFloat()
	{
		return POINTFLOAT() = { fx, fy };
	}
}INFO_DRAW;

//애니메이션
typedef struct tagFrame
{
	int		iFrameStart;	// 이미지 시작점
	int		iFrameEnd;		// 이미지 끝점
	int		iFrameScene;	// 이미지 행동
	DWORD	dwFrameSpeed;	// 재생 속도
	DWORD	dwFrameTime;	// 재생 시간
}FRAME;

// 유닛 클래스를 위한 유닛의 이름, 체력, 레벨등의 정보 구조체
typedef struct tagInfoUnit
{
	TCHAR	szName[100];

	int		iAtt;
	int		iMaxHp;
	int		iHp;
	int		iMaxMp;
	int		iMp;
	
	int		iExp;
	int		iMaxExp;
	int		iLevel;

	int		iGold;

	int		iCritical;
public:
	tagInfoUnit(){
		Fn_Initialize();
	}
	tagInfoUnit(const LPCWSTR _pName, int _iAtt = 100, int _iMaxHp = 100, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0) {
		Fn_Initialize();
		Fn_Set_Name(_pName);
		iAtt = _iAtt;
		iMaxHp = _iMaxHp;
		iMaxMp = _iMaxMp;
		iLevel = _iLevel;
		iGold = _iGold;
		Fn_Recovery();
	}
	//szName의 깊은 복사를 하기 위한 대입 연산자 오버로드
	tagInfoUnit& operator=(const tagInfoUnit& rData)
	{
		Fn_Set_Name(rData.szName);
		iAtt = rData.iAtt;
		iMaxHp = rData.iMaxHp;
		iHp = rData.iHp;
		iMaxMp = rData.iMaxMp;
		iMp = rData.iMp;

		iMaxExp = rData.iMaxExp;
		iExp = rData.iExp;
		iLevel = rData.iLevel;

		iGold = rData.iGold;
		iCritical = rData.iCritical;
		return *this;
	}

public:
	void Fn_RecoveryHp()
	{
		iHp = iMaxHp;
	}
	void Fn_RecoveryMp()
	{
		iMp = iMaxMp;
	}
	void Fn_Recovery()
	{
		Fn_RecoveryHp();
		Fn_RecoveryMp();
	}
	void Fn_Set_Name(const LPCWSTR _pName)
	{
		swprintf_s(szName, L"%s", _pName);
	}
	bool Fn_LevelUp()
	{
		if (iExp >= iMaxExp)
		{
			iExp -= iMaxExp;
			return true;
		}
		return false;
	}
	void Fn_Gain(tagInfoUnit& _tUnit)
	{
		iHp += 20;
		iGold += _tUnit.iGold;
		iExp += _tUnit.iMaxExp;
		if (iHp > iMaxHp)
			iHp = iMaxHp;
	}
public:
	void Fn_Initialize()
	{
		ZeroMemory(szName, sizeof(szName));
		iAtt = 0;

		iMaxHp = 0;
		iHp = iMaxHp;
		iMaxMp = 0;
		iMp = iMaxMp;

		iMaxExp = 100;
		iExp = 0;
		iLevel = 0;

		iGold = 10;
		iCritical = 0;	//크리티컬 최대값 1000 이면 무조건 크리
	}
}INFO_UNIT;

// 유닛 클래스를 위한 유닛의 이름, 체력, 레벨등의 정보 구조체
typedef struct tagInfoSkill
{
	TCHAR	szName[100];

	int		iAtt;
	int		iMaxHp;
	int		iHp;
	int		iMaxMp;
	int		iMp;

	int		iExp;
	int		iMaxExp;
	int		iLevel;

	int		iGold;

	int		iCritical;
public:
	tagInfoSkill() {
		Fn_Initialize();
	}
	tagInfoSkill(const LPCWSTR _pName, int _iAtt = 100, int _iMaxHp = 100, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0) {
		Fn_Initialize();
		Fn_Set_Name(_pName);
		iAtt = _iAtt;
		iMaxHp = _iMaxHp;
		iMaxMp = _iMaxMp;
		iLevel = _iLevel;
		iGold = _iGold;
		Fn_Recovery();
	}
	//szName의 깊은 복사를 하기 위한 대입 연산자 오버로드
	tagInfoSkill& operator=(const tagInfoSkill& rData)
	{
		Fn_Set_Name(rData.szName);
		iAtt = rData.iAtt;
		iMaxHp = rData.iMaxHp;
		iHp = rData.iHp;
		iMaxMp = rData.iMaxMp;
		iMp = rData.iMp;

		iMaxExp = rData.iMaxExp;
		iExp = rData.iExp;
		iLevel = rData.iLevel;

		iGold = rData.iGold;

		iCritical = rData.iCritical;
		return *this;
	}

public:
	void Fn_RecoveryHp()
	{
		iHp = iMaxHp;
	}
	void Fn_RecoveryMp()
	{
		iMp = iMaxMp;
	}
	void Fn_Recovery()
	{
		Fn_RecoveryHp();
		Fn_RecoveryMp();
	}
	void Fn_Set_Name(const LPCWSTR _pName)
	{
		swprintf_s(szName, L"%s", _pName);
	}
	bool Fn_LevelUp()
	{
		if (iExp >= iMaxExp)
		{
			iExp -= iMaxExp;
			return true;
		}
		return false;
	}

public:
	void Fn_Initialize()
	{
		ZeroMemory(szName, sizeof(szName));
		iAtt = 0;

		iMaxHp = 0;
		iHp = iMaxHp;
		iMaxMp = 0;
		iMp = iMaxMp;

		iMaxExp = 0;
		iExp = 0;
		iLevel = 0;

		iGold = 0;

		iCritical = 0;
	}
}INFO_SKILL;


typedef struct tagPos
{
	int x;
	int y;
	tagPos(int _x = 0, int _y = 0) :x(_x), y(_y) {}

	tagPos(INFO_DRAW pt)
	{
		x = (int)pt.fx;
		y = (int)pt.fy;
	}

	POINT Get_DrawPoint() {
		return POINT() = { LONG(x*SIZEX + SIZEX*0.5), LONG(y*SIZEY + SIZEY*0.5) };
	}
	POINTFLOAT Get_DrawPointFloat() {
		return POINTFLOAT() = { float(x*SIZEX + SIZEX*0.5), float(y*SIZEY + SIZEY*0.5) };
	}

	tagPos& operator += (const tagPos& _tPos)
	{
		this->x += _tPos.x;
		this->y += _tPos.y;
		return *this;
	}
	tagPos& operator -= (const tagPos& _tPos)
	{
		this->x -= _tPos.x;
		this->y -= _tPos.y;
		return *this;
	}
	tagPos operator + (const tagPos& _tPos) const
	{
		tagPos tPos = *this;
		tPos.x += _tPos.x;
		tPos.y += _tPos.y;
		return tPos;
	}
	tagPos operator - (const tagPos& _tPos) const
	{
		tagPos tPos = *this;
		tPos.x -= _tPos.x;
		tPos.y -= _tPos.y;
		return tPos;
	}
	bool operator ==(const tagPos& _tPos) const
	{
		return ((this->x == _tPos.x) && (this->y == _tPos.y));
	}
	bool operator !=(const tagPos& _tPos) const
	{
		return ((this->x != _tPos.x) && (this->y == _tPos.y));
	}
}POS;