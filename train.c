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


void Judge_ticket(Node* p)		//票数非负判断 
{
	if (p->data.ticket < 0)
	{
		printf("\t票数输入有误，请重新输入： ");
		scanf("%d", &p->data.ticket);
		Judge_ticket(p);
	}
}

void Judge_money(Node* p)		//票价非负判断 
{
	if (p->data.money < 0)
	{
		printf("\t票价输入有误，请重新输入： ");
		scanf("%d", &p->data.money);
		Judge_money(p);
	}
}

void except_id(Node* p, link l)//录入列车号查重 
{
	Node* q;
	q = l;
	while (q != NULL)
	{
		if (p->data.stationId == q->data.stationId)
		{
			printf("\t当前列车班次已存在,请重新输入：");
			scanf("%d", &p->data.stationId);
			except_id(p, l);
		}
		else
			q = q->next;
	}
}

void except_update_id(Node* p)//修改列车号查重 
{
	Node* q;
	q = p->next;
	while (q != NULL)
	{
		if (p->data.stationId == q->data.stationId)
		{
			printf("\t当前列车班次已存在,请重新输入：");
			scanf("%d", &p->data.stationId);
			except_update_id(p);
		}
		else
			q = q->next;
	}
}

void luru(link l)//文件信息录入 
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
		printf("\n\t---------------------------------列车信息录入---------------------------------\n");
		if (!p)
		{
			printf("录入出错！");
			exit(0);
		}
		printf("\n\t1.请输入列车号：");
		scanf("%d", &p->data.stationId);
		except_id(p, l);
		printf("\t2.请输入起点站名称：");
		scanf("%s", &p->data.from);
		printf("\t3.请输入终点站名称：");
		scanf("%s", &p->data.to);
		printf("\t4.请输入列车出发时间(时分格式为00:00)：");
		scanf("%s", &p->data.stime);
		printf("\t5.请输入列车到达时间(时分格式为00:00)：");
		scanf("%s", &p->data.rtime);
		printf("\t6.请输入票价：");
		scanf("%d", &p->data.money);
		Judge_money(p);
		printf("\t7.请输入票数：");
		scanf("%d", &p->data.ticket);
		Judge_ticket(p);
		p->next = NULL;
		q->next = p;
		q = p;
		printf("\t录入成功！\t");
		break;
	}
}

void save(link l)//文件保存 
{
	Node* p;
	FILE* fp;
	p = l->next;
	if ((fp = fopen("train", "wb")) == NULL)
	{
		printf("\t********文件打开失败！*********");
		exit(0);
	}
	else
		printf("\t========文件保存成功！=========");
	while (p)
	{
		fwrite(p, sizeof(Node), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void load(link l)//文件数据载入
{
	Node* p, * r;
	FILE* fp;
	l->next = NULL;
	r = l;
	if ((fp = fopen("train", "rb")) == NULL)
	{
		printf("\n\t********文件打开失败！*********");
	}
	else
	{
		printf("\n\t========文件数据导入成功！=========");
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

void Info(Node* p)//列车信息显示 
{
	printf("\t%5d", p->data.stationId);
	printf("%8s", p->data.from);
	printf("%8s", p->data.to);
	printf("%10s", p->data.stime);
	printf("%15s", p->data.rtime);
	printf("%15d", p->data.money);
	printf("%15d\n", p->data.ticket);
}

void search_t_id(link l)//按列车号查询 
{
	int num_c;
	Node* p;
	p = l;
	printf("请输入您需要查找的列车信息的列车号：");
	scanf("%d", &num_c);
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
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
		printf("\t\t未找到该列车号的信息!\n");
	}
}

void search_t_from(link l)//按发车站查询 
{
	Node* p;
	char pstart[STR_LEN];
	p = l;
	int count = 0;
	printf("请输入您需要查找的列车信息的始发站：");
	scanf("%s", &pstart);
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
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
		printf("\t\t\t.......未找到该列车信息!");
	}
}

void search_t_to(link l)//按终点站查询 
{
	Node* p;
	char preach[STR_LEN];
	p = l->next;
	int count = 0;
	printf("请输入您需要查找的列车信息的终点站：");
	scanf("%s", &preach);
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
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
		printf("\t\t\t.......未找到该列车信息!");
	}
}

void uInfo(uNode* p)//用户信息 
{
	printf("\t%s\t", p->data.id);
	printf("%s\t", p->data.name);
	printf("%s\t\t", p->data.tele_num);
	printf("%d\t", p->data.t_id);
	printf("%d", p->data.order_no);
}

void all_show(link l)//查询全部 
{
	Node* p;
	p = l->next;
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
	if (p == NULL)
	{
		printf("\t\t\t.......未查询到任何列车信息！");
	}
	while (p != NULL)
	{
		Info(p);
		p = p->next;
	}
}

void all_user(ulink u)//用户信息查询 
{
	uNode* p; p = u;
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	if (p == NULL)
	{
		printf("\t\t\t.......未查询到任何列车信息！");
	}
	while (p != NULL)
	{
		uInfo(p);
		p = p->next;
	}
}

void search(link l)//列车信息查找 
{
	int num_cf;
	printf("\n\t---------------------------------列车信息查询---------------------------------\n");
	printf("\t1.按列车号查询\n\t2.按始发站查询\n\t3.按终点站查询\n\t4.查询所有列车信息\n\n");
	printf("\t请输入您的查询方式：");
	scanf("%d", &num_cf);
	printf("\n\t---------------------------------————————-----------------------------\n");
	if (num_cf == 1)
		search_t_id(l);
	else if (num_cf == 2)
		search_t_from(l);
	else if (num_cf == 3)
		search_t_to(l);
	else if (num_cf == 4)
		all_show(l);
	else
		printf("\t\t输入错误！！");
}


void updateInfo(link l)//列车信息修改 
{
	int num;
	int n;
	Node* p;
	p = l;
	if (p == NULL)
	{
		printf("\t**暂时没有可以修改的列车信息**\n");

	}
	else
	{
		printf("请输入需要修改列车信息的列车号：");
		scanf("%d", &num);
		while (p->data.stationId != num)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("找不到该列车信息");
				break;
			}
		}
		if (p != NULL)
		{
			printf("\n\t---------------------------------列车信息修改---------------------------------\n");
			printf("\t1.列车号\n\t2.起始站\n\t3.终点站\n\t4.出发时间\n\t5.到达时间\n\t6.票价\n\t7.票数\n");
			printf("\t---------------------------------——————---------------------------------\n");
			printf("\t请输入您要修改的信息编号：");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
				printf("\t请输入变更后的列车号:");
				scanf("%d", &p->data.stationId);
				except_update_id(p);
				break;
			case 2:
				printf("\t请输入变更后的起始站:");
				scanf("%s", &p->data.from);
				break;
			case 3:
				printf("\t请输入变更后的终点站:");
				scanf("%s", &p->data.to);
				break;
			case 4:
				printf("\t请输入变更后的出发时间(时分格式为00:00)：");
				scanf("%s", &p->data.stime);
				break;
			case 5:
				printf("\t请输入变更后的到达时间(时分格式为00:00)：");
				scanf("%s", &p->data.rtime);
				break;
			case 6:
				printf("\t请输入变更后的票价：");
				scanf("%d", &p->data.money);
				Judge_money(p);
				break;
			case 7:
				printf("\t请输入变更后的票数：");
				scanf("%d", &p->data.ticket);
				Judge_ticket(p);
				break;
			default:
				printf("\t输入错误！");
				system("pause");
			}
			if (n >= 1 && n <= 7)
				printf("\t**修改成功**");
		}
	}
}


