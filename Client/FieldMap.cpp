#include "stdafx.h"
#include "FieldMap.h"
#include "Wall.h"
/*#include "Block.h"
#include "Item.h"
#include "RotateBlock.h"
#include "Turret.h"*/

CFieldMap::CFieldMap()
	:m_lMaxDistance(0), m_lMaxDistanceM(0)
{
	m_iRow = MAXROW;
	m_iCol = MAXCOL;
}

CFieldMap::~CFieldMap()
{
	Release();
}

void CFieldMap::Release()
{
	for (auto& pMap : m_ListMap)
		SAFE_DELETE_ARR_2(pMap, m_iRow);
}

LONG CFieldMap::CreateMap(list<CObj*>* pListObj, int dir, float fSpeed)
{
	for (int i = OBJID::WALL; i <= OBJID::ITEM; ++i)
	{
		for (auto& pObj : pListObj[i])
		{
			SAFE_DELETE(pObj);
		}
		pListObj[i].clear();
	}

	POINT ptThis = {};
	POINT ptNext = {};
	auto ListMap = m_ListMap;

	ptNext = { 0, 0 };
	for (auto& piMap : ListMap)
	{
		ptThis.y = LONG(SIZEY * 0.5 + ptNext.y);
		for (int i = 0; i < m_iRow; ++i)
		{
			ptThis.x = LONG(SIZEX * 0.5 + ptNext.x);
			for (int j = 0; j < m_iCol; ++j)
			{
				switch (piMap[i][j])
				{
				case MAP_WALL:
					//pListObj[OBJID::WALL].emplace_back(CAbstractFactory<CWall>::Create(-1, (float)ptThis.x, (float)ptThis.y, dir, fSpeed));
					pListObj[OBJID::WALL].emplace_back(CAbstractFactory<CWall>::Create(-1, (float)ptThis.x, (float)ptThis.y));
					break;
				/*case MAP_BLOCK:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CBlock>::Create(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed));
					break;
				case MAP_ITEM:
					pListObj[OBJID::ITEM].emplace_back(CAbstractFactory_Obj<CItem>::Create(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed));
					break;
				case MAP_ROTATEBLOCK:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CRotateBlock>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ROTATEBLOCK));
					break;
				case MAP_ROTATEBLOCK_VERTICAL:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CRotateBlock>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ROTATEBLOCK_VERTICAL));
					break;
				case MAP_ROTATEBLOCK_HORIZON:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CRotateBlock>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ROTATEBLOCK_HORIZON));
					break;
				case MAP_ROTATEBLOCK_DIAGONAL:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CRotateBlock>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ROTATEBLOCK_DIAGONAL));
					break;
				case MAP_ROTATEBLOCK_REVDIAGONAL:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CRotateBlock>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ROTATEBLOCK_REVDIAGONAL));
					break;
				case MAP_BLOCK_TURRET:
					pListObj[OBJID::BLOCK].emplace_back(CAbstractFactory_Obj<CTurret>::Create(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed));
					break;
				case MAP_ITEM_SIZEBIG:
					pListObj[OBJID::ITEM].emplace_back(CAbstractFactory_Obj<CItem>::CreateMod(pListObj, (float)ptThis.x, (float)ptThis.y, dir, fSpeed, MAP_ITEM_SIZEBIG));
					break;*/
				default:
					break;
				}
				ptThis.x += SIZEX;
			}
			ptThis.y += SIZEY;
		}
		if (DIR::LEFT == dir)
			ptNext.x += PAGEX;
		if (DIR::RIGHT == dir)
			ptNext.x -= PAGEX;
		if (DIR::UP == dir)
			ptNext.y += PAGEY;
		if (DIR::DOWN == dir)
			ptNext.y -= PAGEY;
	}
	if (DIR::LEFT == dir || DIR::RIGHT == dir)
	{
		m_lMaxDistance = abs(ptNext.x);
		m_lMaxDistanceM = m_lMaxDistance - PAGEX;
	}
	else
	{
		m_lMaxDistance = abs(ptNext.y);
		m_lMaxDistanceM = m_lMaxDistance - PAGEY;
	}

	return m_lMaxDistance;
}

void CFieldMap::Set_Speed(list<CObj*>* pListObj, float fSpeed)
{
	for (int i = OBJID::WALL; i <= OBJID::ITEM; ++i)
	{
		for (auto pObj : pListObj[i])
		{
			pObj->Set_Speed(fSpeed);
		}
	}
}

bool CFieldMap::Set_ListMap(const char * _pFileName)
{
	char szPath[100] = {};
	strcpy_s(szPath, sizeof(szPath), PATH_MAP);
	strcat_s(szPath, _pFileName);

	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, szPath, "rt");
	if (0 == err)
	{
		int** iMap = new int*[m_iRow] {};
		for (int i = 0; i < m_iRow; ++i)
			iMap[i] = new int[m_iCol] {};
		//memset(iMap, 0, sizeof(int)*m_iRow*m_iCol);
		for (int i = 0; i < m_iRow; ++i)
		{
			for (int j = 0; j < m_iCol; ++j)
			{
				int iRead = 0;
				fscanf_s(fp, "%d", &iRead);
				iMap[i][j] = iRead;
			}
		}
		m_ListMap.emplace_back(iMap);
		fclose(fp);
		return true;
	}
	return false;
}

int & CFieldMap::map(int _x, int _y)
{
	static int iTemp = -1;
	int** pMap = m_ListMap.front();
	if ((m_iCol > _x && 0 <= _x) && (m_iRow > _y && 0 <= _y))
		return pMap[_y][_x];
	return iTemp;
}

