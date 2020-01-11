#include "stdafx.h"
#include "MyImage.h"


CMyImage::CMyImage()
	:m_CurImg(nullptr),m_OldImg(nullptr)
{
}


CMyImage::~CMyImage()
{
}

HDC CMyImage::GetMemDC() const
{
	return m_hMemDC;
}

bool CMyImage::LoadBmp(const wstring & wstrFilePath)
{
	m_CurImg = new Gdiplus::Image(wstrFilePath.c_str(),0);
	
	HDC hdc = GetDC(g_hwnd);

	m_hMemDC = CreateCompatibleDC(hdc);

	ReleaseDC(g_hwnd, hdc);
	
	if (m_hMemDC == nullptr)
		return false;



	return true;
}

void CMyImage::Release()
{
	DeleteObject(m_CurImg);
	DeleteDC(m_hMemDC);
}
