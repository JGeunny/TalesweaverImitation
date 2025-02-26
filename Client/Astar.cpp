#include "stdafx.h"
#include "Astar.h"
#include "FieldMap.h"

CAstar::tagNode::tagNode(POS _StartPoint, tagNode * _pParent, POS _EndPoint)
	:point(_StartPoint), pParent(_pParent), end(_EndPoint), F(0), G(0), H(0)
{
	int x = 0, y = 0;	// ��� ��ǥ ��(�θ� ��ǥ-�ڽ� ��ǥ)
	if (nullptr == pParent)	// �θ� ���� ���
		G = 0;
	else
	{
		x = point.x - pParent->point.x;
		y = point.y - pParent->point.y;
		if (0 == x || 0 == y)	// ������ ���
			G = pParent->G + 10;
		else if (0 != x && 0 != y)	// �밢 ���� ���
			G = pParent->G + 14;
		else // ����(�θ�� ��ǥ�� ���� ���)(0 == x && 0 == y)
		{
			F = -100000;  H = -100000; G = -100000;
		}
	}

	H = (abs(end.x - point.x) + abs(end.y - point.y)) * 10;
	F = G + 10;
}

void CAstar::SetPoint(INFO_DRAW _tStartPoint, INFO_DRAW _tEndPoint)
{
	tStartPoint = POS((int)_tStartPoint.fx / SIZEX, (int)_tStartPoint.fy / SIZEY);
	tEndPoint = POS((int)_tEndPoint.fx / SIZEX, (int)_tEndPoint.fy / SIZEY);
}

void CAstar::SetPoint(POS _tStartPoint, POS _tEndPoint)
{
	tStartPoint = _tStartPoint;
	tEndPoint = _tEndPoint;
}

list<POS> CAstar::FindPath()
{
	return FindPath(m_pField, tStartPoint, tEndPoint);
}

list<POS> CAstar::FindPath(CFieldMap * _pField, POS _tStartPoint, POS _tEndPoint)
{
	list<NODE*> OpenNode;
	list<NODE*> CloseNode;
	NODE* pSelectNode;
	list<POS> path;
	POS tTempPoint;

	list<NODE*>::iterator iter;

	if(IsWall(_tEndPoint)) return path;

	

	int iSmallest_F = 0;

	OpenNode.push_back(new NODE(_tStartPoint, NULL, _tEndPoint));

	while ((OpenNode.end() != OpenNode.begin())
		&& (OpenNode.end() == FindNodeByPoint(OpenNode, _tEndPoint)))
	{
		iter = NextNode(OpenNode);
		pSelectNode = *iter;

		ExploreNode(_pField, pSelectNode, OpenNode, CloseNode, _tEndPoint);

		CloseNode.push_back(pSelectNode);
		OpenNode.erase(iter);
	}

	if ((OpenNode.end() != OpenNode.begin())) // ���� ã�� ���
	{
		iter = FindNodeByPoint(OpenNode, _tEndPoint); // �������� ��带 ã�Ƽ� iter�� ����
		for (pSelectNode = *iter; pSelectNode->pParent != NULL; pSelectNode = pSelectNode->pParent)  // �θ� NULL�� ������ path�� ��� ����
			path.push_back(POS(pSelectNode->point));
		path.push_back(POS(pSelectNode->point)); // �θ� NULL�� ����� path���� ����(��� ����)
		path.reverse(); // �������������� �������� �Է������Ƿ� �ٽ� �������� ������ ��������� ù ��°�� �ǵ��� ��.

		for (iter = OpenNode.begin(); iter != OpenNode.end(); ++iter)// ���� ã�� ��� �����Ҵ� ����
			delete *iter; // ���� ��� �����Ҵ� ����

		for (iter = CloseNode.begin(); iter != CloseNode.end(); ++iter)
			delete *iter; // ���� ��� �����Ҵ� ����

		return path; // ���� ã�� ��� ����
	}

	// ���� ã�� ���� ��� �����Ҵ� ����
	for (iter = CloseNode.begin(); iter != CloseNode.end(); iter++)
		delete *iter; // ���� ��� �����Ҵ� ����
	return path; // ���� ã�� ���� ��� ����
}

