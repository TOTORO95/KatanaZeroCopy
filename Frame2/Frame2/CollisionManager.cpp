#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Tile.h"
#include "Player.h"
CCollisionManager* CCollisionManager::m_pInstance = nullptr;
CCollisionManager * CCollisionManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CCollisionManager;
	return m_pInstance;
}

void CCollisionManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			RECT rc = {};

			// �� �簢���� �����Ǿ����� �Ǻ��ϴ� �Լ�. ���������� TRUE, �ƴϸ� FALSE ��ȯ.
			// �� �簢���� �����Ǿ��� �� ��ģ ������ �Ǵٸ� �簢���� ���������. 
			// �� ��ģ �簢���� ù��° ���ڷ� ��ȯ�Ѵ�.
			if (IntersectRect(&rc, &pDest->GetRect(), &pSrc->GetRect()))
			{
				//pDest->IsDead();
				//pSrc->IsDead();
			}
		}
	}
}

void CCollisionManager::CollisionRectEx(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectRectEx(pDest, pSrc, &fMoveX, &fMoveY))
			{
				float fX = pSrc->GetInfo().fX;
				float fY = pSrc->GetInfo().fY;

				if (fMoveX > fMoveY) // Y������ �о
				{
					if (pDest->GetInfo().fY < fY)
						pSrc->SetPos(fX, fY + fMoveY);
					else
						pSrc->SetPos(fX, fY - fMoveY);
				}
				else // X������ �о
				{
					if (pDest->GetInfo().fX < fX)
						pSrc->SetPos(fX + fMoveX, fY);
					else
						pSrc->SetPos(fX - fMoveX, fY);
				}
			}

		}
	}

}

void CCollisionManager::CollisionSphere(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectSphere(pDest, pSrc))
			{
				//pDest->IsDead();
				//pSrc->IsDead();
			}
		}
	}
}

bool CCollisionManager::CollisionRectTile(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto pSrc : srcList)
	{
		for (auto pDest : dstList)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->GetRect(), &pSrc->GetRect()))
			{
				if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 4)
				{
					//cout << "Wall" << endl;
					pSrc->SetWall(pDest->GetInfo().fX);
					dynamic_cast<CPlayer*>(pSrc)->SetIsDbJump(true);
				}
				if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 1)
				{
					cout << "Flat" << endl;
					pSrc->SetFlat(pDest->GetInfo().fY);
					pSrc->SetIsColl(true);
					cout << pDest->GetInfo().fY << endl;
				}


			}
		//dynamic_cast<CPlayer*>(pSrc)->SetIsDbJump(false);
		//pSrc->SetIsColl(false);
		//return false;
		}
	}
	return false;
}

bool CCollisionManager::IntersectSphere(CGameObject* pDest, CGameObject* pSource)
{
	// ���浹
	// �� ���� ������ ���� ���Ѵ�. r1 + r2
	// �� ���� ���� �� �Ÿ��� ���Ѵ�. d
	// r1 + r2 >= d ������ �����ϸ� TRUE

	float r1 = pDest->GetInfo().fCX * 0.5f;
	float r2 = pSource->GetInfo().fCX * 0.5f;

	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// sqrtf: ������ ���ϴ� �Լ�. <cmath>���� ����.
	float d = sqrtf(w * w + h * h);

	return r1 + r2 >= d;
}

bool CCollisionManager::IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY)
{
	// x���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� x���� ������ ���� x���� �Ÿ����� ũ�� x������ ���ƴ�.
	float fSumX = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);

	// y���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� y���� ������ ���� y���� �Ÿ����� ũ�� y������ ���ƴ�.
	float fSumY = pDest->GetInfo().fCY * 0.5f + pSource->GetInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);

	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// ��ģ������ ũ�� ���ϱ�.
		*pMoveX = fSumX - fDistX;
		*pMoveY = fSumY - fDistY;
		return true;
	}

	return false;
}
