#pragma once
#include "Unit.h"
class CAircraftCarrier :
	public CUnit
{
public:
	CAircraftCarrier();
	virtual ~CAircraftCarrier();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

	void MoveFrameAircraft();

protected:
	//애니메이션
	FRAME		m_tFramePerson[4];
	INFO_DRAW	m_tDrawPerson[4];
	TCHAR*		m_pFrameKeyPerson[4];

	INFO_DRAW	m_tDrawSlaves[4];


	float		m_fRunSpeed;
	bool		m_bRunEnd;
	
};

