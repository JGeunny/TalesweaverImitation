#pragma once

#ifndef __ASTAR_H__
#define __ASTAR_H__

class CFieldMap;
class CAstar
{
public:
	typedef struct tagNode
	{
		POS point;
		POS end;
		int F, G, H;		// F = 비용(G + H) , G = 지난 거리, H = 남은 거리
		tagNode* pParent;
		tagNode() :point(0, 0), pParent(nullptr), end(0, 0), F(0), G(0), H(0) {}
		tagNode(POS _StartPoint, tagNode* _pParent, POS _EndPoint);
	}NODE;
public:
	CAstar() { release(); }
	CAstar(CFieldMap* _pField) { release(); m_pField = _pField; }
	~CAstar() { release(); }

	void Initialize(CFieldMap* _pField) { release(); m_pField = _pField; }
	void SetPoint(INFO_DRAW _tStartPoint, INFO_DRAW _tEndPoint);
	void SetPoint(POS _tStartPoint, POS _tEndPoint);
	list<POS> FindPath();
	list<POS> FindPath(CFieldMap* _pNavi, POS _tStartPoint, POS _tEndPoint);
	bool IsWall(POS _tPoint);
	bool IsWall(CFieldMap* _pField, POS _tPoint);
	//void Render();

	POS tStartPoint;
	POS tEndPoint;
private:
	void ExploreNode(CFieldMap* _pField, NODE* _pSelectNode, list<NODE*>& _OpenNode, list<NODE*>& _CloseNode, POS _tEndPoint);
	list<NODE*>::iterator FindNodeByPoint(list<NODE*>& _Node, POS& _tPoint);
	list<NODE*>::iterator NextNode(list<NODE*>& _Node);
	void release()
	{
		m_pField = nullptr;
		tStartPoint = POS(0, 0);
		tEndPoint = POS(0, 0);
	}

	CFieldMap* m_pField;
};

#endif // !__ASTAR_H__