#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct phone_data
{
	char name[30];
	char phone1[20];
	char phone2[20];
	char memo[40];
	int lineNumber;
	struct phone_data* front;
	struct phone_data* rear;
}phone_data;

typedef struct array_list
{
	phone_data* head;
	phone_data* tail;
	int size;
}array_list;

array_list list;
FILE* fp;

phone_data* ReadAndMakeData(const char buffer[41])
{
	phone_data* temp_data = (phone_data*)malloc(sizeof(phone_data));//함수 안에서 동적할당하는 습관은 좋지 않으나.. 끝나고 free에서 해제.
	static int line = 0; //이 함수 안에서는 전역변수로 써야 함. linked list는 ordered 상태이므로 원래 txt에서 몇번째 라인인지.
	temp_data->name[0] = '\0';
	temp_data->phone1[0] = '\0';
	temp_data->phone2[0] = '\0';
	temp_data->memo[0] = '\0';
	int i = 0, start = 0, select = 0;
	for (select = 0; buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != EOF; select++) //어느 데이터에 저장할지.
	{
		for (start = 0; buffer[i] != ':' && buffer[i] != '\n' && buffer[i] != '\0' && buffer[i] != EOF;) //token 파씽.
		{
			switch (select)
			{
			case 0:
				temp_data->name[start++] = buffer[i++];
				break;
			case 1:
				temp_data->phone1[start++] = buffer[i++];
				break;
			case 2:
				temp_data->phone2[start++] = buffer[i++];
				break;
			case 3:
				temp_data->memo[start++] = buffer[i++];
				break;
			default:
				assert(0, "fail copy");
			}
		}
		switch (select) //문자열 마지막은 null을 넣어줘야 함.
		{
		case 0:
			temp_data->name[start] = '\0';
			break;
		case 1:
			temp_data->phone1[start] = '\0';
			break;
		case 2:
			temp_data->phone2[start] = '\0';
			break;
		case 3:
			temp_data->memo[start] = '\0';
			break;
		default:
			assert(0, "fail null add");
		}
		i++;
	}

	temp_data->lineNumber = line++; //본인이 몇번째 라인인지 저장.
	return temp_data;
}

void InitList() //doubly linked list
{
	list.tail = (phone_data*)malloc(sizeof(phone_data));
	list.head = (phone_data*)malloc(sizeof(phone_data));
	list.head->name[0] = '\0';
	list.tail->name[0] = '\0';
	list.head->rear = list.tail;
	list.head->front = NULL;
	list.tail->rear = NULL;
	list.tail->front = list.head;
	list.size = 0;
	list.tail->rear = 0;
}

void Free()
{
	phone_data* ptr = list.head;
	while (ptr->rear != NULL)
	{
		ptr = ptr->rear;
		free(ptr->front);
	}
	if (!fp) //del option이 정상적으로 작동했을 때 fclose는 중복됨.
	{
		fclose(fp);
	}
}

//삽입 복잡도가 O(N)이지만.. 정렬된 상태를 유지.
void InsertList(phone_data* data)
{
	phone_data* ptr = list.head;
	while (ptr->rear != NULL)
	{
		if (ptr->rear->name[0] == '\0' || strcmp(ptr->rear->name, data->name) > 0)
		{
			data->front = ptr;
			data->rear = ptr->rear;
			ptr->rear->front = data;
			ptr->rear = data;
			break;
		}
		ptr = ptr->rear;
	}
}

void PrintList()
{
	phone_data* ptr = list.head->rear;
	while (ptr->rear != NULL)
	{
		printf("%s %s %s %s\n", ptr->name, ptr->phone1, ptr->phone2, ptr->memo);
		ptr = ptr->rear;
	}
}

//파일을 읽고 doubly linked list를 만들어주는 함수
void ReadFilesAndMakeList()
{
	fp = fopen("data.txt", "r+");
	if (fp == NULL)
	{
		assert(0, "Can't open file");
	}
	char buffer[41];
	int index = 0;
	while (fgets(buffer, 100, fp))
	{
		InsertList(ReadAndMakeData(buffer));
		list.size++;
	}
}

//문자열 있는지 확인하고 출력해줌.
void CheckAndPrintList(char* str)
{
	phone_data* ptr = list.head->rear;
	int count = 0, isPrint = 0;
	while (ptr->rear != NULL)
	{
		int find = 0;
		if (strstr(ptr->name, str) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->phone1, str) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->phone2, str) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->memo, str) != NULL)
		{
			find = 1;
		}
		if (find)
		{
			isPrint = 1;
			printf("%d : %s %s %s %s\n", ++count, ptr->name, ptr->phone1, ptr->phone2, ptr->memo);
		}
		ptr = ptr->rear;
	}
	if (isPrint)
	{
		printf("match found.\n");
	}
	else
	{
		printf("no match found.\n");
	}
}

