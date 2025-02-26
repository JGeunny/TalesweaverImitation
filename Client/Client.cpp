// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "crtdbg.h"

// Console 창을 띄우기 위해서...
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

// Memory Leak Detection을 위해서...
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif


#include "stdafx.h"
#include "Client.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWND;
int g_iTileX;
int g_iTileY;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 코드 진입부의 가장 맨 윗쪽에 넣어 줘야함.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(숫자); // 메모리 누수 위치.
	//_CrtSetBreakAlloc(6666); // 메모리 누수 위치.

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	msg.message = WM_NULL;

	g_iTileX = 100;
	g_iTileY = 100;
	CMainGame Main;
	Main.Initialize();

	//GetTickCount() - 대략 1/1000 초를 반환해 주는 함수. 
	DWORD dwOldTime = GetTickCount();
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//대략 0.03초 마다 갱신/
			if (dwOldTime + 30 < GetTickCount())
			{
				dwOldTime = GetTickCount();
				Main.Update();
				Main.LateUpdate();
				Main.Render();
			}
		}
	}

	//_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	RECT rc = { 0, 0, WINCX, WINCY };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); 

	lstrcpy(szTitle, L"이것은 테일즈 위버인가 스타인가 디아블로인가?");
	HWND hWnd = CreateWindowW(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0,
		rc.right - rc.left, rc.bottom - rc.top,
		nullptr,nullptr,hInstance,nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	g_hWND = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			//DestroyWindow(hWnd);
			break;
		default:
			break;
		}
	}
	break;
	/*case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINCX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINCY;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINCX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINCY;
		return FALSE;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
