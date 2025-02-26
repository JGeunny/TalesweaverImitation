#pragma once
class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static void CollisionMouseOnUnit(list<CObj*>& rUnit, CObj * rMouse);

public:
	static void CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionRectEx(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionRectMapEx(vector<CObj*>& rTile, list<CObj*>& rUnit);
	static void CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc);

	static void Follow_Enemy(list<CObj*>& rSrc);
	static void Follow_Building_Enemy(list<CObj*>& rDst, list<CObj*>& rSrc);

public:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
	static void CollisionRectWallAndAttack(list<CObj*>& rWall, list<CObj*>& rSkill_Crash);
	static void CollisionRectAttack(list<CObj*>& rEnmey, list<CObj*>& rSkill_Crash);
	//	static bool CheckWall(CObj * pObjWall, CObj * pObjPlayer);
};
