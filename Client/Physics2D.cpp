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
		//����üũ �� ��ġ ��ȯ ���� rGround
		int iSize = rGround.size();
		for (int i = 0; i < iSize - 1; ++i)
		{
			POINT pt1 = rGround[i];
			POINT pt2 = rGround[i + 1];
			POINT ptTemp = {};
			// �÷��̾��� ��ǥ�� ���� ���̿� ���� ��� üũ ����
			// ������ ������ ��쵵 �����Ƿ� �ݴ� ���⵵ üũ
			if ((pt1.x <= tInfoObj.fx && pt2.x >= tInfoObj.fx) ||
				(pt1.x >= tInfoObj.fx && pt2.x <= tInfoObj.fx))
			{
				if (pt1.x > pt2.x)
				{
					ptTemp = pt1;
					pt1 = pt2;
					pt2 = ptTemp;
				}
				//���� ���ϱ�
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
		//����üũ �� ��ġ ��ȯ ���� ��

		//���� ���� ����
		// ������ �Ÿ� = ��*�ð� + �߷�* �ð�*�ð� *0.5
		// �� = �߷�*�ð�
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
