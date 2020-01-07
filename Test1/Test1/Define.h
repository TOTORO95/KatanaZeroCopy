#pragma once
#ifndef __DEFINE_H__

#define PI 3.141592f
#define GRAVITY 9.8f
#define WinCX 880
#define WinCY 600

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


#define __DEFINE_H__
#endif // !__DEFINE_H__