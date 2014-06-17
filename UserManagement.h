#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h> 

#pragma warning(disable:4996)

/* �ִ� ���� ���� ���� �� ���� */
#define User_MAX 500

/* ���� ���� ���� ���� */
#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define WHITE SetConsoleTextAttribute( col, 0x000f )
#define RED SetConsoleTextAttribute( col, 0x000c )
#define YELGREEN SetConsoleTextAttribute( col, 0x00a )
#define SKY SetConsoleTextAttribute( col, 0x000b )
#define YELLOW SetConsoleTextAttribute( col, 0x000e )
#define GRAY SetConsoleTextAttribute(col, 0x0008);

// ����Ű �����
#define LEFT   75      // ��������Ű
#define RIGHT  77      // ��������Ű
#define UP     72      // ���ʹ���Ű
#define DOWN   80      // �Ʒ�����Ű
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define SIX 54
#define SEVEN 55

typedef struct userInfo{
	int userId;
	char UserName[30];
	char userAddress[128];
	char cellphone[30];
}UserInfo;

int initData(UserInfo userInfo[], FILE* fp);

#endif