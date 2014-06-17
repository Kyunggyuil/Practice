/*
	[ 2014�г⵵ 1�б� ] ���α׷��� ���� - �⸻����
	��  �� : ȸ�� ���� ���α׷�
	�ۼ��� : �����, �谭��
	�� ���� ������ : 2014�� 5�� 31�� �����(Ver. 0.1.0.)
*/


/* ��� ���� */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#include "UserManagement.h"
#include "UserManagement_Func.h" // �Լ� ����

// ���� �Լ�
int main(void){

	//���� �����
	int userCount;
	int option;
	int searchResult[User_MAX];
	int searchCount=0;

	UserInfo userInfo[User_MAX];
	FILE *readFile;
	FILE *writeFile;

	struct tm *t;
	time_t timer;

	// �ܼ�â ũ�� ����
	system("mode con lines=32 cols=105");

	// ������ ���� �о����
	readFile = fopen("data.txt", "rt");
	if (readFile == NULL){
		puts("data.txt file error. \n");
		return -1;
	}

	userCount = initData(userInfo, readFile);

	/* ���� ȭ�� �ݺ� */
	while (1){

		/* �ð� ���� ���� */
		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

		/* 0. ���� ������ */
		system("cls");

		// 0-(1) ��ܺ�
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                             ȸ�� ���� ���α׷� (ver. 0.1.0.)                             ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;

		// 0-(2) �޴� ��º�
		printf("		���� �� ����Ͻ� ����� �������ּ���. \n\n");
		printf("		   1. ��ü ȸ�� ��� ���� \n");
		printf("		   2. �ű� ȸ�� ����ϱ� \n");
		printf("		   3. ���� ȸ�� �˻��ϱ� (���� �� ����) \n");
		printf("		   4. ���� ���� ���� �� �����ϱ� \n");
		printf("		   5. ������ ���� ���� \n\n");
		printf("        ����������������������������������������������������������������������������������������\n");


		// 0-(3) �޴� ���ú�

		printf("         �� ���� �Է����� �����ϰ� �̿��Ͻ� �� �ֽ��ϴ�. : ");
		while (1)
		{
			if (_kbhit())
			{
				option = getch(); //�ƽ�Ű �ڵ� ���� ������ ��ȯ 

				switch (option){
				case ONE:
					system("cls");
					mainfunc_List(userInfo, userCount);
					break;
				case TWO:
					system("cls");
					mainfunc_Enroll(userInfo, &userCount);
					break;
				case THREE:
					system("cls");
					mainfunc_Search(userInfo, userCount, searchResult);
					break;
				case FOUR:
					system("cls");
					fclose(readFile);

					writeFile = fopen("data.txt", "wt");
					if (writeFile == NULL){
						puts("data.txt file error. \n");
						return -1;
					}

					mainfunc_SaveExit(userInfo, writeFile, userCount);
					fclose(writeFile);

					return;
				case FIVE:
					system("cls");
					mainfunc_Info();
					break;
				default:
					printf("\n\n	    �߸��� �Է��Դϴ�!");
					printf("\n	    �ƹ� Ű�� �Է��Ͻø� �ٽ� �����Ͻ� �� �ֽ��ϴ�. ");
					getch();
				}
				break;
			}
		}

		// ���� ȭ�� �ݺ� ����
	}

	// file close
	fclose(readFile);
	fclose(writeFile);

	// ���� �Լ�
	return 0;
}