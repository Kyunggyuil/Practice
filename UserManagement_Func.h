/* 함수(주요 기능) 선언부 */
void mainfunc_List(UserInfo userInfo[], int count); // 전체 회원 명단 보기
void mainfunc_Enroll(UserInfo * userInfo, int * count); // 신규 회원 등록하기
void mainfunc_Delete(UserInfo * userInfo, int * count, int searchResult[], int targetData); // 기존 회원 삭제하기
void mainfunc_Modify(UserInfo * userInfo, int * searchResult, int targetData); // 기존 회원 정보 수정하기
void mainfunc_Search(UserInfo * userInfo, int * count, int searchResult[]); // 기존 회원 검색하기
void mainfunc_SaveExit(UserInfo * userInfo, FILE * writeFile, int count); // 변경 내용 저장 및 종료하기
void mainfunc_Info(void); // 개발자 정보 보기

// 함수(세부 기능) 선언부
char* timeToString(struct tm *t);
int initData(UserInfo userInfo[], FILE* fp);
void setUserInfo(char *buffer, UserInfo *userInfo);