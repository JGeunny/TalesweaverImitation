#include "stdafx.h"
#include "Item.h"
#include "ImgMgr.h"

CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize()
{
	CImgMgr::Get_Instance()->AddImage(L"item/items.bmp", L"items");

	m_tDraw.fcx = 24;
	m_tDraw.fcy = 24;
	//24*24
	CItem::Set_Kind(CItem::HP);
	m_iCount = 1;
	m_bEquip = false;
	m_bDetailsVeiw = true;
}

int CItem::Update()
{
	if (m_iCount == 0)
		return OBJ_DEAD;
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON, CKeyMgr::SPECIAL))
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);
		if (PtInRect(&m_rtSelectItem, pt))
		{
			return OBJ_SELECT;
		}
	}
	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	TCHAR szInfo[100] = L"";
	TCHAR szTemp[100] = L"";
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"items");
	GdiTransparentBlt(hDC, m_tDraw.fx, m_tDraw.fy, m_tDraw.fcx, m_tDraw.fcy, hMemDC,
		24 * m_eKind, 0, 24, 24, RGB(255, 0, 255));
	RECT rt = m_tDraw.Get_Rect();
	m_rtSelectItem.left = rt.left + 15;
	m_rtSelectItem.top = rt.top + 12;
	m_rtSelectItem.bottom = rt.bottom + 13;

	rt.top += 18;
	rt.bottom += 15;
	rt.left = rt.right + 20;
	rt.right = rt.left + 215;
	//Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);

	if (m_bDetailsVeiw)
	{
		if (CItem::ID::SEED == m_eKind)
			swprintf_s(szInfo, L"%s ", m_tItem.szName);
		else
			swprintf_s(szInfo, L"%s: ", m_tItem.szName);

		if (0 < m_tItem.iAtt)
		{
			swprintf_s(szTemp, L"Att %d ", m_tItem.iAtt);
			lstrcat(szInfo, szTemp);
		}
		if (0 < m_tItem.iHp)
		{
			swprintf_s(szTemp, L"HP %d ", m_tItem.iHp);
			lstrcat(szInfo, szTemp);
		}
		DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER);

		if (CItem::ID::HP == m_eKind || CItem::ID::SEED == m_eKind)
		{
			swprintf_s(szInfo, L"개수 %d", m_iCount);
			DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_RIGHT);
		}

		if (m_bEquip)
		{
			swprintf_s(szInfo, L"<착용중>");
			DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_RIGHT);
		}

		rt.left = rt.right + 10;
		rt.right = rt.left + 50;
		swprintf_s(szInfo, L"%d", m_tItem.iGold);
		DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER | DT_CENTER);


		m_rtSelectItem.right = rt.right;
		rt = m_rtSelectItem;
		//Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);
	}
	else
	{
		if (CItem::ID::SEED == m_eKind)
			swprintf_s(szInfo, L"%s ", m_tItem.szName);
		else
			swprintf_s(szInfo, L"%s: ", m_tItem.szName);
		DrawText(hDC, szInfo, lstrlen(szInfo), &rt, DT_VCENTER);
	}
}

void CItem::Release()
{
}

void CItem::Set_Kind(CItem::ID _eKind)
{
	m_eKind = _eKind;
	m_tItem = INFO_UNIT();
	m_tItem.iAtt = 0;
	m_tItem.iHp = 0;
	switch (_eKind)
	{
	case CItem::HP:
		m_tItem.Fn_Set_Name(L"체력 물약");
		m_tItem.iHp = 1200;
		m_tItem.iGold = 100;
		break;
	case CItem::MP:
		m_tItem.Fn_Set_Name(L"마나 물약");
		m_tItem.iMp = 1200;
		m_tItem.iGold = 100;
		break;
	case CItem::SP:
		m_tItem.Fn_Set_Name(L"지구력 물약");
		m_tItem.iExp = 120;
		m_tItem.iGold = 100;
		break;
	case CItem::ARMOR1:
		m_tItem.Fn_Set_Name(L"초급 갑옷");
		m_tItem.iHp = 1400;
		m_tItem.iGold = 1000;
		break;
	case CItem::ARMOR2:
		m_tItem.Fn_Set_Name(L"중급 갑옷");
		m_tItem.iHp = 2800;
		m_tItem.iGold = 5000;
		break;
	case CItem::SWORD1:
		m_tItem.Fn_Set_Name(L"초급 검");
		m_tItem.iAtt = 500;
		m_tItem.iGold = 1000;
		break;
	case CItem::SWORD2:
		m_tItem.Fn_Set_Name(L"중급 검");
		m_tItem.iAtt = 1600;
		m_tItem.iGold = 5000;
		break;
	case CItem::SHOES1:
		m_tItem.Fn_Set_Name(L"초급 신발");
		m_tItem.iHp = 500;
		m_tItem.iAtt = 100;
		m_tItem.iGold = 1000;
		break;
	case CItem::SHOES2:
		m_tItem.Fn_Set_Name(L"중급 신발");
		m_tItem.iHp = 1000;
		m_tItem.iAtt = 300;
		m_tItem.iGold = 5000;
		break;
	case CItem::RING1:
		m_tItem.Fn_Set_Name(L"초급 반지");
		m_tItem.iHp = 300;
		m_tItem.iAtt = 200;
		m_tItem.iGold = 1000;
		break;
	case CItem::RING2:
		m_tItem.Fn_Set_Name(L"중급 반지");
		m_tItem.iHp = 600;
		m_tItem.iAtt = 600;
		m_tItem.iGold = 5000;
		break;
	case CItem::HAT1:
		m_tItem.Fn_Set_Name(L"초급 모자");
		m_tItem.iHp = 500;
		m_tItem.iAtt = 100;
		m_tItem.iGold = 1000;
		break;
	case CItem::HAT2:
		m_tItem.Fn_Set_Name(L"중급 모자");
		m_tItem.iHp = 1000;
		m_tItem.iAtt = 300;
		m_tItem.iGold = 5000;
		break;
	case CItem::SEED:
		m_tItem.Fn_Set_Name(L"돈주머니 1만 시드의 가치");
		m_tItem.iGold = 10000;
		break;
	case CItem::END:
		break;
	default:
		break;
	}
}
