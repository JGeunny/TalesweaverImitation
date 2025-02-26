#include "stdafx.h"
#include "Astar.h"
#include "FieldMap.h"

CAstar::tagNode::tagNode(POS _StartPoint, tagNode * _pParent, POS _EndPoint)
	:point(_StartPoint), pParent(_pParent), end(_EndPoint), F(0), G(0), H(0)
{
	int x = 0, y = 0;	// 상대 좌표 값(부모 좌표-자식 좌표)
	if (nullptr == pParent)	// 부모가 없는 경우
		G = 0;
	else
	{
		x = point.x - pParent->point.x;
		y = point.y - pParent->point.y;
		if (0 == x || 0 == y)	// 십자인 경우
			G = pParent->G + 10;
		else if (0 != x && 0 != y)	// 대각 선인 경우
			G = pParent->G + 14;
		else // 에러(부모와 좌표가 같은 경우)(0 == x && 0 == y)
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

	if ((OpenNode.end() != OpenNode.begin())) // 길을 찾은 경우
	{
		iter = FindNodeByPoint(OpenNode, _tEndPoint); // 목적지의 노드를 찾아서 iter에 저장
		for (pSelectNode = *iter; pSelectNode->pParent != NULL; pSelectNode = pSelectNode->pParent)  // 부모가 NULL일 때까지 path에 경로 저장
			path.push_back(POS(pSelectNode->point));
		path.push_back(POS(pSelectNode->point)); // 부모가 NULL인 경우의 path까지 저장(출발 지점)
		path.reverse(); // 목적지점으부터 역순으로 입력했으므로 다시 역순으로 뒤집어 출발지점이 첫 번째가 되도록 함.

		for (iter = OpenNode.begin(); iter != OpenNode.end(); ++iter)// 길을 찾은 경우 동적할당 해제
			delete *iter; // 열린 노드 동적할당 해제

		for (iter = CloseNode.begin(); iter != CloseNode.end(); ++iter)
			delete *iter; // 닫힌 노드 동적할당 해제

		return path; // 길을 찾은 경우 리턴
	}

	// 길을 찾지 못한 경우 동적할당 해제
	for (iter = CloseNode.begin(); iter != CloseNode.end(); iter++)
		delete *iter; // 닫힌 노드 동적할당 해제
	return path; // 길을 찾지 못한 경우 리턴
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
			if (0 == y && 0 == x) {}// 부모 좌표
			else
			{
				bCreateNode = true;
				if (0 == x || 0 == y) //수직, 수평
					iDistance = 10;
				else				// 대각선
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
					if (false == IsWall(_pField, tPoint))	// 벽이 아닐 경우 OpenNode 참조
					{
						iter = FindNodeByPoint(_OpenNode, tPoint);
						if (_OpenNode.end() != iter)					// 오픈 노드에 있을 경우
						{
							if ((*iter)->G > (_pSelectNode->G + iDistance))
								(*iter)->pParent = _pSelectNode;
						}
						else	//오픈 노드에 없을 경우 생성!
							_OpenNode.push_back(new NODE(tPoint, _pSelectNode, _tEndPoint));
					}
					else		// 벽일 경우  CloseNode 참조
					{
						iter = FindNodeByPoint(_CloseNode, tPoint);
						if (_CloseNode.end() != iter)					// 닫힌 노드에 있을 경우
						{
							if ((*iter)->G > (_pSelectNode->G + iDistance))
								(*iter)->pParent = _pSelectNode;
						}
						else	// 닫힌 노드에 없을 경우 생성!
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

