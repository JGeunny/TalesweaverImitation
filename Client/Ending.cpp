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
	lstrcpy(pText, L"��û ���ּż� �����մϴ�!");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"��� 97�� A1�� ���ٿ�");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"������ �ֽźе�");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"API�� �ǹ��� �ʿ��� ���ϵ�: �ں��� ������");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"C++�� ���ʿ� STL: �ſ��� ������");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"������ ���� ���ҽ� ����: 86�� �����");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"�ϴù��, ���ۿ�������, ������ư ����: �̼���");
	m_listText.emplace_back(pText);

	/*pText = new TCHAR[100];
	lstrcpy(pText, L"���༱ �������� ��� �̹��� ����: �̼���");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"���� ���� ��� ���� ����: �̼���");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"�������� ��ư ����: �̼���");
	m_listText.emplace_back(pText);*/

	pText = new TCHAR[100];
	lstrcpy(pText, L"�Ѿ� �̹��� ����: �����");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"ȭ�� �̹��� ����: �����");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"���� ȭ�� ����: �ŵ���");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"F��ư ����: �念ö");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"�츮�� ģ����");
	m_listText.emplace_back(pText);

	pText = new TCHAR[100];
	lstrcpy(pText, L"��� �����մϴ�!");
	m_listText.emplace_back(pText);
}

int CEnding::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))	//�ʵ�� �Ѿ
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
	HFONT hFont = CreateFont(22, 0, 0, 0, FW_BOLD + 100, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����ü"));
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
