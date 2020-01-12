#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
}

HDC CMyBmp::GetMemDC() const
{
	return m_hMemDC;
}

bool CMyBmp::LoadBmp(const wstring& wstrFilePath)
{
	// 비트맵 읽어오기.
	m_hBitmap = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if(m_hBitmap==nullptr)
		return false;
	
	HDC hDC = GetDC(g_hwnd);

	// CreateCompatibleDC: 출력DC와 호환이 되는 메모리DC를 생성하는 함수.
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hwnd, hDC);
	if(m_hMemDC==nullptr)
		return false;

	// 메모리DC에 불러온 비트맵을 미리 그린다.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return true;
}


bool CMyBmp::LoadBmp (const wstring& wstrFilePath, bool isRot)
{
	// 비트맵 읽어오기.
	m_hBitmap = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (m_hBitmap == nullptr)
		return false;

}



void CMyBmp::Release()
{
	// 당장 DC가 선택한 대상은 바로 해제할 수 없어 해방 시켜주어야 한다.
	SelectObject(m_hMemDC, m_hOldBmp);

	// GDI 오브젝트 해제.
	DeleteObject(m_hBitmap);

	// 메모리DC 해제.
	DeleteDC(m_hMemDC);
}
