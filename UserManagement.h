#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h> 

#pragma warning(disable:4996)

/* 최대 저장 가능 유저 수 정의 */
#define User_MAX 500

/* 글자 색상 관련 정의 */
#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define WHITE SetConsoleTextAttribute( col, 0x000f )
#define RED SetConsoleTextAttribute( col, 0x000c )
#define YELGREEN SetConsoleTextAttribute( col, 0x00a )
#define SKY SetConsoleTextAttribute( col, 0x000b )
#define YELLOW SetConsoleTextAttribute( col, 0x000e )
#define GRAY SetConsoleTextAttribute(col, 0x0008);

// 방향키 선언부
#define LEFT   75      // 좌측방향키
#define RIGHT  77      // 우측방향키
#define UP     72      // 위쪽방향키
#define DOWN   80      // 아래방향키
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