#pragma once

//map�� find_if�� �����Ҵ�� ���� ���ϱ� ���� �Լ�
class CMyStrCmp
{
public:
	CMyStrCmp() {}
	CMyStrCmp(TCHAR* pString)
		:m_pString(pString)
	{}
	~CMyStrCmp() {}
public:
	template<class T>
	bool operator()(T& rObj)
	{
		return !lstrcmp(rObj.first, m_pString);
	}
private:
	const TCHAR* m_pString;
};