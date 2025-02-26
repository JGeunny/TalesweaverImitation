#pragma once
#include"State.h"

class CFSM
{
public:
	CFSM();
	virtual ~CFSM();
	
public:
	void Update();

public:
	void ChangeState(CState* _pState);

protected:
	CState*	 m_pState;
	/*SCENEID m_eCurScene;
	SCENEID m_eNextScene;*/
};

