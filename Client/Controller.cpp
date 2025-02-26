#include "stdafx.h"
#include "Controller.h"

CController* CController::m_pInstance = nullptr;
CController::CController()
	:m_pTarget(nullptr),
	m_pMouse(nullptr)
{
}


CController::~CController()
{
	Release();
}

bool CController::Initialize()
{
	return false;
}

void CController::Set_Target(CObj * pObj)
{
	m_pTarget = pObj;
	//m_pTarget->Set_Target(true);
}

void CController::Set_Mouse(CObj * pObj)
{
	m_pMouse = pObj;
}

CObj * CController::Get_Target()
{
	return m_pTarget;
}

CObj * CController::Get_Mouse()
{
	return m_pMouse;
}

int CController::Update()
{
	if (nullptr == m_pTarget) return OBJ_NOEVENT;
	if (true == m_pTarget->Get_Dead())
	{
		m_pTarget = nullptr;
		return OBJ_NOEVENT;
	}
	m_pTarget->Control();
	return m_pTarget->Update();
}

void CController::LateUpdate()
{
	if (nullptr == m_pTarget) return;
	m_pTarget->LateUpdate();
}

void CController::Render(HDC hDC)
{
	if (nullptr == m_pTarget) return;
	m_pTarget->Render(hDC);
}

void CController::Release()
{
	m_pTarget = nullptr;
}
