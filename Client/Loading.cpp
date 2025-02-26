#include "stdafx.h"
#include "Loading.h"
#include "ImgMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLoading::CLoading()
{
}


CLoading::~CLoading()
{
	Release();
}

void CLoading::Initialize()
{
	m_iNextLoading = 0;
	CImgMgr::Get_Instance()->AddImage(L"Loading/Loading.bmp", L"Loading");
	CImgMgr::Get_Instance()->AddImage(L"Loading/LoadingBar.bmp", L"LoadingBar");
	CImgMgr::Get_Instance()->AddImage(L"Loading/LoadingProgress.bmp", L"LoadingProgress");
	m_eState = CLoading::LOGO;

	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"xtown.mp3");
}

int CLoading::Update()
{
	switch (m_eState)
	{
	case CLoading::LOGO:
		lstrcpy(m_szLoadingInfo, L"로고 이미지 불러오는 중...");
		CImgMgr::Get_Instance()->AddImage(L"Logo/MyLogo.bmp", L"Logo");
		break;
	case CLoading::MAP:
		lstrcpy(m_szLoadingInfo, L"맵 이미지 불러오는 중...");
		CImgMgr::Get_Instance()->AddImage(L"Map/Boss.bmp", L"Boss");
		CImgMgr::Get_Instance()->AddImage(L"Map/Dun1.bmp", L"Dun1");
		CImgMgr::Get_Instance()->AddImage(L"Map/Dun2.bmp", L"Dun2");
		CImgMgr::Get_Instance()->AddImage(L"Map/Field.bmp", L"Field");
		CImgMgr::Get_Instance()->AddImage(L"Map/Store.bmp", L"Store");
		CImgMgr::Get_Instance()->AddImage(L"Map/Town.bmp", L"Town");
		CImgMgr::Get_Instance()->AddImage(L"Map/FinishStage.bmp", L"FinishStage");
		CImgMgr::Get_Instance()->AddImage(L"Map/FinishStageBackGround.bmp", L"FinishStageBackGround");
		break;
	case CLoading::UNIT:
		lstrcpy(m_szLoadingInfo, L"유닛 이미지 불러오는중...");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_Down_.bmp", L"Player_Down_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_Left_.bmp", L"Player_Left_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_LeftDown_.bmp", L"Player_LeftDown_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_LeftUp_.bmp", L"Player_LeftUp_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_Right_.bmp", L"Player_Right_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_RightDown_.bmp", L"Player_RightDown_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_RightUp_.bmp", L"Player_RightUp_");
		CImgMgr::Get_Instance()->AddImage(L"Player/Player_Up_.bmp", L"Player_Up_");

		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_LD.bmp", L"MonsterJelly_LD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_LU.bmp", L"MonsterJelly_LU");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_RD.bmp", L"MonsterJelly_RD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterJelly_RU.bmp", L"MonsterJelly_RU");

		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterF_LD.bmp", L"MonsterF_LD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterF_LU.bmp", L"MonsterF_LU");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterF_RD.bmp", L"MonsterF_RD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterF_RU.bmp", L"MonsterF_RU");

		CImgMgr::Get_Instance()->AddImage(L"Monster/Boss_Boris.bmp", L"Boss_Boris");

		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_LD.bmp", L"MonsterWizard_LD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_LU.bmp", L"MonsterWizard_LU");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_RD.bmp", L"MonsterWizard_RD");
		CImgMgr::Get_Instance()->AddImage(L"Monster/MonsterWizard_RU.bmp", L"MonsterWizard_RU");

		CImgMgr::Get_Instance()->AddImage(L"Boss/BossLive.bmp", L"BossLive");
		CImgMgr::Get_Instance()->AddImage(L"Boss/BossDead.bmp", L"BossDead");

		CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson1.bmp", L"AirshipPerson1");
		CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson2.bmp", L"AirshipPerson2");
		CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson3.bmp", L"AirshipPerson3");
		CImgMgr::Get_Instance()->AddImage(L"Boss/AirshipPerson4.bmp", L"AirshipPerson4");

		CImgMgr::Get_Instance()->AddImage(L"Pet/Normal_Left.bmp", L"Normal_Left");
		CImgMgr::Get_Instance()->AddImage(L"Pet/Normal_Right.bmp", L"Normal_Right");
		m_iNextLoading = 1;
		break;
	case CLoading::SKILL:
		lstrcpy(m_szLoadingInfo, L"스킬 이미지 불러오는 중...");
		CImgMgr::Get_Instance()->AddImage(L"Skill/Skill_Soul.bmp", L"Skill_Soul");
		CImgMgr::Get_Instance()->AddImage(L"Skill/MultiAttack.bmp", L"MultiAttack");
		CImgMgr::Get_Instance()->AddImage(L"Skill/Bullet_Orange_20.bmp", L"Bullet_Orange_20");

		CImgMgr::Get_Instance()->AddImage(L"Skill/BOW_LEFT.bmp", L"BOW_LEFT");
		CImgMgr::Get_Instance()->AddImage(L"Skill/BOW_RIGHT.bmp", L"BOW_RIGHT");
		break;
	case CLoading::EFFECT:
		lstrcpy(m_szLoadingInfo, L"특수 효과 이미지 불러오는 중...");
		CImgMgr::Get_Instance()->AddImage(L"Effect/Portal.bmp", L"Portal");
		CImgMgr::Get_Instance()->AddImage(L"Effect/Portal2.bmp", L"Portal2");
		CImgMgr::Get_Instance()->AddImage(L"Effect/Explosion.bmp", L"Explosion");
		CImgMgr::Get_Instance()->AddImage(L"Effect/StageState.bmp", L"StageState");
		CImgMgr::Get_Instance()->AddImage(L"Effect/LvUp.bmp", L"LvUp");
		CImgMgr::Get_Instance()->AddImage(L"Effect/DmgFont.bmp", L"DmgFont");
		CImgMgr::Get_Instance()->AddImage(L"Effect/Crash.bmp", L"Crash");
		CImgMgr::Get_Instance()->AddImage(L"Effect/Crash2.bmp", L"Crash2");
		break;
	case CLoading::UI:
		lstrcpy(m_szLoadingInfo, L"인터페이스 이미지 불러오는 중...");
		CImgMgr::Get_Instance()->AddImage(L"ui/Equip_Info.bmp", L"Equip_Info");
		CImgMgr::Get_Instance()->AddImage(L"ui/trade.bmp", L"trade");
		CImgMgr::Get_Instance()->AddImage(L"ui/Inven_Info.bmp", L"Inven_Info");
		CImgMgr::Get_Instance()->AddImage(L"ui/Player_Stats.bmp", L"Player_Stats");
		CImgMgr::Get_Instance()->AddImage(L"ui/Player_Info.bmp", L"Player_Info");
		CImgMgr::Get_Instance()->AddImage(L"ui/Player_Hp.bmp", L"Player_Hp");
		CImgMgr::Get_Instance()->AddImage(L"ui/Player_Mp.bmp", L"Player_Mp");
		CImgMgr::Get_Instance()->AddImage(L"ui/Player_Sp.bmp", L"Player_Sp");
		CImgMgr::Get_Instance()->AddImage(L"Monster/BorisBar.bmp", L"BorisBar");
		CImgMgr::Get_Instance()->AddImage(L"Monster/BorisHp.bmp", L"BorisHp");

		CImgMgr::Get_Instance()->AddImage(L"MyFont/TextUI.bmp", L"TextUI");
		CImgMgr::Get_Instance()->AddImage(L"Menu/Ending.bmp", L"Ending");
		break;
	case CLoading::END:
		lstrcpy(m_szLoadingInfo, L"로딩 완료! 엔터를 눌러주세요!");
		break;
	default:
		break;
	}
	if(m_eState != CLoading::END)
		m_eState = (CLoading::STATE)((int)m_eState + 1);

	return 0;
}

