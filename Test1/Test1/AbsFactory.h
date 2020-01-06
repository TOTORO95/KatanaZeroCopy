#pragma once
#ifndef __ABSFACTORY_H__
class CGameObject;

template <typename T>
class AbsFactory
{
	public:
	static CGameObject* CreateObject()
	{
		CGameObject* pObj = new T;
		pObj->Initialize();

		return pObj;
	}


	static CGameObject* CreateObject(float x, float y)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(x, y);

		return pObj;
	}

	static CGameObject* CreateObject(float x, float y, float degree)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(x, y);
		pObj->SetAngle(degree);

		return pObj;
	}
};


#define __ABSFACTORY_H__
#endif // !__ABSFACTORY_H__
