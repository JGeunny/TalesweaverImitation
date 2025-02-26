#pragma once

class CObj;
class CObjMgrBuffer
{
	DECLARE_SINGLETON(CObjMgrBuffer)
public:
	bool Initialize();
public:
	void AddObject(OBJID::ID eID, CObj* pObj);
public:
	int Update();
	void Release();
public:
	list<CObj*>* Get_List(OBJID::ID eID) { return &m_ObjList[eID]; }
	list<CObj*>* Get_List() { return m_ObjList; }
private:
	list<CObj*>		m_ObjList[OBJID::END];

};