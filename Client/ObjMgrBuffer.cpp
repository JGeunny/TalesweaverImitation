#include "stdafx.h"
#include "ObjMgrBuffer.h"
#include "ObjMgr.h"

IMPLEMENT_SINGLETON(CObjMgrBuffer)
CObjMgrBuffer::CObjMgrBuffer()
{
}


CObjMgrBuffer::~CObjMgrBuffer()
{
	Release();
}

bool CObjMgrBuffer::Initialize()
{
	return true;
}

void CObjMgrBuffer::AddObject(OBJID::ID eID, CObj * pObj)
{
	m_ObjList[eID].emplace_back(pObj);
}

int CObjMgrBuffer::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			CObjMgr::Get_Instance()->Get_List((OBJID::ID)i)->emplace_back(pObj);
		}
		m_ObjList[i].clear();
	}
	return 0;
}

void CObjMgrBuffer::Release()
{
	for (auto& listObj : m_ObjList)
	{
		listObj.clear();
	}
}