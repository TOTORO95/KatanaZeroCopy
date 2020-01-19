#pragma once
#ifndef __OBJ_FACTORY_H__
template <typename T>
class CObjFactory
{
public:

	static CGameObject* CreateObject()
	{
		CGameObject* pObject = new T;
		pObject->Initialize();

		return pObject;
	}
	static CGameObject* CreateObject(float x, float y)
	{
		CGameObject* pObject = new T(x,y);
		pObject->Initialize();
		//pObject->SetPos(x, y);

		return pObject;
	}
	static CGameObject* CreateObject(float x, float y, MONSTER_TYPE eMonster_Type)
	{
		CGameObject* pObject = new T(eMonster_Type,x, y);
		pObject->Initialize();
		//pObject->SetPos(x, y);

		return pObject;
	}
	static CGameObject* CreateObject(float x, float y, int option)
	{
		CGameObject* pObject = new T(x,y,option);
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateObject(float x, float y, float degree)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(x, y);
		pObject->SetAngle(degree);

		return pObject;
	}

	static CGameObject* CreateObject(float x, float y, const wstring& wstrImageKey)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(x, y);
		pObject->SetImageKey(wstrImageKey);

		return pObject;
	}


};


#define __OBJ_FACTORY_H__
#endif // !__OBJ_FACTORY_H__

