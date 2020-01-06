#pragma once
#ifndef __MAINGAME_H__

class CGameObject;

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Render();
	
private:
	void Release();
	HDC				m_hdc;
	Obj_pList		m_ObjpList[OBJ_END];
	float timecount;


};



#define __MAINGAME_H__
#endif // !__MAINGAME_H__
