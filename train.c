/*
	@author: yaunsine
	@date: 2018-12-07
*/
#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"
#include"train.h"


void Judge_ticket(Node* p)		//Ʊ���Ǹ��ж� 
{
	if (p->data.ticket < 0)
	{
		printf("\tƱ�������������������룺 ");
		scanf("%d", &p->data.ticket);
		Judge_ticket(p);
	}
}

void Judge_money(Node* p)		//Ʊ�۷Ǹ��ж� 
{
	if (p->data.money < 0)
	{
		printf("\tƱ�������������������룺 ");
		scanf("%d", &p->data.money);
		Judge_money(p);
	}
}

void except_id(Node* p, link l)//¼���г��Ų��� 
{
	Node* q;
	q = l;
	while (q != NULL)
	{
		if (p->data.stationId == q->data.stationId)
		{
			printf("\t��ǰ�г�����Ѵ���,���������룺");
			scanf("%d", &p->data.stationId);
			except_id(p, l);
		}
		else
			q = q->next;
	}
}

void except_update_id(Node* p)//�޸��г��Ų��� 
{
	Node* q;
	q = p->next;
	while (q != NULL)
	{
		if (p->data.stationId == q->data.stationId)
		{
			printf("\t��ǰ�г�����Ѵ���,���������룺");
			scanf("%d", &p->data.stationId);
			except_update_id(p);
		}
		else
			q = q->next;
	}
}

void luru(link l)//�ļ���Ϣ¼�� 
{
	Node* p, * q;
	while (1)
	{
		q = l;
		while (q->next != NULL)
		{
			q = q->next;
		}
		p = (Node*)malloc(sizeof(Node));
		printf("\n\t---------------------------------�г���Ϣ¼��---------------------------------\n");
		if (!p)
		{
			printf("¼�����");
			exit(0);
		}
		printf("\n\t1.�������г��ţ�");
		scanf("%d", &p->data.stationId);
		except_id(p, l);
		printf("\t2.���������վ���ƣ�");
		scanf("%s", &p->data.from);
		printf("\t3.�������յ�վ���ƣ�");
		scanf("%s", &p->data.to);
		printf("\t4.�������г�����ʱ��(ʱ�ָ�ʽΪ00:00)��");
		scanf("%s", &p->data.stime);
		printf("\t5.�������г�����ʱ��(ʱ�ָ�ʽΪ00:00)��");
		scanf("%s", &p->data.rtime);
		printf("\t6.������Ʊ�ۣ�");
		scanf("%d", &p->data.money);
		Judge_money(p);
		printf("\t7.������Ʊ����");
		scanf("%d", &p->data.ticket);
		Judge_ticket(p);
		p->next = NULL;
		q->next = p;
		q = p;
		printf("\t¼��ɹ���\t");
		break;
	}
}

