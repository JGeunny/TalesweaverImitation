#pragma once
#ifndef __ABSTRACTFACTORY
#define __ABSTRACTFACTORY

#include "Obj.h"
#include "Scene.h"
#include "Skill.h"
#include "Unit.h"
#include "Bullet.h"
#include "RotatePos.h"
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create(int _iTeam)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Team(_iTeam);
		return pObj;
	}
	static CObj* Create(int _iTeam, float x, float y)
	{
		CObj* pObj = Create(_iTeam);
		pObj->Set_Pos(x, y);
		return pObj;
	}
	static CObj* Create(int _iTeam, float x, float y, float angle)
	{
		CObj* pObj = Create(_iTeam, x, y);
		pObj->Set_Angle(angle);
		return pObj;
	}

	static CObj* Create_Unit(int _iTeam, float x, float y, float angle
		, const LPCWSTR _pName, int _iAtt = 80, int _iMaxHp = 600, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0)

	{
		CObj* pObj = Create(_iTeam, x, y, angle);
		//tagInfoUnit(const LPCWSTR _pName, int _iMaxHp = 100, int _iMaxMp = 0, int _iLevel = 1, int _iGold = 0)
		INFO_UNIT tUnitInfo(_pName, _iAtt, _iMaxHp, _iMaxMp, _iLevel, _iGold);
		static_cast<CUnit*>(pObj)->Alter_UnitInfo() = tUnitInfo;
		return pObj;
	}

	static CObj* Create_Unit_Slave(CObj* _pOwner, float x, float y, float angle
		, const LPCWSTR _pName, int _iAtt = 80, int _iMaxHp = 600, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0)

	{
		CObj* pObj = Create(_pOwner->Get_Team(), x, y, angle);
		pObj->Set_Master(_pOwner);
		//tagInfoUnit(const LPCWSTR _pName, int _iMaxHp = 100, int _iMaxMp = 0, int _iLevel = 1, int _iGold = 0)
		INFO_UNIT tUnitInfo(_pName, _iAtt, _iMaxHp, _iMaxMp, _iLevel, _iGold);
		static_cast<CUnit*>(pObj)->Alter_UnitInfo() = tUnitInfo;
		return pObj;
	}

	static CObj* Create_Skill(CObj* _pOwner, float dist
		, const LPCWSTR _pName = L"@", int _iAtt = 1, int _iMaxHp = 100, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0)
	{
		INFO_DRAW tOwner = _pOwner->Get_Info();
		CObj* pObj = Create(_pOwner->Get_Team(), tOwner.fx, tOwner.fy, tOwner.fAngle);
		POINTFLOAT ptWH = CRotatePos::GetSpeed(tOwner.fAngle, dist);
		tOwner.fx += ptWH.x;
		tOwner.fy -= ptWH.y;
		pObj->Set_Pos(tOwner.fx, tOwner.fy);
		pObj->Set_Master(_pOwner);
		INFO_SKILL tSkillInfo(_pName, _iAtt, _iMaxHp, _iMaxMp, _iLevel, _iGold);
		if (dynamic_cast<CUnit*>(_pOwner))
		{
			tSkillInfo.iCritical += static_cast<CUnit*>(_pOwner)->Get_Unit().iCritical;
		}
		if (dynamic_cast<CSkill*>(_pOwner))
		{
			tSkillInfo.iCritical += static_cast<CSkill*>(_pOwner)->Alter_SkillInfo().iCritical;
		}
		static_cast<CSkill*>(pObj)->Alter_SkillInfo() = tSkillInfo;
		return pObj;
	}

	static CScene* Create_Scene()
	{
		CScene* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
};
#endif // __ABSCRACTFACTORY