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



//#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <ole2.h> 
#include <GdiPlus.h> 
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include <map>
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
using namespace std;

//User Header
#include "Define.h"
#include "Extern.h"
#include "Struct.h"

//Manager

#include "ImageManager.h"