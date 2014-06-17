#include "UserManagement.h"
#include "UserManagement_Func.h"

/* 공통적으로 사용하는 함수 */

// 현재의 시간을 계산하는 함수
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

	fscanf(readFile, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[count].userId, &userInfo[count].UserName, &userInfo[count].userAddress, &userInfo[count].cellphone); // 첫 번째 데이터 읽은 뒤 다시 읽어서 지워버릴 것임

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

/* [주요 기능] 전체 회원 명단 보기 */
void mainfunc_List(UserInfo userInfo[], int count){
	int pageNum = 0, ListLine = 0;
	int userViewUnit = 15;
	int finalPage;
	char input;

	struct tm *t;
	time_t timer;

	// finalPage 정의
	if (count%userViewUnit == 0){
		finalPage = count / userViewUnit;
	}
	else{
		finalPage = (count / userViewUnit) + 1;
	}

	// 페이지 별 출력
	for (pageNum = 0; pageNum < finalPage;)
	{
		timer = time(NULL);    // 현재 시각을 초 단위로 얻기
		t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

		// 대메뉴 상단 출력부
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ┌─────────────────────────────────────────────┐\n");
		printf("     │                         회원 관리 프로그램 : 전체 회원 명단 보기                         │\n");
		printf("     └─────────────────────────────────────────────┘\n\n");
		WHITE;

		if (pageNum < 0)
			pageNum++;

		// 이전, 다음 페이지 출력부
		printf("	◀ 이전 (좌측 방향키)		     ");
		printf("[ Page : %d / %d ]", pageNum + 1, finalPage);
		printf("		    (우측 방향키) 다음 ▶\n");

		// 메뉴 메인 상단부
		YELGREEN;
		printf("	────────────────────────────────────────────\n");
		printf("	       학  번  \t     이  름 \t\t 주  소\t\t\t\t   연 락 처  \n");
		printf("	────────────────────────────────────────────\n");

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
		printf("	────────────────────────────────────────────\n\n");
		WHITE;
		printf("	※ 메인 페이지로 가시려면 ESC 키를 입력해주세요. \n");
		printf("	   이전, 다음 페이지로의 이동은 각각 BackSpace키, Enter키로도 가능합니다. ");

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

/* [주요 기능] 신규 회원 등록하기 */
void mainfunc_Enroll(UserInfo * userInfo, int * count){
	struct tm *t;
	time_t timer;
	UserInfo * TempUser = (UserInfo*)malloc(sizeof(UserInfo));

	char id[10];
	char name[30];
	char address[128];
	char cellphone[20];

	char input;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	RED;
	printf("\n      NHN NEXT FITNESS CENTER         ");
	SKY;
	printf("       %s\n", timeToString(t));
	YELLOW;
	printf("     ┌─────────────────────────────────────────────┐\n");
	printf("     │                         회원 관리 프로그램 : 신규 회원 등록하기                          │\n");
	printf("     └─────────────────────────────────────────────┘\n\n");
	WHITE;

	printf("\n      ▶ 지금부터 ");
	YELGREEN;
	printf("%d년 %d월의 신규 회원", t->tm_year + 1900, t->tm_mon + 1);
	WHITE;
	printf("을 등록합니다! (등록 담당자 : ");
	GRAY;
	printf("Admin");
	WHITE;
	printf(") \n\n");


	printf("          ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┃     ◈ 학번 :                                                        ┃\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┃     ◈ 이름(4자 이내) :                                              ┃\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┃     ◈ 주소(띄어쓰기 포함 20자 이내) :                               ┃\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┃     ◈ 전화번호(- 포함 11자 이내) :                                  ┃\n");
	printf("          ┃                                                                      ┃\n");
	printf("          ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
	printf("");

	printf("   ────────────────────────────────────────────\n\n");
	printf("     ※ 입력 도중 등록을 중지하고 싶다면,\n        키보드의 ESC 키를 입력하시면 메인 화면으로 돌아갑니다.\n\n\n");

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
		printf("◈ 전화번호 : ");
		gets(cellphone);
	} while (verifyPhone == 0);
	printf("%s\t%s\t%s\t%s\n", id, name, address, cellphone);

	userInfo[*count].userId = userInfo[*(count - 1)].userId>151000 ? userInfo[*(count - 1)].userId+1:151001;
	strncpy(userInfo[*count].UserName, name, sizeof(name));
	strncpy(userInfo[*count].userAddress, address, sizeof(address));
	strncpy(userInfo[*count].cellphone, cellphone, sizeof(cellphone));
	(*count)++;

	printf("신규 등록 완료\n아무 키나 눌러 메인화면으로 가시오");
	free(TempUser);
	getche();
}

/* [주요 기능] 기존 회원 삭제하기 */
void mainfunc_Delete(UserInfo * userInfo, int * count, int searchResult[], int targetData){
	struct tm *t;
	time_t timer;
	char deleteSelect;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	while (1)
	{
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ┌─────────────────────────────────────────────┐\n");
		printf("     │                         회원 관리 프로그램 : 기존 회원 삭제하기                          │\n");
		printf("     └─────────────────────────────────────────────┘\n\n");
		WHITE;

		printf("ID\t:\t%d\n이름\t:\t%s\n주소\t:\t%s\n전화번호\t:\t%s\n위의 자료를 정말로 삭제하시겠습니까?", userInfo[searchResult[targetData]].userId, userInfo[searchResult[targetData]].UserName, userInfo[searchResult[targetData]].userAddress, userInfo[searchResult[targetData]].cellphone);
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
					printf("삭제가 완료 되었습니다. 아무키나 눌러 계속하십시오.");
					return;
				case 'n':
				case 'N':
					return;
				default:
					printf("잘못 선택하셨습니다. 아무 키나 눌러서 다시 시작할 수 있습니다.");
					getch();
				}
				break;
			}
		}
	}
}

