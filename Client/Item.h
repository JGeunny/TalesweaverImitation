#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();
	enum ID {HP, MP, SP, ARMOR1, ARMOR2, SWORD1, SWORD2, SHOES1, SHOES2, RING1, RING2, HAT1, HAT2, SEED, END};
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	INFO_UNIT& Alter_Item() { return m_tItem; }
	void Set_Kind(CItem::ID _eKind);
	CItem::ID Get_Kind(){return m_eKind;}

	int&	Alter_ItemCount() { return m_iCount; }
	bool&	Alter_Equip() { return m_bEquip; }
	bool&	Alter_DetailsVeiw() { return m_bDetailsVeiw; }
protected:
	INFO_UNIT	m_tItem;
	CItem::ID	m_eKind;
	RECT		m_rtSelectItem;

	int			m_iCount;
	bool		m_bEquip;// 착용 상태를 확인하기 위한
	
	bool		m_bDetailsVeiw;
};

