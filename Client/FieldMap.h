#pragma once

class CObj;
class CFieldMap
{
public:
	CFieldMap();
	~CFieldMap();

	void Release();
	LONG CreateMap(list<CObj*>* pListObj, int dir, float speed = 2.0f);
	void Set_Speed(list<CObj*>* pListObj, float fSpeed);
public:
	int Get_Row() { return m_iRow; }
	int Get_Col() { return m_iCol; }
	bool Set_ListMap(const char* _pFileName);
	list<int**>& Get_ListMap() { return m_ListMap; }
	LONG Get_MaxDistance() { return m_lMaxDistance; }
	LONG Get_MaxDistanceM() { return m_lMaxDistanceM; }

	//AStar에서 사용하기 위한 함수
	int & map(int _x, int _y);
private:
	int m_iRow;
	int m_iCol;
	list<int**> m_ListMap;

	LONG m_lMaxDistance;
	LONG m_lMaxDistanceM;//총 거리에서 한칸을 뺀 값 (인터페이스의 거리 랜더에서 필요)
};

