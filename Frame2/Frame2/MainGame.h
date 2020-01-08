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

private:
	HDC				m_hdc;
	//OBJECT_LIST m_objlist[OBJ_END];
};

#define __MAINGAME_H__
#endif