void save(link l)//�ļ����� 
{
	Node* p;
	FILE* fp;
	p = l->next;
	if ((fp = fopen("train", "wb")) == NULL)
	{
		printf("\t********�ļ���ʧ�ܣ�*********");
		exit(0);
	}
	else
		printf("\t========�ļ�����ɹ���=========");
	while (p)
	{
		fwrite(p, sizeof(Node), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void load(link l)//�ļ���������
{
	Node* p, * r;
	FILE* fp;
	l->next = NULL;
	r = l;
	if ((fp = fopen("train", "rb")) == NULL)
	{
		printf("\n\t********�ļ���ʧ�ܣ�*********");
	}
	else
	{
		printf("\n\t========�ļ����ݵ���ɹ���=========");
		while (!feof(fp))
		{
			p = (Node*)malloc(sizeof(Node));
			if (fread(p, sizeof(Node), 1, fp) != 1)
				break;
			else
			{
				p->next = NULL;
				r->next = p;
				r = p;
			}
		}
	}
}

void Info(Node* p)//�г���Ϣ��ʾ 
{
	printf("\t%5d", p->data.stationId);
	printf("%8s", p->data.from);
	printf("%8s", p->data.to);
	printf("%10s", p->data.stime);
	printf("%15s", p->data.rtime);
	printf("%15d", p->data.money);
	printf("%15d\n", p->data.ticket);
}

void search_t_id(link l)//���г��Ų�ѯ 
{
	int num_c;
	Node* p;
	p = l;
	printf("����������Ҫ���ҵ��г���Ϣ���г��ţ�");
	scanf("%d", &num_c);
	printf("\n\t\t\t\t******-----��ѯ���-----******\n");
	printf("\t�г���\t����վ\t����վ\t����ʱ��\t����ʱ��\tƱ��(Ԫ)\tƱ�����ţ�\n");
	while (p)
	{
		if (p->data.stationId == num_c)
		{
			Info(p);
			break;
		}
		p = p->next;
	}
	if (!p)
	{
		printf("\t\tδ�ҵ����г��ŵ���Ϣ!\n");
	}
}

void search_t_from(link l)//������վ��ѯ 
{
	Node* p;
	char pstart[STR_LEN];
	p = l;
	int count = 0;
	printf("����������Ҫ���ҵ��г���Ϣ��ʼ��վ��");
	scanf("%s", &pstart);
	printf("\n\t\t\t\t******-----��ѯ���-----******\n");
	printf("\t�г���\t����վ\t����վ\t����ʱ��\t����ʱ��\tƱ��(Ԫ)\tƱ�����ţ�\n");
	while (p)
	{
		if (strcmp(p->data.from, pstart) == 0)
		{
			Info(p);
			count++;
			if (p->next == NULL)
				break;
			else
				p = p->next;
		}
		if (p->next != NULL)
			p = p->next;
		else
			break;
	}
	if (p == NULL || count == 0)
	{
		printf("\t\t\t.......δ�ҵ����г���Ϣ!");
	}
}

void search_t_to(link l)//���յ�վ��ѯ 
{
	Node* p;
	char preach[STR_LEN];
	p = l->next;
	int count = 0;
	printf("����������Ҫ���ҵ��г���Ϣ���յ�վ��");
	scanf("%s", &preach);
	printf("\n\t\t\t\t******-----��ѯ���-----******\n");
	printf("\t�г���\t����վ\t����վ\t����ʱ��\t����ʱ��\tƱ��(Ԫ)\tƱ�����ţ�\n");
	while (p)
	{
		if (strcmp(p->data.to, preach) == 0)
		{
			Info(p);
			count++;
		}
		if (p->next == NULL)
			break;
		else
			p = p->next;
	}
	if (!p || count == 0)
	{
		printf("\t\t\t.......δ�ҵ����г���Ϣ!");
	}
}

void uInfo(uNode* p)//�û���Ϣ 
{
	printf("\t%s\t", p->data.id);
	printf("%s\t", p->data.name);
	printf("%s\t\t", p->data.tele_num);
	printf("%d\t", p->data.t_id);
	printf("%d", p->data.order_no);
}

void all_show(link l)//��ѯȫ�� 
{
	Node* p;
	p = l->next;
	printf("\n\t\t\t\t******-----��ѯ���-----******\n");
	printf("\t�г���\t����վ\t����վ\t����ʱ��\t����ʱ��\tƱ��(Ԫ)\tƱ�����ţ�\n");
	if (p == NULL)
	{
		printf("\t\t\t.......δ��ѯ���κ��г���Ϣ��");
	}
	while (p != NULL)
	{
		Info(p);
		p = p->next;
	}
}

void all_user(ulink u)//�û���Ϣ��ѯ 
{
	uNode* p; p = u;
	printf("\n\t\t\t\t******-----��ѯ���-----******\n");
	if (p == NULL)
	{
		printf("\t\t\t.......δ��ѯ���κ��г���Ϣ��");
	}
	while (p != NULL)
	{
		uInfo(p);
		p = p->next;
	}
}

void search(link l)//�г���Ϣ���� 
{
	int num_cf;
	printf("\n\t---------------------------------�г���Ϣ��ѯ---------------------------------\n");
	printf("\t1.���г��Ų�ѯ\n\t2.��ʼ��վ��ѯ\n\t3.���յ�վ��ѯ\n\t4.��ѯ�����г���Ϣ\n\n");
	printf("\t���������Ĳ�ѯ��ʽ��");
	scanf("%d", &num_cf);
	printf("\n\t---------------------------------����������������-----------------------------\n");
	if (num_cf == 1)
		search_t_id(l);
	else if (num_cf == 2)
		search_t_from(l);
	else if (num_cf == 3)
		search_t_to(l);
	else if (num_cf == 4)
		all_show(l);
	else
		printf("\t\t������󣡣�");
}


void updateInfo(link l)//�г���Ϣ�޸� 
{
	int num;
	int n;
	Node* p;
	p = l;
	if (p == NULL)
	{
		printf("\t**��ʱû�п����޸ĵ��г���Ϣ**\n");

	}
	else
	{
		printf("��������Ҫ�޸��г���Ϣ���г��ţ�");
		scanf("%d", &num);
		while (p->data.stationId != num)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("�Ҳ������г���Ϣ");
				break;
			}
		}
		if (p != NULL)
		{
			printf("\n\t---------------------------------�г���Ϣ�޸�---------------------------------\n");
			printf("\t1.�г���\n\t2.��ʼվ\n\t3.�յ�վ\n\t4.����ʱ��\n\t5.����ʱ��\n\t6.Ʊ��\n\t7.Ʊ��\n");
			printf("\t---------------------------------������������---------------------------------\n");
			printf("\t��������Ҫ�޸ĵ���Ϣ��ţ�");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
				printf("\t������������г���:");
				scanf("%d", &p->data.stationId);
				except_update_id(p);
				break;
			case 2:
				printf("\t�������������ʼվ:");
				scanf("%s", &p->data.from);
				break;
			case 3:
				printf("\t������������յ�վ:");
				scanf("%s", &p->data.to);
				break;
			case 4:
				printf("\t����������ĳ���ʱ��(ʱ�ָ�ʽΪ00:00)��");
				scanf("%s", &p->data.stime);
				break;
			case 5:
				printf("\t����������ĵ���ʱ��(ʱ�ָ�ʽΪ00:00)��");
				scanf("%s", &p->data.rtime);
				break;
			case 6:
				printf("\t�����������Ʊ�ۣ�");
				scanf("%d", &p->data.money);
				Judge_money(p);
				break;
			case 7:
				printf("\t�����������Ʊ����");
				scanf("%d", &p->data.ticket);
				Judge_ticket(p);
				break;
			default:
				printf("\t�������");
				system("pause");
			}
			if (n >= 1 && n <= 7)
				printf("\t**�޸ĳɹ�**");
		}
	}
}


