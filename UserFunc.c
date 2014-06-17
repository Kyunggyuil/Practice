#include "UserManagement.h"
#include "UserManagement_Func.h"

/* ���������� ����ϴ� �Լ� */

// ������ �ð��� ����ϴ� �Լ�
char* timeToString(struct tm *t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
		);

	return s;
}

int initData(UserInfo userInfo[], FILE* readFile)
{
	int i = 0;
	int count = 0;

	fscanf(readFile, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[count].userId, &userInfo[count].UserName, &userInfo[count].userAddress, &userInfo[count].cellphone); // ù ��° ������ ���� �� �ٽ� �о �������� ����

	for (count = 0; fscanf(readFile, "%d\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[count].userId, &userInfo[count].UserName, &userInfo[count].userAddress, &userInfo[count].cellphone) != EOF; count++);

	return count;
}

int verifyId(int id)
{
	if (id >= 100000 && id <= 999999)
		return 1;
	else
		return 0;
}

int verifyName(char *name)
{
	int idx;

	if (strlen(name) == 0 || strlen(name) > 8)
		return 0;
	
	else
	{
		for (idx = 0 ; idx < strlen(name) ; idx++)
			if (*(name + idx) >= 48 && *(name + idx) <= 57)
				return 0;
	}

	return 1;
}

int verifyPhone(char *phone)
{
	int idx;

	if (strlen(phone) == 0 || strlen(phone) < 12 || strlen(phone) > 13)
		return 0;

	for (idx = 0; idx < strlen(phone); idx++)
	{
		if (*(phone + idx) < '0' || *(phone + idx) > '9')
		{
			if ((idx == 3 || idx == 8) && *(phone + idx) == '-')
				continue;
			else
				return 0;
		}
	}

	return 1;
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}

/* [�ֿ� ���] ��ü ȸ�� ��� ���� */
void mainfunc_List(UserInfo userInfo[], int count){
	int pageNum = 0, ListLine = 0;
	int userViewUnit = 15;
	int finalPage;
	char input;

	struct tm *t;
	time_t timer;

	// finalPage ����
	if (count%userViewUnit == 0){
		finalPage = count / userViewUnit;
	}
	else{
		finalPage = (count / userViewUnit) + 1;
	}

	// ������ �� ���
	for (pageNum = 0; pageNum < finalPage;)
	{
		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

		// ��޴� ��� ��º�
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                         ȸ�� ���� ���α׷� : ��ü ȸ�� ��� ����                         ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;

		if (pageNum < 0)
			pageNum++;

		// ����, ���� ������ ��º�
		printf("	�� ���� (���� ����Ű)		     ");
		printf("[ Page : %d / %d ]", pageNum + 1, finalPage);
		printf("		    (���� ����Ű) ���� ��\n");

		// �޴� ���� ��ܺ�
		YELGREEN;
		printf("	����������������������������������������������������������������������������������������\n");
		printf("	       ��  ��  \t     ��  �� \t\t ��  ��\t\t\t\t   �� �� ó  \n");
		printf("	����������������������������������������������������������������������������������������\n");

		WHITE;
		if (pageNum == 0){
			for (ListLine = 0; ListLine <= userViewUnit; ListLine++)
			{
				if (pageNum * userViewUnit + ListLine >= count)
				{
					break;
				}
				if (pageNum == 0 && ListLine == 0)
					continue;
				if (userInfo[pageNum + userViewUnit + ListLine].userId == 0)
					continue;
				printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[pageNum * userViewUnit + ListLine].userId, userInfo[pageNum * userViewUnit + ListLine].UserName, userInfo[pageNum * userViewUnit + ListLine].userAddress, userInfo[pageNum * userViewUnit + ListLine].cellphone);
			}
		}
		else{
			for (ListLine = 0; ListLine < userViewUnit; ListLine++)
			{
				if (pageNum * userViewUnit + ListLine >= (count - 1))
				{
					break;
				}
				if (userInfo[pageNum + userViewUnit + ListLine].userId == 0)
					continue;
				printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[pageNum * userViewUnit + ListLine + 1].userId, userInfo[pageNum * userViewUnit + ListLine + 1].UserName, userInfo[pageNum * userViewUnit + ListLine + 1].userAddress, userInfo[pageNum * userViewUnit + ListLine + 1].cellphone);
			}
		}

		YELGREEN;
		printf("	����������������������������������������������������������������������������������������\n\n");
		WHITE;
		printf("	�� ���� �������� ���÷��� ESC Ű�� �Է����ּ���. \n");
		printf("	   ����, ���� ���������� �̵��� ���� BackSpaceŰ, EnterŰ�ε� �����մϴ�. ");

		while (1)
		{
			if (_kbhit())
			{
				input = _getch();
				switch (input)
				{
				case LEFT:
					pageNum--;
					system("cls");
					break;
				case RIGHT:
					if (pageNum != (finalPage - 1)) pageNum++; // lastpage
					system("cls");
					break;
				case BACKSPACE:
					pageNum--;
					system("cls");
					break;
				case ENTER:
					if (pageNum != (finalPage - 1)) pageNum++;
					system("cls");
					break;
				case ESC:
					return;
				default:
					break;
				}
				if (input == LEFT || input == RIGHT || input == 8 || input == 13)
				{
					input = 0;
					break;
				}
				else
				{
					input = 0;
					continue;
				}
			}
		}
	}
}

