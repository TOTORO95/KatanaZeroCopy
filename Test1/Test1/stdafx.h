// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"
// #define WIN32_LEAN_AND_MEAN   <- �̷��� �ּ�ó���ϼ���! 
//#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <Gdiplus.h>             // GDI+�� ����ϱ� ���� ��� ���� 
#pragma comment(lib, "gdiplus")  // GDI+�� ����ϱ� ���� ���̺귯�� ���� 

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