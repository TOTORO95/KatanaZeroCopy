// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Standard Headers
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;


// User Headers
#include "Define.h"
#include "Struct.h"
#include "Extern.h"
#include "Enum.h"
#include "Function.h"
#include "Typedef.h"

#include "ObjFactory.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include  "SceneManager.h"
#include "LineManager.h"
#include "CollisionManager.h"
#include "DetectManager.h"
#include "CameraMgr.h"

#pragma comment(lib, "msimg32.lib")


#ifdef _DEBUG
// 콘솔창 띄우기
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
// VLD (Visual Leak Detector)
//#include "vld.h"
#endif