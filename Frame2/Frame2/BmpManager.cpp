#include "stdafx.h"
#include "BmpManager.h"
#include "MyBmp.h"

CBmpManager* CBmpManager::m_pInstance = nullptr;
CBmpManager * CBmpManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CBmpManager;
	return m_pInstance;
}

void CBmpManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;

	m_pInstance = nullptr;

}

CBmpManager::CBmpManager()
{
}


CBmpManager::~CBmpManager()
{

}

HDC CBmpManager::GetMemDC(const wstring & wstrImgKey) const
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() == iter_find)
		return nullptr;

	return iter_find->second->GetMemDC();
}

void CBmpManager::LoadBmp(const wstring & wstrImgKey, const wstring & wstrFilePath)
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() != iter_find)
		return;

	CMyBmp* pBmp = new CMyBmp;

	if (!pBmp->LoadBmp(wstrFilePath))
	{
		SafeDelete(pBmp);
		MessageBox(nullptr, wstrFilePath.c_str(), L"Image Load Failed", MB_OK);
		return;
	}

	m_mapBmp.insert(make_pair(wstrImgKey, pBmp));
}

void CBmpManager::Release()
{
	for (auto& MyPair : m_mapBmp)
		SafeDelete(MyPair.second);

	m_mapBmp.clear();
}

