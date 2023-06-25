#ifndef TRAIN_H
#define TRAIN_H
#define STR_LEN  30
#define MAX 50



typedef struct train {
	int stationId; //车站号
	char from[STR_LEN]; //车票起点
	char to[STR_LEN]; //车票终点
	char stime[16];//出发时间
	char rtime[16];//到达时间
	int money; //票价
	int ticket;//票数
}Train;

typedef struct user {
	char name[MAX];//用户姓名 
	char id[MAX];//身份证号 
	char tele_num[MAX];//用户电话 
	int t_id;//用户所购的列车号 
	int order_no;//订单编号 
}User;

typedef struct node  //定义列车节点 
{
	Train data;
	struct node* next;
}Node, * link;

typedef struct unode	//定义用户链表 
{
	User data;
	struct unode* next;
}uNode, * ulink;

void menu();					//菜单显示 
void luru(link l);//文件信息录入 
void search_t_to(link l);//按终点站查询 
void search_t_id(link l);//按列车号查询 
void search_t_from(link l);//按发车站查询 
void search(link l);//列车信息查找 
void save(link l);//文件保存 
void orderTicket(link l, ulink u);		//订票服务 
void returnTicket(link l, ulink u);//退票服务 
void updateInfo(link l);//列车信息修改 
void Info(Node* p);//列车信息显示 
void Judge_ticket(Node* p);		//票数非负判断 
void Judge_money(Node* p);		//票价非负判断 
void except_id(Node* p, link l);//列车号录入查重 
void except_update_id(Node* p);//修改列车号查重 
void all_show(link l);//查询全部用户 
void all_user(ulink u);//用户信息查询 
void load(link l);//文件数据载入
void uInfo(uNode* p);//用户信息 
void exitSystem();				//退出系统

#endif