/* [�ֿ� ���] �ű� ȸ�� ����ϱ� */
void mainfunc_Enroll(UserInfo * userInfo, int * count){
	struct tm *t;
	time_t timer;
	UserInfo * TempUser = (UserInfo*)malloc(sizeof(UserInfo));

	char id[10];
	char name[30];
	char address[128];
	char cellphone[20];

	char input;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n      NHN NEXT FITNESS CENTER         ");
	SKY;
	printf("       %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                         ȸ�� ���� ���α׷� : �ű� ȸ�� ����ϱ�                          ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("\n      �� ���ݺ��� ");
	YELGREEN;
	printf("%d�� %d���� �ű� ȸ��", t->tm_year + 1900, t->tm_mon + 1);
	WHITE;
	printf("�� ����մϴ�! (��� ����� : ");
	GRAY;
	printf("Admin");
	WHITE;
	printf(") \n\n");


	printf("          ��������������������������������������������������������������������������\n");
	printf("          ��                                                                      ��\n");
	printf("          ��     �� �й� :                                                        ��\n");
	printf("          ��                                                                      ��\n");
	printf("          ��     �� �̸�(4�� �̳�) :                                              ��\n");
	printf("          ��                                                                      ��\n");
	printf("          ��     �� �ּ�(���� ���� 20�� �̳�) :                               ��\n");
	printf("          ��                                                                      ��\n");
	printf("          ��                                                                      ��\n");
	printf("          ��     �� ��ȭ��ȣ(- ���� 11�� �̳�) :                                  ��\n");
	printf("          ��                                                                      ��\n");
	printf("          ��������������������������������������������������������������������������\n\n");
	printf("");

	printf("   ����������������������������������������������������������������������������������������\n\n");
	printf("     �� �Է� ���� ����� �����ϰ� �ʹٸ�,\n        Ű������ ESC Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�.\n\n\n");

	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
			case 27: // ESC Key
				return;
			default:
				break;
			}
		}
	}
	do{
		gets(name);
	} while (verifyName == 0);
	gets(address);
	do{
		printf("�� ��ȭ��ȣ : ");
		gets(cellphone);
	} while (verifyPhone == 0);
	printf("%s\t%s\t%s\t%s\n", id, name, address, cellphone);

	userInfo[*count].userId = userInfo[*(count - 1)].userId>151000 ? userInfo[*(count - 1)].userId+1:151001;
	strncpy(userInfo[*count].UserName, name, sizeof(name));
	strncpy(userInfo[*count].userAddress, address, sizeof(address));
	strncpy(userInfo[*count].cellphone, cellphone, sizeof(cellphone));
	(*count)++;

	printf("�ű� ��� �Ϸ�\n�ƹ� Ű�� ���� ����ȭ������ ���ÿ�");
	free(TempUser);
	getche();
}

/* [�ֿ� ���] ���� ȸ�� �����ϱ� */
void mainfunc_Delete(UserInfo * userInfo, int * count, int searchResult[], int targetData){
	struct tm *t;
	time_t timer;
	char deleteSelect;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	while (1)
	{
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                         ȸ�� ���� ���α׷� : ���� ȸ�� �����ϱ�                          ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;

		printf("ID\t:\t%d\n�̸�\t:\t%s\n�ּ�\t:\t%s\n��ȭ��ȣ\t:\t%s\n���� �ڷḦ ������ �����Ͻðڽ��ϱ�?", userInfo[searchResult[targetData]].userId, userInfo[searchResult[targetData]].UserName, userInfo[searchResult[targetData]].userAddress, userInfo[searchResult[targetData]].cellphone);
		while (1)
		{
			if (_kbhit())
			{
				deleteSelect = getch();
				switch (deleteSelect)
				{
				case 'y':
				case 'Y':
					userInfo[searchResult[targetData]].userId = 0;
					(*count)--;
					printf("������ �Ϸ� �Ǿ����ϴ�. �ƹ�Ű�� ���� ����Ͻʽÿ�.");
					return;
				case 'n':
				case 'N':
					return;
				default:
					printf("�߸� �����ϼ̽��ϴ�. �ƹ� Ű�� ������ �ٽ� ������ �� �ֽ��ϴ�.");
					getch();
				}
				break;
			}
		}
	}
}

