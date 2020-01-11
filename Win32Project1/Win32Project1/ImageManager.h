#pragma once
class CMyImage;
class CImageManager
{
public:
	static	CImageManager* GetInstance();
	void DestroyInstance();
private:
	static CImageManager* m_pInstance;

public:
	CImageManager();
	~CImageManager();

public:
	HDC GetMemDC(const wstring& wstrImgKey) const;

public:
	void LoadBmp(const wstring& wstrImgKey, const wstring& wstrFilePath);

private:
	void Release();

private:
	map<wstring, CMyImage*>	m_mapImg;


};

