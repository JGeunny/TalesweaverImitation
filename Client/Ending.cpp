#include "stdafx.h"
#include "Ending.h"
#include "ImgMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CEnding::CEnding()
	:m_iY(0)
{
}

CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"reminiscence.mp3");

	CSceneMgr::g_iNextStage = 0;
	CImgMgr::Get_Instance()->AddImage(L"Menu/Ending.bmp", L"Ending");
	CScrollMgr::ReInitialize();
	for (int i = 0; i < OBJID::END; ++i)
	{
		if ((OBJID::ID)i == OBJID::MOUSE) continue;
		if ((OBJID::ID)i == OBJID::UI) continue;
		CObjMgr::Get_Instance()->DeleteID((OBJID::ID)i);
	}
	TCHAR* pText = nullptr;

	pText = new TCHAR[100];
	lstrcpy(pText, L"시청 해주셔서 감사합니다!");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"쥬신 97기 A1반 정근영");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"도움을 주신분들");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"API와 실무에 필요한 패턴들: 박병건 선생님");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"C++의 기초와 STL: 신우재 선생님");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"테일즈 위버 리소스 지원: 86기 선배님");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"하늘배경, 시작엔딩음악, 편집버튼 지원: 이소정");
	m_listText.emplace_back(pText);

	/*pText = new TCHAR[100];
	lstrcpy(pText, L"비행선 스테이지 배경 이미지 지원: 이소정");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"시작 엔딩 배경 음악 지원: 이소정");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"맵편집기 버튼 지원: 이소정");
	m_listText.emplace_back(pText);*/

	pText = new TCHAR[100];
	lstrcpy(pText, L"총알 이미지 지원: 김관용");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"화살 이미지 지원: 김재우");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"엔딩 화면 지원: 신도원");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"F버튼 지원: 장영철");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"우리반 친구들");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"모두 감사합니다!");
	m_listText.emplace_back(pText);
}

int CEnding::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	//필드로 넘어감
	{
		CScrollMgr::Alter_Scroll().x = 0;
		CScrollMgr::Alter_Scroll().y = 0;
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
		return 0;
	}
	--m_iY;
	return 0;
}

void CEnding::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CEnding::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Ending");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	RECT rt = {0,WINCY + m_iY, WINCX, WINCY + m_iY  + 30};
	int	iY = 0;

	DWORD dwRGB = GetTextColor(hDC);
	HFONT hFont = CreateFont(22, 0, 0, 0, FW_BOLD + 100, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움체"));
	HFONT saveFont = (HFONT)SelectObject(hDC, hFont);
	//SetTextColor(hDC, RGB(0, 0, 0));

	for(auto& pText : m_listText)
	{
		DrawText(hDC, pText, lstrlen(pText), &rt, DT_VCENTER | DT_CENTER);
		iY += 80;
		rt.top = WINCY + m_iY + iY;
		rt.bottom = WINCY + m_iY + 30 + iY;
	}
	DeleteObject(SelectObject(hDC, saveFont));
	SetTextColor(hDC, dwRGB);

}

void CEnding::Release()
{
	for (auto& pText : m_listText)
	{
		SAFE_DELETE(pText)
	}
	m_listText.clear();
}
