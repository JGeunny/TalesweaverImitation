#pragma once

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void FrameInfo(HDC _hDC);

private:
	HDC			m_hDC;
};

 