#include "stdafx.h"
#include "StateMgr.h"
#include "StatePattern.h"

CStateMgr::CStateMgr(CStatePattern* _pState)
	: m_pState(_pState)
{
}


CStateMgr::~CStateMgr()
{
	Release();
}

void CStateMgr::Set_State(CStatePattern * _pState)
{
	m_pState = _pState;
}

void CStateMgr::Initialize()
{
	m_pState->Initialize();
}

int CStateMgr::Update()
{
	return m_pState->Update();
}

void CStateMgr::LateUpdate()
{
	m_pState->LateUpdate();
}

void CStateMgr::Render(HDC hDC)
{
	m_pState->Render(hDC);
}

void CStateMgr::Release()
{
	SAFE_DELETE(m_pState);
}
