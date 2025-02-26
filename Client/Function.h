#pragma once

//map의 find_if의 동적할당된 글자 비교하기 위한 함수
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