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
	DWORD dwFrameStart; // ��������Ʈ �̹����� x��ǥ
	DWORD dwFrameCount;	// �ִϸ��̼� ��� ������ ����
	DWORD dwFrameY;		// ��������Ʈ �̹����� y��ǥ
	DWORD dwFrameSpeed;	// �ִϸ��̼� ��� �ӵ�
	DWORD dwOldTime;
}FRAME;

#define __STRUCT_H__
#endif
