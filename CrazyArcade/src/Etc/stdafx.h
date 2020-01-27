// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
#pragma once
#pragma warning(disable : 4996)

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//STL
#include<vector>
#include<map>
#include<string>
#include <memory>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//내가 만든 헤더파일
#include "Common/commonMacroFunction.h"
#include "Manager/Image.h"
#include "Manager/randomFunction.h"
#include "Manager/keyManager.h"
#include "Manager/imageManager.h"
#include "Manager/timeManager.h"
#include "Manager/sceneManager.h"

#include "CrazyArcadeClass/Type.h"
#include "Common/utils.h"
using namespace UTIL;


//======================================
//##			매니저들			  ##
//======================================
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define KEYMANAGER		keyManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()

//======================================
//##			디파인문			  ##
//======================================
#define WINNAME		(LPTSTR)(TEXT("Crazy Arcade"))
#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1200
#define	WINSIZEY	900
#define MAPOFFSET_X 30
#define MAPOFFSET_Y 58
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define BLOCK_WIDTH 60
#define BLOCK_HEIGHT 60
#define NUM_BLOCK_X 15
#define NUM_BLOCK_Y 13

#define BLOCK_DIS_DELAY 0.2f


//player key setting
#define P1_UP 0
#define P1_DOWN 1
#define P1_LEFT 2
#define P1_RIGHT 3
#define P1_EVENT 4
#define P1_USEITEM 5

#define P2_UP 6
#define P2_DOWN 7
#define P2_LEFT 8
#define P2_RIGHT 9
#define P2_EVENT 10
#define P2_USEITEM 11

#define GAME_LMOUSE 12
#define GAME_RMOUSE 13

#define GAME_DEBUGMODE	51
#define GAME_RECTMODE   52

#ifdef _DEBUG
	#define LOG
#endif

//======================================
//## 메인게임 릴리즈에서 사용하는 녀석##
//======================================
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}

//================================================
//전역변수(인스턴스, 윈도우 핸들, 마우스 좌표)  ##
//================================================
extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;
extern bool m_bLoop;
extern bool m_showFPS;
extern bool m_showRect;
extern bool m_debugMode;

//================================================
//             Singleton Macro                  //
//================================================
#define DECLARE_SINGLE(TYPE) \
static TYPE* mInst; \
\
public: \
	static TYPE* GetInst() {\
		if (!mInst)\
			return mInst = new TYPE;\
		return mInst;\
	}\
	void Destroy() {\
		SAFE_DELETE(mInst);\
	} \
private:\
	TYPE();\
	~TYPE();

#define DEFINITION_SINGLE(TYPE) TYPE* TYPE::mInst = nullptr;
#define GET_SINGLE(TYPE) TYPE::GetInst()
#define RELEASE_SINGLE(TYPE) TYPE::GetInst()->Destroy()