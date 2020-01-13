#pragma once
#ifndef __FUNCTION_H__

template <typename T>
void SafeDelete(T _t)
{
	if (_t == nullptr)
		return;

	delete _t;
	_t = nullptr;
}



#define __FUNCTION_H__
#endif // !__FUNCTION_H__
