#pragma once

#ifndef __STRUCT_H__

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;
}INFO;

typedef struct tagLinePoint
{
	float	fX;
	float	fY;
}LINE_POS;

typedef struct tagLineInfo
{
	LINE_POS	tStart;
	LINE_POS	tEnd;
}LINE_INFO;

typedef struct tagMouseInfo
{
	bool	bStart;
	POINT	ptStart;
	POINT	ptEnd;
}MOUSE_INFO;

typedef struct tagFrame
{
	DWORD dwFrameStart; // 스프라이트 이미지의 x좌표
	DWORD dwFrameCount;	// 애니메이션 재생 프레임 개수
	DWORD dwFrameY;		// 스프라이트 이미지의 y좌표
	DWORD dwFrameSpeed;	// 애니메이션 재생 속도
	DWORD dwOldTime;
}FRAME;

#define __STRUCT_H__
#endif
