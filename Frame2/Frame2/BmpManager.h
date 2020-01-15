#pragma once
class CMyBmp;


class CBmpManager
{
public:
	static CBmpManager* GetInstance();
	void DestroyInstance();
private:
	static CBmpManager* m_pInstance;
public:
	CBmpManager();
	~CBmpManager();
public:
	HDC GetMemDC(const wstring& wstrImgKey) const;
	HBITMAP GetBMP(const wstring& wstrImgKey);

public:
	void LoadBmp(const wstring& wstrImgKey, const wstring& wstrFilePath);
	void LoadBmp(const wstring& wstrImgKey, const wstring& wstrFilePath, bool IsRot);

private:
	void Release();

private:
	map<wstring, CMyBmp*>	m_mapBmp;

};

