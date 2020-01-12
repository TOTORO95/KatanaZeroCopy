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

bool CMyImage::LoadImg(const wstring & wstrFilePath)
{
	m_CurImg = new Gdiplus::Image(wstrFilePath.c_str(),0);
	
	HDC hdc = GetDC(g_hwnd);
	m_hMemDC = CreateCompatibleDC(hdc);	
	//HBITMAP h=  (HBITMAP)m_CurImg;


	ReleaseDC(g_hwnd, hdc);
	if (m_hMemDC == nullptr)
		return false;
	
	SelectObject(m_hMemDC, (HBITMAP)m_CurImg);
	//cout << "check" << endl;
	//m_OldImg = (Gdiplus::Image*) SelectObject(m_hMemDC, m_CurImg);
	//SelectObject(m_hMemDC, m_CurImg);
	return true;
}

void CMyImage::Release()
{
	SelectObject(m_hMemDC, m_OldImg);
	DeleteObject(m_CurImg);
	DeleteDC(m_hMemDC);
}
