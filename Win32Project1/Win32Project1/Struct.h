#pragma once
#ifndef __STRUCT_H__



typedef struct tagFrame
{
	DWORD dwFrameStart; // 스프라이트 이미지의 x좌표
	DWORD dwFrameCount;	// 애니메이션 재생 프레임 개수
	DWORD dwFrameX;
	DWORD dwFrameY;		// 스프라이트 이미지의 y좌표
	DWORD dwFrameSpeed;	// 애니메이션 재생 속도
	DWORD dwOldTime;
}FRAME;

#define __STRUCT_H__
#endif // !__STRUCT_H__
