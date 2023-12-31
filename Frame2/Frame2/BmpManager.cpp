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
	Release();
}

HDC CBmpManager::GetMemDC(const wstring & wstrImgKey) const	//해당 키값 존재시 dc 반환 
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() == iter_find) // 해당 키값 없으면 nullptr반환
		return nullptr;

	return iter_find->second->GetMemDC();
}
HBITMAP CBmpManager::GetBMP(const wstring & wstrImgKey)
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() == iter_find)
		return nullptr;
	return iter_find->second->GetBMP();
}

void CBmpManager::LoadBmp(const wstring & wstrImgKey, const wstring & wstrFilePath, bool IsRot)
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() != iter_find)
		return;

	CMyBmp* pBmp = new CMyBmp;

	if (!pBmp->LoadBmp(wstrFilePath, IsRot))
	{
		SafeDelete(pBmp);
		MessageBox(nullptr, wstrFilePath.c_str(), L"Image Load Failed", MB_OK);
		return;
	}

	m_mapBmp.insert(make_pair(wstrImgKey, pBmp));
}

void CBmpManager::LoadBmp(const wstring & wstrImgKey, const wstring & wstrFilePath) //이미지를 키값과함께 맵에 저장
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() != iter_find) //해당 키값 존재하면 함수 종료
		return;

	CMyBmp* pBmp = new CMyBmp; //맵에 키값이 존재하지않으면 새로운 비트맵 클래스를 생성

	if (!pBmp->LoadBmp(wstrFilePath))// 이미지를 CMyBmp 클래스에 저장하지못하면 메세지박스 출력
	{
		SafeDelete(pBmp);
		MessageBox(nullptr, wstrFilePath.c_str(), L"Image Load Failed", MB_OK);
		return;
	}

	m_mapBmp.insert(make_pair(wstrImgKey, pBmp)); //키값,클래스 맵에 저장
}

void CBmpManager::Release()
{
	for (auto& MyPair : m_mapBmp)
		SafeDelete(MyPair.second);

	m_mapBmp.clear();
}

