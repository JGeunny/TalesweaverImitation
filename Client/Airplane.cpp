#include "stdafx.h"
#include "Airplane.h"


CAirplane::CAirplane()
{
}


CAirplane::~CAirplane()
{
	Release();
}

void CAirplane::Initialize()
{
	m_tInfo.fcx = 50.f;
	m_tInfo.fcy = 50.f;
	m_tInfo.fx = 400.f;
	m_tInfo.fy = 300.f;
}

int CAirplane::Update()
{
	return 0;
}

void CAirplane::LateUpdate()
{
}

void CAirplane::Render(HDC hDC)
{
	CObj::UpdateRect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CAirplane::Release()
{
}
