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
	int startPos;
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

phone_data* ReadAndMakeData(char buffer[41])
{
	phone_data* temp_data = (phone_data*)malloc(sizeof(phone_data));
	temp_data->name[0] = '\0';
	temp_data->phone1[0] = '\0';
	temp_data->phone2[0] = '\0';
	temp_data->memo[0] = '\0';
	int i = 0, start = 0, select = 0;
	for (select = 0; buffer[i] != '\0' && buffer[i] != '\n'; select++) //�� ���� �о�´�
	{
		for (start = 0; buffer[i] != ':' && buffer[i] != '\n'&&buffer[i] !='\0';) //�ݷб��� �д´�.
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
		switch (select)
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
	/*char* ptr = strtok(buffer, ":");
	while(ptr != NULL)
	{
		switch(start++)
		{
		case 0:
			strcpy(temp_data->name, ptr);
			break;
		case 1:
			strcpy(temp_data->phone1, ptr);
			break;
		case 2:
			strcpy(temp_data->phone2, ptr);
			break;
		case 3:
			strcpy(temp_data->memo, ptr);
			break;
		}
		ptr = strtok(NULL, ":");
	}*/
	return temp_data;
}

void InitList()
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
	list.head->startPos = 0;
	list.tail->rear = 0;
}

void Free()
{
	phone_data* ptr = list.head;
	while(ptr->rear != NULL)
	{
		ptr = ptr->rear;
		free(ptr->front);
	}
	fclose(fp);
}

//���� ����Ʈ.
void InsertList(phone_data* data)
{
	phone_data* ptr = list.head;
	while(ptr->rear != NULL)
	{
		if(ptr->rear->name[0] == '\0' || strcmp(ptr->rear->name,data->name)>0)
		{
			data->front = ptr;
			data->rear = ptr->rear;
			ptr->rear->front = data;
			ptr->rear = data;
			data->startPos = data->front->startPos
				+ strlen(data->front->name)
				+ strlen(data->front->phone1)
				+ strlen(data->front->phone2)
				+ strlen(data->front->memo);
			break;
		}
		ptr = ptr->rear;
	}
}

void PrintList()
{
	phone_data* ptr = list.head->rear;
	while(ptr->rear != NULL)
	{
		printf("%s %s %s %s\n", ptr->name,ptr->phone1,ptr->phone2,ptr->memo);
		ptr = ptr->rear;
	}
}

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

void CheckAndPrintList(char *str)
{
	phone_data* ptr = list.head->rear;
	int count = 0, isPrint = 0;
	while(ptr->rear != NULL)
	{
		int find = 0;
		if(strstr(ptr->name,str) != NULL)
		{
			find = 1;
		}
		if (strstr( ptr->phone1,str) != NULL)
		{
			find = 1;
		}
		if (strstr( ptr->phone2,str) != NULL)
		{
			find = 1;
		}
		if (strstr( ptr->memo,str) != NULL)
		{
			find = 1;
		}
		if(find)
		{
			isPrint = 1;
			printf("%d : %s %s %s %s\n",++count, ptr->name, ptr->phone1, ptr->phone2, ptr->memo);
		}
		ptr = ptr->rear;
	}
	if(isPrint)
	{
		printf("match found.\n");
	}
	else
	{
		printf("no match found.\n");
	}
}

void AddNumber(int cnt, char *data[])
{
	//ToDo ���� �д°� ���� �� �Ǵµ� ����ó������ ������ ���� 
	char isAdd;
	for(int i=0;i<cnt;i++)
	{
		printf("%s ", data[i]);
	}
	printf("\n");
	printf("add? [Y/N]: ");
	scanf("%c", &isAdd);

	if(isAdd == 'Y')
	{
		char* copyData = (char*)malloc(sizeof(char) * 61);
		int index = 0;

		for(index = 0; index<4;index++)
		{
			switch (index)
			{
			case 0:
				strcpy(copyData, data[index]); //�̸�
				strcat(copyData, ":");
				break;
			case 1:
				strcat(copyData, data[index]); //��ȭ��ȣ
				strcat(copyData, ":");
				if (cnt == 2) //�̸��̶� ��ȭ��ȣ �ۿ� ���ٴ� �̾߱�
				{
					strcat(copyData, ":\n");
					index = 4;
				}
				break;
			case 2:
				if (cnt == 3) //�޸� �ִٴ� �̾߱�
				{
					strcat(copyData, ":");
					strcat(copyData, data[index]);
					strcat(copyData, "\n");
					index = 4;
				}
				else //2��° ��ȭ��ȣ�� �ִٴ� �̾߱�.
				{
					strcat(copyData, data[index]);
					strcat(copyData, ":");
				}
				break;
			case 3: //��� ������ �ϼ�
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

void DeleteList(const char* deleteData)
{
	int start = 1;
	int cnt = 0;
	int sel;
	phone_data* ptr = list.head->rear;
	phone_data* vector = (phone_data*)malloc(sizeof(phone_data) * list.size);
	while(ptr->rear != NULL)
	{
		int find = 0;
		if(strstr(ptr->name,deleteData)!=NULL)
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
	printf("which one? ");
	scanf("%d", &sel);
	if(sel<0 && sel < cnt)
	{
		fseek(fp, (long)vector[sel].startPos, SEEK_SET);
		fputc()
		//�� ������ �ű� ���� �ش� ���ڿ� ó������ �����͸� �ű�.
	}
}

void CheckOption(int argc,char *argv[])
{
	if(argc > 1 &&argv[1][0] == '?') //�����쿡���� ?�� �޴� �� ����.
	{
		switch(argv[1][1])
		{
		case 'a':
			AddNumber(argc-2,argv + 2);
			break;
		case 'd':
			break;
		case 'l':
			PrintList();
			break;
		default :
			assert(0, "Call default : in CheckOption function");
		}
	}
	else //�ɼ��� ���� �ʾ��� �� ã��.
	{
		CheckAndPrintList(argv[1]);
	}
}

int main(int argc,char *argv[])
{
	
	InitList();
	ReadFilesAndMakeList();
	CheckOption(argc,argv);

	Free();
	return 0;
}