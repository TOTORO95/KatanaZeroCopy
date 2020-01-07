// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"
// #define WIN32_LEAN_AND_MEAN   <- 이렇게 주석처리하세요! 
//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <Gdiplus.h>             // GDI+를 사용하기 위한 헤더 파일 
#pragma comment(lib, "gdiplus")  // GDI+를 사용하기 위한 라이브러리 파일 

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <cmath>
#include <list>
#include <time.h>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
using namespace std;

using namespace Gdiplus;
//User Headers
#include "Define.h"
#include "Struct.h"
#include "Enum.h"
#include "Extern.h"
#include "Typedef.h"
#include "Function.h"

//Manager
#include "AbsFactory.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"