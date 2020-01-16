#include "stdafx.h"
#include "DetectManager.h"
#include "GameObject.h"
#include "Monster.h"
CDetectManager* CDetectManager::m_pInstance = nullptr;
CDetectManager * CDetectManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CDetectManager;
	return m_pInstance;
}

void CDetectManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}

CDetectManager::CDetectManager()
{
	
}


CDetectManager::~CDetectManager()
{
}

bool CDetectManager::CollisionRect(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto pSrc : srcList)
	{
		for (auto pDest : dstList)
		{
			float fX = pSrc->GetInfo().fX;
			float fY = pSrc->GetInfo().fY;
			RECT rc = {};
			if (IntersectRect(&rc, &dynamic_cast<CMonster*>(pDest)->GetDetectRect(), &pSrc->GetRect()))
			{
				dynamic_cast<CMonster*>(pDest)->SetTarget(pSrc->GetInfo(), true);
				cout << "Ãæµ¹" << endl;
			}

		}
	}
	return false;
}
