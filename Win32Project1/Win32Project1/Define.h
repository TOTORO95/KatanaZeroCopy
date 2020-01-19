#pragma once
#define PI 3.14159264f


#define WinCX 1280
#define WinCY 800


#define PI 3.141592f
#define GRAVITY 9.8f

#define NULL_CHECK(ptr) if(nullptr == (ptr)) return;
#define NULL_CHECK_RETURN(ptr, val) if(nullptr == (ptr)) return val;

#define DECLARE_SINGLETON(ClassName)	\
public:									\
	static ClassName* GetInstance();	\
	void DestroyInstance();				\
private:								\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()				\
{												\
	if(nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
void ClassName::DestroyInstance()				\
{												\
	if(m_pInstance)								\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}