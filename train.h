#ifndef TRAIN_H
#define TRAIN_H
#define STR_LEN  30
#define MAX 50



typedef struct train {
	int stationId; //��վ��
	char from[STR_LEN]; //��Ʊ���
	char to[STR_LEN]; //��Ʊ�յ�
	char stime[16];//����ʱ��
	char rtime[16];//����ʱ��
	int money; //Ʊ��
	int ticket;//Ʊ��
}Train;

typedef struct user {
	char name[MAX];//�û����� 
	char id[MAX];//���֤�� 
	char tele_num[MAX];//�û��绰 
	int t_id;//�û��������г��� 
	int order_no;//������� 
}User;

typedef struct node  //�����г��ڵ� 
{
	Train data;
	struct node* next;
}Node, * link;

typedef struct unode	//�����û����� 
{
	User data;
	struct unode* next;
}uNode, * ulink;

void menu();					//�˵���ʾ 
void luru(link l);//�ļ���Ϣ¼�� 
void search_t_to(link l);//���յ�վ��ѯ 
void search_t_id(link l);//���г��Ų�ѯ 
void search_t_from(link l);//������վ��ѯ 
void search(link l);//�г���Ϣ���� 
void save(link l);//�ļ����� 
void orderTicket(link l, ulink u);		//��Ʊ���� 
void returnTicket(link l, ulink u);//��Ʊ���� 
void updateInfo(link l);//�г���Ϣ�޸� 
void Info(Node* p);//�г���Ϣ��ʾ 
void Judge_ticket(Node* p);		//Ʊ���Ǹ��ж� 
void Judge_money(Node* p);		//Ʊ�۷Ǹ��ж� 
void except_id(Node* p, link l);//�г���¼����� 
void except_update_id(Node* p);//�޸��г��Ų��� 
void all_show(link l);//��ѯȫ���û� 
void all_user(ulink u);//�û���Ϣ��ѯ 
void load(link l);//�ļ���������
void uInfo(uNode* p);//�û���Ϣ 
void exitSystem();				//�˳�ϵͳ

#endif