/*void CAstar::Render()
{
	list<POS*> path = FindPath();
	for (list<POS*>::iterator iter = path.begin(); iter != path.end(); ++iter)
		m_pField->map(*(*iter)) = 9;
	m_pField->Render();
}*/

bool CAstar::IsWall(POS _tPoint)
{
	return IsWall(m_pField, _tPoint);
}

bool CAstar::IsWall(CFieldMap * _pField, POS _tPoint)
{
	return (0 != _pField->map(_tPoint.x, _tPoint.y));
}

void CAstar::ExploreNode(CFieldMap * _pField, NODE * _pSelectNode, list<NODE*>& _OpenNode, list<NODE*>& _CloseNode, POS _tEndPoint)
{
	list<NODE*>::iterator iter;
	POS tPoint;
	int iDistance = 0;
	bool bCreateNode = false;

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			tPoint = _pSelectNode->point + POS(x, y);
			if (0 == y && 0 == x) {}// �θ� ��ǥ
			else
			{
				bCreateNode = true;
				if (0 == x || 0 == y) //����, ����
					iDistance = 10;
				else				// �밢��
				{
					iDistance = 14;
					if (POS(1, -1) == POS(x, y))
						bCreateNode = !IsWall(_pField, tPoint + POS(0, 1))
						&& !IsWall(_pField, tPoint + POS(-1, 0));
					if (POS(1, 1) == POS(x, y))
						bCreateNode = !IsWall(_pField, tPoint + POS(-1, 0))
						&& !IsWall(_pField, tPoint + POS(0, -1));
					if (POS(-1, 1) == POS(x, y))
						bCreateNode = !IsWall(_pField, tPoint + POS(0, -1))
						&& !IsWall(_pField, tPoint + POS(1, 0));
					if (POS(-1, -1) == POS(x, y))
						bCreateNode = !IsWall(_pField, tPoint + POS(1, 0))
						&& !IsWall(_pField, tPoint + POS(0, 1));
				}
				if (true == bCreateNode)
				{
					if (false == IsWall(_pField, tPoint))	// ���� �ƴ� ��� OpenNode ����
					{
						iter = FindNodeByPoint(_OpenNode, tPoint);
						if (_OpenNode.end() != iter)					// ���� ��忡 ���� ���
						{
							if ((*iter)->G > (_pSelectNode->G + iDistance))
								(*iter)->pParent = _pSelectNode;
						}
						else	//���� ��忡 ���� ��� ����!
							_OpenNode.push_back(new NODE(tPoint, _pSelectNode, _tEndPoint));
					}
					else		// ���� ���  CloseNode ����
					{
						iter = FindNodeByPoint(_CloseNode, tPoint);
						if (_CloseNode.end() != iter)					// ���� ��忡 ���� ���
						{
							if ((*iter)->G > (_pSelectNode->G + iDistance))
								(*iter)->pParent = _pSelectNode;
						}
						else	// ���� ��忡 ���� ��� ����!
							_CloseNode.push_back(new NODE(tPoint, _pSelectNode, _tEndPoint));
					}
				}
			}
		}
	}
}

list<CAstar::NODE*>::iterator CAstar::FindNodeByPoint(list<NODE*>& _Node, POS & _tPoint)
{
	list<NODE*>::iterator iter = _Node.begin();
	for (; iter != _Node.end(); ++iter)
	{
		if (_tPoint == (*iter)->point)
			break;
	}
	return iter;
}

list<CAstar::NODE*>::iterator CAstar::NextNode(list<NODE*>& _Node)
{
	list<NODE*>::iterator iter = _Node.begin();
	int iSmallestF = (*iter)->F;
	for (; iter != _Node.end(); ++iter)
		if ((*iter)->F < iSmallestF)
		{
			iSmallestF = (*iter)->F;
			break;
		}
	for (iter = _Node.begin(); iter != _Node.end(); ++iter)
		if ((*iter)->F == iSmallestF)
			break;
	return iter;
}

