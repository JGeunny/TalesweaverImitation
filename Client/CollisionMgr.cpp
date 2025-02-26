#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Scene.h"
#include "Astar.h"
#include "Unit.h"
#include "Player.h"
#include "Tile.h"
#include "Mouse.h"
#include "AbstractFactory.h"
#include "BeAttacked.h"
#include "CriticalAttacked.h"
#include "ObjMgr.h"
#include "AircraftCarrier.h"
#include "Turret.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionMouseOnUnit(list<CObj*>& rUnit, CObj* rMouse)
{
	RECT rc = {};
	static_cast<CMouse*>(rMouse)->Set_Attack(false);
	for (auto& pUnit : rUnit)
	{
		if (pUnit->Get_Dead()) continue;
		if (pUnit->Get_Team() != TEAM_1)
		{
			if (IntersectRect(&rc, rMouse->Get_Rect(), pUnit->Get_Rect()))
			{
				static_cast<CMouse*>(rMouse)->Set_Attack(true);
				break;
			}
		}
	}
}

void CCollisionMgr::CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	RECT rc = {};
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
			{
				pDest->Set_Dead(true);
				pSource->Set_Dead(true);
			}
		}
	}
}

void CCollisionMgr::CollisionRectEx(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		if (dynamic_cast<CTurret*>(pDest)) continue;
		if (pDest->Get_Dead()) continue;
		for (auto& pSource : rSrc)
		{
			//if (dynamic_cast<CPlayer*>(pSource)) continue;
			if (dynamic_cast<CTurret*>(pSource)) continue;
			if (pDest == pSource) continue;
			if (pSource->Get_Dead()) continue;
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				float x = pSource->Get_Info().fx;
				float y = pSource->Get_Info().fy;

				if (fMoveX > fMoveY)
				{
					if (y < pDest->Get_Info().fy)
						fMoveY *= -1.f;

					pSource->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pDest->Get_Info().fx)
						fMoveX *= -1.f;

					pSource->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}
}

void CCollisionMgr::CollisionRectMapEx(vector<CObj*>& rTile, list<CObj*>& rUnit)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rTile)
	{
		if (pDest->Get_Dead()) continue;
		if (lstrcmp(static_cast<CTile*>(pDest)->Get_FrameKey(), L"Tile_1"))
			continue;
		for (auto& pSource : rUnit)
		{
			if (pSource->Get_Dead()) continue;
			if (pDest == pSource) continue;
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				float x = pSource->Get_Info().fx;
				float y = pSource->Get_Info().fy;

				if (fMoveX > fMoveY)
				{
					if (y < pDest->Get_Info().fy)
						fMoveY *= -1.f;

					pSource->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pDest->Get_Info().fx)
						fMoveX *= -1.f;

					pSource->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckSphere(pDest, pSource))
			{
				pDest->Set_Dead(true);
				pSource->Set_Dead(true);
			}
		}
	}
}

