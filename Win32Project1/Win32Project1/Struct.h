#pragma once
#ifndef __STRUCT_H__



typedef struct tagFrame
{
	DWORD dwFrameStart; // ��������Ʈ �̹����� x��ǥ
	DWORD dwFrameCount;	// �ִϸ��̼� ��� ������ ����
	DWORD dwFrameX;
	DWORD dwFrameY;		// ��������Ʈ �̹����� y��ǥ
	DWORD dwFrameSpeed;	// �ִϸ��̼� ��� �ӵ�
	DWORD dwOldTime;
}FRAME;

#define __STRUCT_H__
#endif // !__STRUCT_H__
