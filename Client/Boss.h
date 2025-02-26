#pragma once
#include "Monster.h"
class CBoss :
	public CMonster
{
public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

	virtual void LateInit();

public:
	virtual void Set_ImgDir(float _fAngle);
	void SceneChange();

	bool& Alter_Clone() {
		return m_bClone;
	}
protected:
	int			m_iFrameScene;
	//슬라이딩 스피드
	DWORD		m_dwSlidingTime;
	int			m_iSliding_Count;
	float		m_fSpeedBuf;
	float		m_fSliding;

	bool		m_dwSpeed;
	bool		m_bSpeed;

	bool		m_bClone;
	bool		m_bCloneDie;
	DWORD		m_dwDieTime;
};

