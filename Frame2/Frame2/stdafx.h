// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

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
#pragma comment(lib, "msimg32.lib")


#ifdef _DEBUG
// �ܼ�â ����
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
// VLD (Visual Leak Detector)
#include "vld.h"
#endif