void orderTicket(link l, ulink u)		//��Ʊ���� 
{
	Node* p;
	uNode* r, * q;
	int n;
	p = l;
	int t_id;
	printf("\n\t---------------------------------��Ʊ������д---------------------------------\n");
	printf("\t����������ҪԤ�����г��ţ�");
	scanf("%d", &t_id);
	while (p != NULL && p->data.stationId != t_id)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\t**������س�Ʊ��Ԥ��!**");
	}
	else
	{
		if (p->data.ticket <= 0)
		{
			printf("\t**���г���Ʊ�Ѿ��ۿ�**");
		}
		else
		{
			while (1)
			{
				q = u;
				while (q->next != NULL)
				{
					q = q->next;
				}
				r = (uNode*)malloc(sizeof(uNode));
				printf("\n\t#####�밴��ʾ�������ĸ�����Ϣ#####\n");
				printf("\t����������������");
				scanf("%s", &r->data.name);
				printf("\t�������������֤���룺");
				scanf("%s", &r->data.id);
				printf("\t�����������ֻ����룺");
				scanf("%s", &r->data.tele_num);
				r->data.t_id = t_id;
				p->data.ticket = p->data.ticket - 1;
				srand((int)time(NULL));
				n = rand() % 8999 + 1000;
				r->data.order_no = n;
				printf("\t��Ʊ�ɹ������ѳɹ�Ԥ��һ���г���Ϊ%d�ĳ�Ʊ,", r->data.t_id);
				printf("�������Ϊ%d", r->data.order_no);
				r->next = NULL;
				q->next = r;
				q = r;
				break;
			}
		}
	}
}



void returnTicket(link l, ulink u)//��Ʊ���� 
{
	Node* p;
	uNode* q, * r;
	char id[MAX];
	int ord;
	q = (uNode*)malloc(sizeof(uNode));
	p = l;
	r = u;
	char s;
	int input_t_id;
	printf("\n\t---------------------------------��Ʊ��Ʊ����---------------------------------\n");
	printf("\t����������Ҫ��Ʊ���г��ţ�");
	scanf("%d", &input_t_id);
	printf("\t�������������֤�ţ�");
	scanf("%s", &id);
	printf("\t���������Ķ�����ţ�");
	scanf("%d", &ord);
	while (r != NULL)
	{
		if (strcmp(r->data.id, id) == 0 && input_t_id == r->data.t_id && ord == r->data.order_no)
		{
			printf("\t����ǰ�Ķ�Ʊ��Ϣ���£�\n");
			printf("\t���֣�%s\n", r->data.name);
			printf("\t�绰����Ϊ��%s\n", r->data.tele_num);
			printf("\t�г�����Ϊ:%d\n", r->data.t_id);
			break;
		}
		else if (r == NULL)
		{
			printf("\t��ѯ�������Ķ�Ʊ��Ϣ");
		}
		else
		{
			r = r->next;
		}
	}
	if (r == NULL)
	{
		printf("\t**��ѯ�������Ķ�Ʊ��Ϣ**");
	}
	else
	{
		printf("\t��ȷ��Ҫ��Ʊ��(Y/N)��");
		fflush(stdin);
		scanf("%c", &s);
		if (s == 'y' || s == 'Y')
		{
			while (p != NULL && p->data.stationId != input_t_id)
			{
				p = p->next;
			}
			if (p == NULL)
			{
				printf("��ѯ�����ó�Ʊ��Ϣ");
			}
			else
			{
				p->data.ticket += 1;
				q = r;
				r->next = q->next;
				free(r);
			}
			printf("\t**��Ʊ�ɹ�����лʹ��!**\n");
		}
		else
			printf("\n\t**����ȡ����Ʊ**");
	}
}