void CLoading::LateUpdate()
{
	if (m_eState == CLoading::END)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);
		}
	}
}


void CLoading::Render(HDC hDC)
{
	HDC hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"Loading");
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 450 * m_iNextLoading, 512, 450, SRCCOPY);

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"LoadingBar");
	POINT ptXY = { LONG(WINCX *0.25 - 45) , LONG(WINCY *0.75 - 30) };
	//StretchBlt(hDC, ptXY.x, ptXY.y, 500, 70, hMemDC, 0, 0, 170, 46, SRCCOPY);
	GdiTransparentBlt(hDC, ptXY.x, ptXY.y, 500, 70, hMemDC,
		0, 0, 170, 46,
		RGB(255, 0, 255));
	

	hMemDC = CImgMgr::Get_Instance()->GetImgDC(L"LoadingProgress");
	StretchBlt(hDC, ptXY.x +16, ptXY.y +31, 
		(int)m_eState * 471 / (int)CLoading::END, 
		24, hMemDC, 0, 0, 
		(int)m_eState * 159 / (int)CLoading::END, 15, SRCCOPY);

	DWORD dwRGB = GetTextColor(hDC);
	SetTextColor(hDC, RGB(0,0,0));
	//위치 바 + 16, 31 최대 크기 471, 24
	TextOut(hDC, ptXY.x + 13, ptXY.y + 10, m_szLoadingInfo, lstrlen(m_szLoadingInfo));
	SetTextColor(hDC, dwRGB);
}

void CLoading::Release()
{
	CImgMgr::Get_Instance()->EraseImgDC(L"Loading");
	CImgMgr::Get_Instance()->EraseImgDC(L"LoadingBar");
	CImgMgr::Get_Instance()->EraseImgDC(L"LoadingProgress");
}
