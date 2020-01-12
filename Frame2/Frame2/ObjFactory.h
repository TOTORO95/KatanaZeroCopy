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
	static CGameObject* CreateObject(OBJ_TYPE objtype, float fMapX, float fMapY)
	{
		CGameObject* pObject = new T(fMapX,fMapY);
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateObject(float x, float y)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(x, y);

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