void CCollisionMgr::Follow_Enemy(list<CObj*>& rUnit)
{
	CObj*		pTarget = nullptr;
	float		fShortest = 9999;
	float		fDist = 0;
	INFO_DRAW	tDrawMe = {};
	INFO_DRAW	tDrawEnemy = {};

	for (auto& pMe : rUnit)
	{
		fShortest = 9999;
		fDist = 0;
		if (pMe->Get_Dead()) continue;
		if (dynamic_cast<CPlayer*>(pMe)) continue;
		/*if (dynamic_cast<CPlayer*>(pMe))// continue;//플레이어 일경우  같은 편이 있으면 따라옴
		{
			tDrawMe = pMe->Get_Info();
			for (auto& pEnemy : rUnit)
			{
				if (dynamic_cast<CTurret*>(pEnemy)) continue;
				if (pEnemy->Get_Dead()) continue;
				if (pMe == pEnemy) continue;
				if (pMe->Get_Team() == pEnemy->Get_Team())
				{
					tDrawEnemy = pEnemy->Get_Info();
					fDist = tDrawEnemy.Get_Dist(tDrawMe.fx, tDrawMe.fy);
					if (pMe->Get_RecogDist() >= fDist)
					{
						if (fShortest > fDist)
						{
							pTarget = pEnemy;
							fShortest = fDist;
						}
					}
				}
			}
			if (pTarget)
			{
				static_cast<CUnit*>(pTarget)->
					Alter_UnitState(UNIT_STATEID::FOLLOW) = true;
				pTarget->Set_Master(pMe);
			}
		}
		else
		{*/

			if (nullptr == pMe->Get_Target())	// 타겟이 없을 경우 찾기
			{
				tDrawMe = pMe->Get_Info();
				for (auto& pEnemy : rUnit)
				{
					if (static_cast<CUnit*>(pEnemy)->Alter_UnitState(UNIT_STATEID::DEAD)) continue;
					if (dynamic_cast<CTurret*>(pEnemy)) continue;
					if (pEnemy->Get_Dead()) continue;
					if (pMe == pEnemy) continue;
					if (pMe->Get_Team() == pEnemy->Get_Team()) continue;
					tDrawEnemy = pEnemy->Get_Info();
					fDist = tDrawEnemy.Get_Dist(tDrawMe.fx, tDrawMe.fy);
					if (pMe->Get_RecogDist() >= fDist)
					{
						if (fShortest > fDist)
						{
							pTarget = pEnemy;
							fShortest = fDist;
						}
					}
				}
				if (pTarget)
				{
					static_cast<CUnit*>(pMe)->
						Alter_UnitState(UNIT_STATEID::FOLLOW) = true;
					pMe->Set_Target(pTarget);
				}
			}
		//}
	}
}

void CCollisionMgr::Follow_Building_Enemy(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	CObj*		pTarget = nullptr;
	float		fShortest = 9999;
	float		fDist = 0;
	INFO_DRAW	tDrawMe = {};
	INFO_DRAW	tDrawEnemy = {};

	for (auto& pBuilding : rDst)
	{
		fShortest = 9999;
		fDist = 0;
		if (pBuilding->Get_Dead()) continue;
		if (nullptr == pBuilding->Get_Target())	// 타겟이 없을 경우 찾기
		{
			tDrawMe = pBuilding->Get_Info();
			for (auto& pEnemy : rSrc)
			{
				if (dynamic_cast<CTurret*>(pEnemy)) continue;
				if (pEnemy->Get_Dead()) continue;
				if (pBuilding->Get_Team() == pEnemy->Get_Team()) continue;
				tDrawEnemy = pEnemy->Get_Info();
				fDist = tDrawEnemy.Get_Dist(tDrawMe.fx, tDrawMe.fy);
				if (pBuilding->Get_RecogDist() >= fDist)
				{
					if (fShortest > fDist)
					{
						pTarget = pEnemy;
						fShortest = fDist;
					}
				}
			}
			if (pTarget)
			{
				static_cast<CUnit*>(pBuilding)->
					Alter_UnitState(UNIT_STATEID::FOLLOW) = true;
				pBuilding->Set_Target(pTarget);
			}
		}
		//}
	}
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	float fRadiusSum = (pDst->Get_Info().fcx * 0.5f) + (pSrc->Get_Info().fcx * 0.5f);
	float x = pDst->Get_Info().fx - pSrc->Get_Info().fx;
	float y = pDst->Get_Info().fy - pSrc->Get_Info().fy;

	float fDist = sqrtf(x * x + y * y);

	return fRadiusSum > fDist;
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadiusSumX = (pDst->Get_Info().fcx*0.5f) + (pSrc->Get_Info().fcx*0.5f);
	float fRadiusSumY = (pDst->Get_Info().fcy*0.5f) + (pSrc->Get_Info().fcy*0.5f);

	float fDistX = fabs(pDst->Get_Info().fx - pSrc->Get_Info().fx);
	float fDistY = fabs(pDst->Get_Info().fy - pSrc->Get_Info().fy);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	return false;
}

