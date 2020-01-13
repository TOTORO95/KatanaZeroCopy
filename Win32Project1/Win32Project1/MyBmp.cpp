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
	// ��Ʈ�� �о����.
	m_hBitmap = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if(m_hBitmap==nullptr)
		return false;
	
	HDC hDC = GetDC(g_hwnd);

	// CreateCompatibleDC: ���DC�� ȣȯ�� �Ǵ� �޸�DC�� �����ϴ� �Լ�.
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hwnd, hDC);
	if(m_hMemDC==nullptr)
		return false;

	// �޸�DC�� �ҷ��� ��Ʈ���� �̸� �׸���.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return true;
}


bool CMyBmp::LoadBmp (const wstring& wstrFilePath, bool isRot)
{
	// ��Ʈ�� �о����.
	m_hBitmap = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (m_hBitmap == nullptr)
		return false;

}



void CMyBmp::Release()
{
	// ���� DC�� ������ ����� �ٷ� ������ �� ���� �ع� �����־�� �Ѵ�.
	SelectObject(m_hMemDC, m_hOldBmp);

	// GDI ������Ʈ ����.
	DeleteObject(m_hBitmap);

	// �޸�DC ����.
	DeleteDC(m_hMemDC);
}
