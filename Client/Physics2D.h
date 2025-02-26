#pragma once
class CObj;
class CPhysics2D
{
public:
	CPhysics2D();
	~CPhysics2D();

public:
	static void GravityObj(list<CObj*>& rSrc, vector<POINT>& rGround);
};