void orderTicket(link l, ulink u)		//订票服务 
{
	Node* p;
	uNode* r, * q;
	int n;
	p = l;
	int t_id;
	printf("\n\t---------------------------------火车票订单填写---------------------------------\n");
	printf("\t请输入您需要预订的列车号：");
	scanf("%d", &t_id);
	while (p != NULL && p->data.stationId != t_id)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\t**暂无相关车票可预订!**");
	}
	else
	{
		if (p->data.ticket <= 0)
		{
			printf("\t**该列车车票已经售空**");
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
				printf("\n\t#####请按提示输入您的个人信息#####\n");
				printf("\t请输入您的姓名：");
				scanf("%s", &r->data.name);
				printf("\t请输入您的身份证号码：");
				scanf("%s", &r->data.id);
				printf("\t请输入您的手机号码：");
				scanf("%s", &r->data.tele_num);
				r->data.t_id = t_id;
				p->data.ticket = p->data.ticket - 1;
				srand((int)time(NULL));
				n = rand() % 8999 + 1000;
				r->data.order_no = n;
				printf("\t订票成功，您已成功预订一张列车号为%d的车票,", r->data.t_id);
				printf("订单编号为%d", r->data.order_no);
				r->next = NULL;
				q->next = r;
				q = r;
				break;
			}
		}
	}
}



void returnTicket(link l, ulink u)//退票服务 
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
	printf("\n\t---------------------------------火车票退票界面---------------------------------\n");
	printf("\t请输入您需要退票的列车号：");
	scanf("%d", &input_t_id);
	printf("\t请输入您的身份证号：");
	scanf("%s", &id);
	printf("\t请输入您的订单编号：");
	scanf("%d", &ord);
	while (r != NULL)
	{
		if (strcmp(r->data.id, id) == 0 && input_t_id == r->data.t_id && ord == r->data.order_no)
		{
			printf("\t您当前的订票信息如下：\n");
			printf("\t名字：%s\n", r->data.name);
			printf("\t电话号码为：%s\n", r->data.tele_num);
			printf("\t列车号码为:%d\n", r->data.t_id);
			break;
		}
		else if (r == NULL)
		{
			printf("\t查询不到您的订票信息");
		}
		else
		{
			r = r->next;
		}
	}
	if (r == NULL)
	{
		printf("\t**查询不到您的订票信息**");
	}
	else
	{
		printf("\t您确定要退票吗(Y/N)？");
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
				printf("查询不到该车票信息");
			}
			else
			{
				p->data.ticket += 1;
				q = r;
				r->next = q->next;
				free(r);
			}
			printf("\t**退票成功，感谢使用!**\n");
		}
		else
			printf("\n\t**您已取消退票**");
	}
}

