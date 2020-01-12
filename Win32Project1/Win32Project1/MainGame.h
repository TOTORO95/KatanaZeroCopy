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
	void GrassAnimate();


public:
	FRAME m_GrassFrame;
	Image* m_Image;
	Image* m_Image2;
	HDC hdc;
	int m_ianim;
	int m_inum;
private:

};

