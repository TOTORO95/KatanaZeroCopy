#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
	
	
	Image* m_Image;
	Image* m_Image2;
	HDC hdc;
	int m_ianim;
	int m_inum;
private:

};