/* [�ֿ� ���] ���� ȸ�� ���� �����ϱ� */
void mainfunc_Modify(UserInfo * userInfo, int * searchResult, int targetData){
	struct tm *t;
	time_t timer;
	int userSelection = 0;
	char name[30];
	char address[128];
	char cellphone[20];

	while (1)
	{
		system("cls");
		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                       ȸ�� ���� ���α׷� : ���� ȸ�� ���� �����ϱ�                       ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;
		printf("������ ������ ����\n1.\t�̸�\n2.\t�ּ�\n3.\t��ȭ��ȣ\n");
		while (1)
		{
			if (_kbhit())
			{
				userSelection = getch();
				if (userSelection<ONE || userSelection>THREE)
				{
					printf("�߸��� �����Դϴ�. �ٽ� �Է��ϱ����ؼ��� �ƹ�Ű�� �����ֽʽÿ�.");
					getch();
					continue;
				}
				else
				{
					switch (userSelection)
					{
					case ONE:
						printf("���� �̸�\t:\t%s\n�ű� �̸�\t:\t", userInfo[searchResult[targetData]].UserName);
						while (1)
						{
							gets(name);
							if (verifyName(name) == 0)
							{
								printf("�߸��� �̸��Դϴ�. �ٽ� �Է��� �ּ���.\n");
								getch();
								continue;
							}
							else
							{
								break;
							}
						}
						strncpy(userInfo[searchResult[targetData]].UserName, name, sizeof(name));
						break;
					case TWO:
						printf("���� �ּ�\t:\t%s\n�ű� �ּ�\t:\t", userInfo[searchResult[targetData]].userAddress);
						gets(address);
						strncpy(userInfo[searchResult[targetData]].userAddress, address, sizeof(address));
						break;
					case THREE:
						printf("���� ��ȭ��ȣ\t:\t%s\n�ű� ��ȭ��ȣ\t:\t", userInfo[searchResult[targetData]].cellphone);
						while (1)
						{
							gets(cellphone);
							if (verifyPhone(cellphone) == 0)
							{
								printf("�߸��� ��ȭ��ȣ �Դϴ�. �ٽ� �Է��� �ּ���.\n");
								getch();
								continue;
							}
							else
							{
								break;
							}
						}
						strncpy(userInfo[searchResult[targetData]].cellphone, cellphone, sizeof(cellphone));
						break;
					}
				}
			}
		}
	}


	getche();
}

