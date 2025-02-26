#include "stdafx.h"
#include "FSM.h"


CFSM::CFSM()
{
}


CFSM::~CFSM()
{
}

void CFSM::Update()
{
}

void CFSM::ChangeState(CState * _pState)
{
	if (_pState == m_pState) return;//같은 행동이면 나감

	m_pState->Exit();
	SAFE_DELETE(m_pState);

	m_pState = _pState;
	m_pState->Enter();
}
