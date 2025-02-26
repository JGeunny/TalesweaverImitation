#include "stdafx.h"
#include "StatePattern.h"
#include "Obj.h"

CStatePattern::CStatePattern(CObj * _pObj)
	:m_pObj(nullptr)
{
}

CStatePattern::~CStatePattern()
{
}

void CStatePattern::Set_Obj(CObj * _pObj)
{
	m_pObj = _pObj;
}
