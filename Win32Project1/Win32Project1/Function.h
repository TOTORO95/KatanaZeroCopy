#pragma once

template <typename T>
void SafeDelete(T t)
{
	if (t != nullptr)
		delete t;
	t = nullptr;
}