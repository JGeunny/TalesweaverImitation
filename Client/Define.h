#pragma once

/*#include <crtdbg.h>
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__,__LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif*/

//타일 매니져
#define TILEX			g_iTileX
#define TILEY			g_iTileY

#define TILECX			30
#define TILECY			30

//전체 화면
#define WINCX			800
#define WINCY			600
//CFieldMap===============================
//맵의 크기
#define PAGEX			800
#define PAGEY			600
#define MAXCOL			16
#define MAXROW			12
//오브젝트의 크기
#define SIZEX			50
#define SIZEY			50
//패턴의 경로
#define PATH_MAP		"../Data/"
#define FILENAME_0		"m0.txt"
#define FILENAME_1		"m1.txt"
#define FILENAME_2		"m2.txt"
#define FILENAME_3		"m3.txt"
#define FILENAME_4		"m4.txt"
#define FILENAME_5		"m5.txt"
#define FILENAME_6		"m6.txt"
#define FILENAME_7		"m7.txt"
#define FILENAME_8		"m8.txt"
#define FILENAME_9		"m9.txt"
#define FILENAME_10		"m10.txt"
#define FILENAME_11		"m11.txt"

//그림의 경로
#define PATH_IMAGE			L"../Image/"
#define FILENAME_BG			L"background.bmp"
#define FILENAME_BAD		L"BAD.bmp"
#define FILENAME_BLOCK		L"block.bmp"
#define FILENAME_CAKE		L"CAKE.bmp"
#define FILENAME_DISTRACT	L"distract.bmp"
#define FILENAME_ITEM		L"item.bmp"
#define FILENAME_PLAYERPOS	L"kirbywhere.bmp"
#define FILENAME_PLAYER_0	L"p0.bmp"
#define FILENAME_PLAYER_1	L"p1.bmp"
#define FILENAME_PLAYER_2	L"p2.bmp"
#define FILENAME_PLAYER_3	L"p3.bmp"
#define FILENAME_PLAYER_4	L"p4.bmp"
#define FILENAME_WALL		L"WALL.bmp"
#define FILENAME_TITLE		L"title.bmp"

//오브젝트 인덱스
#define MAP_WALL						1
#define MAP_BLOCK						2
#define MAP_ITEM						3
#define MAP_ROTATEBLOCK					4
#define MAP_ROTATEBLOCK_VERTICAL		5
#define MAP_ROTATEBLOCK_HORIZON			6
#define MAP_ROTATEBLOCK_DIAGONAL		7
#define MAP_ROTATEBLOCK_REVDIAGONAL		8
#define MAP_BLOCK_TURRET				9
#define MAP_ITEM_SIZEBIG				10
//CFieldMap 끝===============================

#define PI					3.1415926536f

#define ipow(a, b)			(int)pow(a, b)
#define OPTION_NO			0
#define OPTION_1			1
#define OPTION_2			2
#define OPTION_3			ipow(2, 2)

#define OBJ_NOEVENT			OPTION_NO
#define OBJ_DEAD			OPTION_1
#define OBJ_SELECT			OPTION_2

#define DISPLAY_NO			OPTION_NO
#define DISPLAY_TITLE		OPTION_1
#define DISPLAY_DISTANCE	OPTION_2
#define DISPLAY_SCORE		OPTION_3
#define DISPLAY_ALL			OPTION_1 + OPTION_2 + OPTION_3

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}
#define SAFE_DELETE_ARR(p) if(p){ delete[] p; p = nullptr;}
#define SAFE_DELETE_ARR_2(p, row) if(p) {for (int i = 0; i < row; ++i){delete[] p[i]; p[i] = nullptr;}delete[] p; p = nullptr;}

//팀 선택
#define TEAM_MOUSE		-99
#define TEAM_TILE		-1
#define TEAM_1			1
#define TEAM_2			2
#define TEAM_3			3
#define TEAM_4			4


#define DECLARE_SINGLETON(Class)		\
private:								\
	Class();							\
	~Class();							\
public:									\
static Class* Get_Instance()			\
{										\
	if (nullptr == m_pInstance)			\
		m_pInstance = new Class;		\
										\
	return m_pInstance;					\
}										\
static void Destroy_Instance()			\
{										\
	if (m_pInstance)					\
	{									\
		delete m_pInstance;				\
		m_pInstance = nullptr;			\
	}									\
}										\
private:								\
	static Class* m_pInstance;		

#define IMPLEMENT_SINGLETON(Class)		\
Class* Class::m_pInstance = nullptr;