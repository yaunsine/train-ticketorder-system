#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"
#include"train.h"


void menu()    //�˵����� 
{
	printf("\n\t---------------------------------��ӭ�����𳵶�Ʊϵͳ---------------------------------\n");
	printf("\n\t*********************************\n");
	printf("\t\t1.¼���г���Ϣ\n\t\t2.��ѯ�г����\n\t\t3.�޸��г���Ϣ\n\t\t4.��Ʊ����\n\t\t5.��Ʊ����\n\t\t6.������¼�����Ϣ\n\t\t7.��ȡ���е��г���Ϣ\n\t\t8.�˳�ϵͳ");
	printf("\n\t*********************************\n\t");
	printf("��������Ҫִ�еĹ���(0-8)��");
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
		system("title �𳵶�Ʊϵͳ@yaunsine");
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



