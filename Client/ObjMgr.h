#pragma once

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
public:
	bool Initialize();
public:
	void AddObject(OBJID::ID eID, CObj* pObj);
	list<CObj*>* Get_List(OBJID::ID eID) {return &m_ObjList[eID];}
	list<CObj*>* Get_List() { return m_ObjList; }

public:
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void DeleteID(OBJID::ID eID);
	void RecogDistAllID(OBJID::ID eID);

private:
	list<CObj*>		m_ObjList[OBJID::END];
	
};