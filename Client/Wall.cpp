#include "stdafx.h"
#include "Wall.h"


CWall::CWall()
{
}


CWall::~CWall()
{
}

void CWall::Initialize()
{
	CTile::Initialize();
}

int CWall::Update()
{
	return 0;
}

void CWall::LateUpdate()
{
}

void CWall::Render(HDC hDC)
{
	CTile::Render(hDC);
}

void CWall::Release()
{
}

void CWall::LateInit()
{
}
