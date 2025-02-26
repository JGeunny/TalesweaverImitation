#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID { SCENE_LOADING, SCENE_LOGO, SCENE_MENU, SCENE_EDIT
		, SCENE_TOWN, SCENE_STORE, SCENE_FIELD
		, SCENE_DUN1, SCENE_DUN2, SCENE_BOSS, SCENE_FINISH, SCENE_ENDING, SCENE_END };
public:
	void SceneChange(SCENEID eSceneID);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

private:
	CScene* m_pScene;
	SCENEID m_eCurScene;
	SCENEID m_eNextScene;


public:
	static int g_iNextStage;
	static INFO_UNIT g_tPlayerUnitInfo;
};

