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
	//�ǰ��� �ߴ��� üũ �ϰ� ���� ������ m_dwValidityTime �ð��� �����ٸ� �� ����������
	bool IsHit_Unit(CObj* pUnit);

protected:
	INFO_SKILL	m_tSkill;
	bool		m_bSkill_State[SKILL_STATEID::END];
	int			m_iOption;

	//�ִϸ��̼�
	vector<TCHAR*> m_listImgDir;	//������, ������ ��, ��, ���� ��, ���� -> �ݽð�������� 8�� �ֱ�
	TCHAR* m_pFrameKey;
	/*STATE m_eCurState;
	STATE m_eNextState;*/

	//���� �� Ÿ���� ��� �����־� �������� �������� ���� ��츦 �����ϱ� ���� ����
	map<CObj*, DWORD>	m_mapUnitAttackTime;	//���� ������ ������ �ð��� ����
	DWORD				m_dwValidityTime; 		//m_mapUnitAttackTime �� ���� �ð� �̽ð��� ������ ���� ���ٲ���
	//if (mapInt.find(1) == mapInt.end())
};

