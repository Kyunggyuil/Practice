/* �Լ�(�ֿ� ���) ����� */
void mainfunc_List(UserInfo userInfo[], int count); // ��ü ȸ�� ��� ����
void mainfunc_Enroll(UserInfo * userInfo, int * count); // �ű� ȸ�� ����ϱ�
void mainfunc_Delete(UserInfo * userInfo, int * count, int searchResult[], int targetData); // ���� ȸ�� �����ϱ�
void mainfunc_Modify(UserInfo * userInfo, int * searchResult, int targetData); // ���� ȸ�� ���� �����ϱ�
void mainfunc_Search(UserInfo * userInfo, int * count, int searchResult[]); // ���� ȸ�� �˻��ϱ�
void mainfunc_SaveExit(UserInfo * userInfo, FILE * writeFile, int count); // ���� ���� ���� �� �����ϱ�
void mainfunc_Info(void); // ������ ���� ����

// �Լ�(���� ���) �����
char* timeToString(struct tm *t);
int initData(UserInfo userInfo[], FILE* fp);
void setUserInfo(char *buffer, UserInfo *userInfo);