#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "AfterImage.h"
CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager * CObjectManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CObjectManager;
	return m_pInstance;
}

void CObjectManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance=nullptr;
}

CObjectManager::CObjectManager()
{
	m_iCount = 0;
}


CObjectManager::~CObjectManager()
{
	Release();
}

CGameObject * CObjectManager::GetPlayer() const
{
	if (m_ObjectList[PLAYER].empty())
		return nullptr;

	return m_ObjectList[PLAYER].front();
}

CGameObject* CObjectManager::GetTerrain()
{
	if (m_ObjectList[TERRAIN].empty())
		return nullptr;

	return m_ObjectList[TERRAIN].front();
}



CGameObject * CObjectManager::GetNearTarget(CGameObject * pObject, OBJ_TYPE eType)
{
	if (m_ObjectList[eType].empty())
		return nullptr;

	CGameObject* pNear = m_ObjectList[eType].front();

	float fw = pObject->GetInfo().fX - pNear->GetInfo().fX;
	float fh = pObject->GetInfo().fY - pNear->GetInfo().fY;
	float fNearDist = sqrtf(fw*fw + fh*fh);
	
	for (auto pTarget : m_ObjectList[eType])
	{
		fw = pObject->GetInfo().fX - pTarget->GetInfo().fX;
		fh = pObject->GetInfo().fY - pTarget->GetInfo().fY;
		float fCurdist = sqrtf(fw * fw + fh * fh);
		if (fNearDist > fCurdist)
		{
			pNear = pTarget;
			fNearDist = fCurdist;
		}
	}
	return pNear;

}

void CObjectManager::AddObject(OBJ_TYPE eType, CGameObject * pObject)
{
	m_ObjectList[eType].push_back(pObject);
}

int CObjectManager::Update()
{
	int iEvent = NO_EVENT;
	m_iCount++;

	// 이터레이터 패턴(반복자 패턴)
	// 객체 관리 통일성에 초점을 둔 디자인 패턴
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; )
		{
			iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete((*iter_begin));
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else if (CHANGE_SCENE == iEvent)
				break;
			else
				++iter_begin;
		}
	}
	

	CCollisionManager::CollisionRectEx(m_ObjectList[TILE], m_ObjectList[PLAYER]);
	CCollisionManager::CollisionRect(m_ObjectList[TILE], m_ObjectList[MONSTER]);
	if (!m_ObjectList[AFTERIMAGE].empty())
	{
		m_ObjectList[AFTERIMAGE].front()->SetImageKey(m_ObjectList[PLAYER].front()->GetImageKey());
		if (m_iCount % 3 == 0)
		{
			dynamic_cast<CAfterImage*>(m_ObjectList[AFTERIMAGE].front())->SetPlayerInfo(m_ObjectList[PLAYER].front()->GetWorldPos(), m_ObjectList[PLAYER].front()->GetFrame());
			m_iCount = 0;
		}
	
	}
	CDetectManager::GetInstance()->CollisionRect(m_ObjectList[MONSTER], m_ObjectList[PLAYER]);
	CCollisionManager::CollisionSphere(m_ObjectList[PLAYER], m_ObjectList[BULLET]);
	if (m_ObjectList[PLAYER].front()->GetIsAttk())
		CCollisionManager::CollisionRectKatana(m_ObjectList[PLAYER].front()->GetHitBox(), m_ObjectList[BULLET]);
	//CCollisionMgr::CollisionSphere(m_ObjectList[SHIELD], m_ObjectList[MONSTER]);
	//CCollisionMgr::CollisionRectEx(m_ObjectList[MONSTER], m_ObjectList[PLAYER]);
	return iEvent;
}

void CObjectManager::Render(HDC hdc)
{

	// 이터레이터 패턴(반복자 패턴)
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; ++iter_begin)
			(*iter_begin)->Render(hdc);
	}
}

void CObjectManager::DeleteGroup(OBJ_TYPE eType)
{
	for_each(m_ObjectList[eType].begin(), m_ObjectList[eType].end(), SafeDelete<CGameObject*>);
	m_ObjectList[eType].clear();
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

