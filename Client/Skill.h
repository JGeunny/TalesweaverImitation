#pragma once
#include "Obj.h"
class CSkill :
	public CObj
{
public:
	CSkill();
	virtual ~CSkill();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void LateInit();

public:
	INFO_SKILL& Alter_SkillInfo() { return m_tSkill; }
	bool& Alter_SkillState(SKILL_STATEID::ID _eId) { return m_bSkill_State[_eId]; }

public:
	virtual int& Alter_Option() { return m_iOption; }

public:
	virtual void Set_ImgDir(float _fAngle);
	virtual void SceneChange() {};

public:
	//또공격 했는지 체크 하고 만약 때린뒤 m_dwValidityTime 시간이 지났다면 또 때릴수있음
	bool IsHit_Unit(CObj* pUnit);

protected:
	INFO_SKILL	m_tSkill;
	bool		m_bSkill_State[SKILL_STATEID::END];
	int			m_iOption;

	//애니매이션
	vector<TCHAR*> m_listImgDir;	//오른쪽, 오른쪽 위, 위, 왼쪽 위, 왼쪽 -> 반시계방향으로 8개 넣기
	TCHAR* m_pFrameKey;
	/*STATE m_eCurState;
	STATE m_eNextState;*/

	//공격 한 타겟이 계속 겹쳐있어 연속으로 데미지가 들어가는 경우를 방지하기 위한 변수
	map<CObj*, DWORD>	m_mapUnitAttackTime;	//최초 공격한 유닛의 시간을 저장
	DWORD				m_dwValidityTime; 		//m_mapUnitAttackTime 의 유지 시간 이시간이 지나면 삭제 해줄꺼임
	//if (mapInt.find(1) == mapInt.end())
};