/* [주요 기능] 기존 회원 정보 수정하기 */
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
		timer = time(NULL);    // 현재 시각을 초 단위로 얻기
		t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ┌─────────────────────────────────────────────┐\n");
		printf("     │                       회원 관리 프로그램 : 기존 회원 정보 수정하기                       │\n");
		printf("     └─────────────────────────────────────────────┘\n\n");
		WHITE;
		printf("수정할 데이터 선택\n1.\t이름\n2.\t주소\n3.\t전화번호\n");
		while (1)
		{
			if (_kbhit())
			{
				userSelection = getch();
				if (userSelection<ONE || userSelection>THREE)
				{
					printf("잘못된 선택입니다. 다시 입력하기위해서는 아무키나 눌러주십시오.");
					getch();
					continue;
				}
				else
				{
					switch (userSelection)
					{
					case ONE:
						printf("기존 이름\t:\t%s\n신규 이름\t:\t", userInfo[searchResult[targetData]].UserName);
						while (1)
						{
							gets(name);
							if (verifyName(name) == 0)
							{
								printf("잘못된 이름입니다. 다시 입력해 주세요.\n");
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
						printf("기존 주소\t:\t%s\n신규 주소\t:\t", userInfo[searchResult[targetData]].userAddress);
						gets(address);
						strncpy(userInfo[searchResult[targetData]].userAddress, address, sizeof(address));
						break;
					case THREE:
						printf("기존 전화번호\t:\t%s\n신규 전화번호\t:\t", userInfo[searchResult[targetData]].cellphone);
						while (1)
						{
							gets(cellphone);
							if (verifyPhone(cellphone) == 0)
							{
								printf("잘못된 전화번호 입니다. 다시 입력해 주세요.\n");
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

/* [주요 기능] 기존 회원 검색하기 */
void mainfunc_Search(UserInfo * userInfo, int * count, int searchResult[]){
	struct tm *t;
	time_t timer;
	int searchSelect;
	int idx;
	char continueSelect=0;
	int resultCount = 0;
	int dataChange=0;
	int dataControlSelect = 0;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

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
		printf("     ┌─────────────────────────────────────────────┐\n");
		printf("     │                         회원 관리 프로그램 : 기존 회원 검색하기                          │\n");
		printf("     └─────────────────────────────────────────────┘\n\n");
		WHITE;

		printf("\t1.\tid를 이용해 찾기\n\t2.\t이름을 이용해 찾기\n\t3.\t전화번호를 이용해 찾기\n\tESC.\t메인메뉴로 돌아가기\n");
		
		searchSelect = getch();

		switch (searchSelect)
		{
		case ONE: // id로 찾기
			while (1)
			{
				printf("\nID를 입력해 주십시오 : ");
				scanf(" %d", &id);
				if (verifyId(id) == 0) // 유효한 id가 아닌 경우
				{
					printf("\n유효하지 않은 id입니다. 다시 입력하시겠습니까?(Y/N) : ");
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
								printf("\n잘못된 입력입니다. 아무 키나 눌러주십시오.\n");
								getch();
								printf("유효하지 않은 id입니다. 다시 입력하시겠습니까?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect == 'y'||continueSelect == 'Y');
				}

				else // 유효한 id인 경우
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
				printf("\n이름을 입력해 주십시오 : ");
				gets(name);
				if (verifyName(name) == 0) // 유효한 이름이 아닌 경우
				{
					printf("\n유효하지 않은 이름입니다. 다시 입력하시겠습니까?(Y/N) : ");
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
								printf("\n잘못된 입력입니다. 아무 키나 눌러주십시오.\n");
								getch();
								printf("\n유효하지 않은 이름입니다. 다시 입력하시겠습니까?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // 유효한 이름인 경우
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
				printf("\n전화번호를 입력해 주십시오 : ");
				gets(cellphone);
				if (verifyPhone(cellphone) == 0) // 유효한 전화번호가 아닌 경우
				{
					printf("\n유효하지 않은 전화번호입니다. 다시 입력하시겠습니까?(Y/N) : ");
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
								printf("잘못된 입력입니다. 아무 키나 눌러주십시오.\n");
								getch();
								printf("유효하지 않은 전화번호입니다. 다시 입력하시겠습니까?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // 유효한 전화번호인 경우
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
			printf("잘못된 입력입니다.\n");
			searchSelect = 0;
		}

		if (resultCount == 0)
			printf("일치하는 검색 결과가 없습니다. \n");
		else
		{
			printf("데이터를 수정 또는 삭제하시려면 해당하시는 번호를 하지 않으시고 종료하시려면 0을 입력하시면 됩니다 : ");
			while (1)
			{
				if (_kbhit)
				{
					dataChange = getch();

					if (dataChange <= resultCount || dataChange > 0)
					{
						while (1)
						{
							printf("데이터를 수정하려면 1, 삭제하려면 2, 종료하려면 0 : ");
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
								printf("잘못된 입력입니다. 다시 하기 위해서는 아무키나 눌르시면 됩니다.\n");
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
		printf("\t다시 검색하시겠습니까?(Y/N)\t:\t");
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
					printf("잘못된 입력입니다. 아무 키나 눌러주십시오.\n");
					getche();
					continueSelect = 0;
				}
			}
		} while (continueSelect == 'y'&&continueSelect == 'Y');
	}

	return resultCount;
}

/* [주요 기능] 변경 내용 저장 및 종료하기 */
void mainfunc_SaveExit(UserInfo * userInfo, FILE * writeFile, int count){
	struct tm *t;
	time_t timer;
	int idx;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ┌─────────────────────────────────────────────┐\n");
	printf("     │                      회원 관리 프로그램 : 변경 내용 저장 및 종료하기                     │\n");
	printf("     └─────────────────────────────────────────────┘\n\n");
	WHITE;

	fprintf(writeFile, "회원 아이디\t이름\t주소\t전화번호\n");

	for (idx = 0; idx < count; idx++)
	{
		if (userInfo[idx].userId == 0)
		{
			count++;
			continue;
		}
		fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
	}

	printf("저장 완료. 아무키나 입력하여 프로그램 종료");
	getch();
	return;
}

/* [주요 기능] 개발자 정보 보기 */
void mainfunc_Info(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ┌─────────────────────────────────────────────┐\n");
	printf("     │                          회원 관리 프로그램 : 개발자 정보 보기                           │\n");
	printf("     └─────────────────────────────────────────────┘\n\n");
	WHITE;

	printf("		141007 : 김강원 \n");
	printf("		141001 : 경규일 \n\n		");
	getche();
}