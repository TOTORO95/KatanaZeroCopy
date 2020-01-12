#include "stdafx.h"
#include "ImageManager.h"
#include "MyImage.h"
CImageManager* CImageManager::m_pInstance = nullptr;
CImageManager * CImageManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CImageManager();

	return m_pInstance;
}

void CImageManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;

	m_pInstance = nullptr;
}

CImageManager::CImageManager()
{

}


CImageManager::~CImageManager()
{
}

HDC CImageManager::GetMemDC(const wstring & wstrImgKey) const
{ 
	auto itr_find = m_mapImg.find(wstrImgKey);
	if (itr_find == m_mapImg.end())
		return nullptr;
	return itr_find->second->GetMemDC();
}

Gdiplus::Image * CImageManager::GetMemImage(const wstring & wstrImgKey) const
{
	auto itr_find = m_mapImg.find(wstrImgKey);
	if (itr_find == m_mapImg.end())
		return nullptr;

	return itr_find->second->GetIMG();

}

void CImageManager::LoadImg(const wstring & wstrImgKey, const wstring & wstrFilePath)
{
	auto itr_find = m_mapImg.find(wstrImgKey);
	if (itr_find != m_mapImg.end())
		return;

	CMyImage *p_Img = new CMyImage;

	if (!(p_Img->LoadImg(wstrFilePath)))
	{
		delete p_Img;
		p_Img = nullptr;
		MessageBox(nullptr, wstrFilePath.c_str(), L"Image Load Failed", MB_OK);
		return;
	}

	m_mapImg.insert(make_pair(wstrImgKey, p_Img));

}

void CImageManager::Release()
{
	for (auto& MyPair : m_mapImg)
	{
		delete MyPair.second;
		MyPair.second = nullptr;
	}
	m_mapImg.clear();

}