/* [�ֿ� ���] ���� ȸ�� �˻��ϱ� */
void mainfunc_Search(UserInfo * userInfo, int * count, int searchResult[]){
	struct tm *t;
	time_t timer;
	int searchSelect;
	int idx;
	char continueSelect=0;
	int resultCount = 0;
	int dataChange=0;
	int dataControlSelect = 0;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	int id;
	char name[30];
	char cellphone[20];

	while (1)
	{
		searchSelect = 0;
		continueSelect = 0;
		resultCount = 0;

		system("cls");
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                         ȸ�� ���� ���α׷� : ���� ȸ�� �˻��ϱ�                          ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;

		printf("\t1.\tid�� �̿��� ã��\n\t2.\t�̸��� �̿��� ã��\n\t3.\t��ȭ��ȣ�� �̿��� ã��\n\tESC.\t���θ޴��� ���ư���\n");
		
		searchSelect = getch();

		switch (searchSelect)
		{
		case ONE: // id�� ã��
			while (1)
			{
				printf("\nID�� �Է��� �ֽʽÿ� : ");
				scanf(" %d", &id);
				if (verifyId(id) == 0) // ��ȿ�� id�� �ƴ� ���
				{
					printf("\n��ȿ���� ���� id�Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return;
							default:
								printf("\n�߸��� �Է��Դϴ�. �ƹ� Ű�� �����ֽʽÿ�.\n");
								getch();
								printf("��ȿ���� ���� id�Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect == 'y'||continueSelect == 'Y');
				}

				else // ��ȿ�� id�� ���
				{
					break;
				}
			}
			
			for (idx = 0; idx < count; idx++)
			{
				if (userInfo[idx].userId == id)
				{
					printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}

			break;
		case TWO:
			while (1)
			{
				printf("\n�̸��� �Է��� �ֽʽÿ� : ");
				gets(name);
				if (verifyName(name) == 0) // ��ȿ�� �̸��� �ƴ� ���
				{
					printf("\n��ȿ���� ���� �̸��Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return (int)NULL;
							default:
								printf("\n�߸��� �Է��Դϴ�. �ƹ� Ű�� �����ֽʽÿ�.\n");
								getch();
								printf("\n��ȿ���� ���� �̸��Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // ��ȿ�� �̸��� ���
				{
					break;
				}
			}

			for (idx = 0; idx < count; idx++)
			{
				if (!strcmp(userInfo[idx].UserName, name))
				{
					printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}
			break;
		case THREE:
			while (1)
			{
				printf("\n��ȭ��ȣ�� �Է��� �ֽʽÿ� : ");
				gets(cellphone);
				if (verifyPhone(cellphone) == 0) // ��ȿ�� ��ȭ��ȣ�� �ƴ� ���
				{
					printf("\n��ȿ���� ���� ��ȭ��ȣ�Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return (int)NULL;
							default:
								printf("�߸��� �Է��Դϴ�. �ƹ� Ű�� �����ֽʽÿ�.\n");
								getch();
								printf("��ȿ���� ���� ��ȭ��ȣ�Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // ��ȿ�� ��ȭ��ȣ�� ���
				{
					break;
				}
			}

			for (idx = 0; idx < count; idx++)
			{
				if (strcmp(userInfo[idx].cellphone, cellphone)==0)
				{
					printf("%d\t:\t	       %-8d\t    %-7s \t %-35s\t%-10s\n", idx+1, userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}

			break;
		case ESC:
			return resultCount;
		default:
			printf("�߸��� �Է��Դϴ�.\n");
			searchSelect = 0;
		}

		if (resultCount == 0)
			printf("��ġ�ϴ� �˻� ����� �����ϴ�. \n");
		else
		{
			printf("�����͸� ���� �Ǵ� �����Ͻ÷��� �ش��Ͻô� ��ȣ�� ���� �����ð� �����Ͻ÷��� 0�� �Է��Ͻø� �˴ϴ� : ");
			while (1)
			{
				if (_kbhit)
				{
					dataChange = getch();

					if (dataChange <= resultCount || dataChange > 0)
					{
						while (1)
						{
							printf("�����͸� �����Ϸ��� 1, �����Ϸ��� 2, �����Ϸ��� 0 : ");
							dataControlSelect = getch();
							if (dataControlSelect == '1')
							{
								mainfunc_Modify(userInfo, searchResult, dataChange);
								break;
							}
							else if (dataControlSelect == '2')
							{
								mainfunc_Delete(userInfo, count, searchResult, dataChange);
								break;
							}
							else if (dataControlSelect == '0')
							{
								break;
							}
							else
							{
								printf("�߸��� �Է��Դϴ�. �ٽ� �ϱ� ���ؼ��� �ƹ�Ű�� �����ø� �˴ϴ�.\n");
								getch();
							}
						}
					}
					else if (dataChange == '0')
						return;
				}
				if (dataChange == '0')
			}
		}

		continueSelect = 0;
		printf("\t�ٽ� �˻��Ͻðڽ��ϱ�?(Y/N)\t:\t");
		fflush(stdin);
		do
		{
			if (_kbhit())
			{
				continueSelect = getch();
				switch (continueSelect)
				{
				case 'y':
				case 'Y':
					continueSelect = 0;
					resultCount = 0;
					dataChange = 0;
					dataControlSelect = 0;
					searchSelect = 0;
					break;
				case 'n':
				case 'N':
					return resultCount;
				default:
					printf("�߸��� �Է��Դϴ�. �ƹ� Ű�� �����ֽʽÿ�.\n");
					getche();
					continueSelect = 0;
				}
			}
		} while (continueSelect == 'y'&&continueSelect == 'Y');
	}

	return resultCount;
}

/* [�ֿ� ���] ���� ���� ���� �� �����ϱ� */
void mainfunc_SaveExit(UserInfo * userInfo, FILE * writeFile, int count){
	struct tm *t;
	time_t timer;
	int idx;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                      ȸ�� ���� ���α׷� : ���� ���� ���� �� �����ϱ�                     ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	fprintf(writeFile, "ȸ�� ���̵�\t�̸�\t�ּ�\t��ȭ��ȣ\n");

	for (idx = 0; idx < count; idx++)
	{
		if (userInfo[idx].userId == 0)
		{
			count++;
			continue;
		}
		fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
	}

	printf("���� �Ϸ�. �ƹ�Ű�� �Է��Ͽ� ���α׷� ����");
	getch();
	return;
}

/* [�ֿ� ���] ������ ���� ���� */
void mainfunc_Info(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                          ȸ�� ���� ���α׷� : ������ ���� ����                           ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		141007 : �谭�� \n");
	printf("		141001 : ����� \n\n		");
	getche();
}