#pragma once
#ifndef __STRUCT_H__


typedef struct Info
{
	float fPosX, fPosY;
	float fCX, fCY;
}INFO;
typedef struct TagArea
{
	bool bStart;
	POINT ptStart;
	POINT ptEnd;
}TagArea;

#define __STRUCT_H__
#endif // !__STRUCT_H__