//새로 데이터 파일을 만들 때.
//cnt는 token의 갯수이다.
void AddNumber(const int cnt, char* data[])
{
	//ToDo 
	char isAdd;
	for (int i = 0; i < cnt; i++)
	{
		printf("%s ", data[i]);
	}
	printf("\n");
	printf("add? [Y/N]: ");
	scanf("%c", &isAdd);

	if (isAdd == 'Y')
	{
		char* copyData = (char*)malloc(sizeof(char) * 61); //RAII
		int index = 0;

		//strtok를 쓰려고 했으나.. :: <- 이상태에서 따로 처리하는 것이 아닌 한꺼번에 처리하는 거 같아 그냥 구현함.
		for (index = 0; index < 4; index++)
		{
			switch (index)
			{
			case 0:
				strcpy(copyData, data[index]);
				strcat(copyData, ":");
				break;
			case 1:
				strcat(copyData, data[index]);
				strcat(copyData, ":");
				if (cnt == 2)
				{
					strcat(copyData, ":\n");
					index = 4;
				}
				break;
			case 2:
				if (cnt == 3) // ::2개 있는 상황
				{
					strcat(copyData, ":");
					strcat(copyData, data[index]);
					strcat(copyData, "\n");
					index = 4;
				}
				else
				{
					strcat(copyData, data[index]);
					strcat(copyData, ":");
				}
				break;
			case 3: //다 있는 상황
				strcat(copyData, data[index]);
				strcat(copyData, "\n");
				break;
			default:
				assert(0, "error : in AddNumber Function!");
			}
		}

		fputs(copyData, fp);
		free(copyData);
	}
}

//fwrite로 문자를 대체하려 했으나.. 파일이 깨져 새로 만들어서 대체하는 방식을 채택.
void MakeNewDataTxtFile(const int deleteLine)
{
	FILE* newFp = fopen("replace.txt", "w");
	int temp = 0;

	rewind(fp);
	char ch = getc(fp);
	while (ch != EOF)
	{
		if (temp != deleteLine) //해당하는 라인이 아니면 파일에 쓰기
		{
			putc(ch, newFp);
		}
		if (ch == '\n')
		{
			temp++;
		}
		ch = getc(fp);
	}
	fclose(newFp);
	fclose(fp); //중복 free 생각!
	//remove 함수는 fclose()를 하지 않거나, 현재 사용중이면 작동하지 않고 -1을 리턴한다.
	remove("data.txt");
	rename("replace.txt", "data.txt");
	remove("replace.txt");
}

void DeleteList(const char* deleteData)
{
	int start = 1;
	int cnt = 0;
	int sel;
	phone_data* ptr = list.head->rear;
	// 부합하는 list를 뽑기 위한 것.배열처럼 쓰기 위함.
	// 들어오는 데이터를 예측하기 힘들기 때문에 어쩔수없이 동적할당.
	phone_data* vector = (phone_data*)malloc(sizeof(phone_data) * list.size);
	while (ptr->rear != NULL)
	{
		int find = 0;
		if (strstr(ptr->name, deleteData) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->phone1, deleteData) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->phone2, deleteData) != NULL)
		{
			find = 1;
		}
		if (strstr(ptr->memo, deleteData) != NULL)
		{
			find = 1;
		}
		if (find)
		{
			printf("%d %s %s %s %s\n", start++, ptr->name, ptr->phone1, ptr->phone2, ptr->memo);
			vector[cnt++] = *ptr;
		}
		ptr = ptr->rear;
	}
	if (cnt > 0)
	{
		printf("which one? ");
		scanf("%d", &sel);
		if (sel > 0 && sel <= cnt)
		{
			MakeNewDataTxtFile(vector[sel - 1].lineNumber);
		}
	}
	free(vector);
}

void CheckOption(int argc, char* argv[])
{
	if (argc > 1 && argv[1][0] == '-')
	{
		switch (argv[1][1])
		{
		case 'a':
			AddNumber(argc - 2, argv + 2); //앞에 쓸대없는 부분 제거, 그리고 포인터 증감연산을 함으로써 필요한 string만 취함.
			break;
		case 'd':
			DeleteList(argv[2]);
			break;
		case 'l':
			PrintList();
			break;
		default:
			assert(0, "Call default : in CheckOption function");
		}
	}
	else
	{
		CheckAndPrintList(argv[1]);
	}
}

int main(int argc, char* argv[])
{
	InitList();
	ReadFilesAndMakeList();
	CheckOption(argc, argv);

	Free();

	return 0;
}