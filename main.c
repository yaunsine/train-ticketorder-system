#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"
#include"train.h"


void menu()    //菜单函数 
{
	printf("\n\t---------------------------------欢迎来到火车订票系统---------------------------------\n");
	printf("\n\t*********************************\n");
	printf("\t\t1.录入列车信息\n\t\t2.查询列车情况\n\t\t3.修改列车信息\n\t\t4.订票服务\n\t\t5.退票服务\n\t\t6.保存已录入的信息\n\t\t7.读取已有的列车信息\n\t\t8.退出系统");
	printf("\n\t*********************************\n\t");
	printf("输入您所要执行的功能(0-8)：");
}


int main()
{
	link l;
	int num_f;
	ulink u;
	l = (Node*)malloc(sizeof(Node));
	u = (uNode*)malloc(sizeof(uNode));
	l->next = NULL;
	u->next = NULL;
	do
	{
		//system("date 2018/12/07");
		system("title 火车订票系统@yaunsine");
		system("color F4");
		menu();
		scanf("%d", &num_f);
		system("cls");
		switch (num_f)
		{
		case 1:
			luru(l); break;
		case 2:
			search(l); break;
		case 3:
			updateInfo(l); break;
		case 4:
			orderTicket(l, u); break;
		case 5:
			returnTicket(l, u); break;
		case 6:
			save(l); break;
		case 7:
			load(l); break;
		case 8:
			exit(0); break;
			/*case 9:
				all_user(u);break;*/
		default:
			continue;
		}
	} while (1);
	return 0;
}