void CCollisionMgr::CollisionRectWallAndAttack(list<CObj*>& rWall, list<CObj*>& rSkill_Crash)
{
	RECT rc = {};
	for (auto& pWall : rWall)
	{
		for (auto& pSkill_Crash : rSkill_Crash)
		{
			if (IntersectRect(&rc, pWall->Get_Rect(), pSkill_Crash->Get_Rect()))
			{
				static_cast<CSkill*>(pSkill_Crash)->Alter_SkillState(SKILL_STATEID::BOUNCE) = true;
			}
		}
	}
}
void CCollisionMgr::CollisionRectAttack(list<CObj*>& rEnmey, list<CObj*>& rSkill_Crash)
{
	RECT rc = {};
	for (auto& pEnmey : rEnmey)
	{
		if (static_cast<CUnit*>(pEnmey)->Alter_UnitState(UNIT_STATEID::DEAD)) continue;
		if (pEnmey->Alter_ObjState(OBJ_STATEID::OVERPOWER)) continue;
		if (pEnmey->Get_Dead()) continue;
		for (auto& pSkill_Crash : rSkill_Crash)
		{
			if (pSkill_Crash->Get_Dead()) continue;
			if (pEnmey->Get_Team() == pSkill_Crash->Get_Team()) continue;
			if (IntersectRect(&rc, pEnmey->Get_Rect(), pSkill_Crash->Get_Rect()))
			{
				if (static_cast<CSkill*>(pSkill_Crash)->IsHit_Unit(pEnmey))
				{
					INFO_UNIT& tUnit = static_cast<CUnit*>(pEnmey)->Alter_UnitInfo();
					INFO_SKILL& tSkill = static_cast<CSkill*>(pSkill_Crash)->Alter_SkillInfo();

					//공격 임펙트
					int iSkillAtt = tSkill.iAtt;
					CObj* pBeAttacked = nullptr;

					int iCritical = (tSkill.iCritical > 1000) ? 1000: tSkill.iCritical;
					iCritical = (tSkill.iCritical < 1) ? 1 : tSkill.iCritical;
					
					INFO_DRAW tDrawPos;
					if (dynamic_cast<CAircraftCarrier*>(pEnmey))
					{
						tDrawPos = pSkill_Crash->Get_Info();
						tDrawPos.fy -= 100;
					}
					else
					{
						tDrawPos = pEnmey->Get_Info();
					}
					if (rand() % int(1000 / iCritical) == 0) //크리티컬 공격
					{
						iSkillAtt *= 6;
						pBeAttacked = CAbstractFactory<CCriticalAttacked>::Create(TEAM_MOUSE, tDrawPos.fx, tDrawPos.fy);
					}
					else
						pBeAttacked = CAbstractFactory<CBeAttacked>::Create(TEAM_MOUSE, tDrawPos.fx, tDrawPos.fy);

					static_cast<CBeAttacked*>(pBeAttacked)->Alter_Attack() = iSkillAtt;
					CObjMgr::Get_Instance()->Get_List()[OBJID::EFFECT].emplace_back(pBeAttacked);

					tUnit.iHp -= iSkillAtt;					
					--tSkill.iHp;

					if (tUnit.iHp <= 0)
					{
						//적을 잡음
						pEnmey->Set_Dead(true);
						//최고 위의 주인은 유닛이므로 유닛에게 보상을 줌
						CObj* pMaster = pSkill_Crash->Get_Master();
						while (nullptr != pMaster)
						{
							if (dynamic_cast<CUnit*>(pMaster))
							{
								static_cast<CUnit*>(pMaster)->Alter_UnitInfo().Fn_Gain(tUnit); //적 처치시 경험치와 골드를 얻음
								break;
							}
							else
								pMaster = pMaster->Get_Master();
						}
					}
					if (tSkill.iHp <= 0)
						pSkill_Crash->Set_Dead(true);
				}
			}
		}
	}
}
