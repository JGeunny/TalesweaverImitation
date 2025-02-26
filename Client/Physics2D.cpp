#include "stdafx.h"
#include "Physics2D.h"
#include "Obj.h"

CPhysics2D::CPhysics2D()
{
}

CPhysics2D::~CPhysics2D()
{
}

void CPhysics2D::GravityObj(list<CObj*>& rSrc, vector<POINT>& rGround)
{
	/*INFO tInfoObj = {};
	POINTFLOAT ptForce = {};

	for (auto& pSource : rSrc)
	{
		tInfoObj = pSource->Get_Info();
		ptForce = *pSource->Get_Force();
		bool bDoJump = pSource->Get_DoJump();
		float fGroundY = 0;
		//지면체크 후 위치 반환 구간 rGround
		int iSize = rGround.size();
		for (int i = 0; i < iSize - 1; ++i)
		{
			POINT pt1 = rGround[i];
			POINT pt2 = rGround[i + 1];
			POINT ptTemp = {};
			// 플레이어의 좌표가 직선 사이에 있을 경우 체크 시작
			// 뒤집힌 직선일 경우도 있으므로 반대 방향도 체크
			if ((pt1.x <= tInfoObj.fx && pt2.x >= tInfoObj.fx) ||
				(pt1.x >= tInfoObj.fx && pt2.x <= tInfoObj.fx))
			{
				if (pt1.x > pt2.x)
				{
					ptTemp = pt1;
					pt1 = pt2;
					pt2 = ptTemp;
				}
				//기울기 구하기
				if (0 == (pt2.y - pt1.y))
				{
					fGroundY = pt1.y;
				}
				else
				{
					float fSlope = ((float)pt2.y - pt1.y) / (pt2.x - pt1.x);
					fGroundY = (tInfoObj.fx - pt1.x) * fSlope + pt1.y;
				}
				break;
			}
		}
		//지면체크 후 위치 반환 구간 끝

		//자유 낙하 공식
		// 떨어진 거리 = 힘*시간 + 중력* 시간*시간 *0.5
		// 힘 = 중력*시간
		if (tInfoObj.fy < fGroundY || ptForce.y > 0)
		{
			bDoJump = false;
			ptForce.y -= GRAVITY*REAL_TIME;
		}
		else
		{
			tInfoObj.fy = fGroundY;
			bDoJump = true;
			ptForce.y = 0;
		}
		pSource->Set_DoJump(bDoJump);
		pSource->Set_Force(ptForce);
		pSource->Set_Pos(tInfoObj.fx, tInfoObj.fy - ptForce.y);
	}*/
}
