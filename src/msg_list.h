#ifndef MSG_LIST__H
#define MSG_LIST__H
#include "msg.h"


#define MAX_LIST 100


typedef struct {
	int id_conv;
	char *_user_to;
	char *_user_from;
	long int date;
	char *_body;
	char *_blocked;
}_data_msgs_achive;

struct no_msgs{	
	_data_msgs_achive _msgs;
	struct no_msgs *prox;
};

typedef struct{
	int id_list;
	struct no_msgs *inicio;	
}msgList;

int insertdata(int id_list_conv, const _data_msg msgs);
void createList_conv(msgList *ml, const int _id_list_set);
int isEmpty_listConv(msgList ml);
int insertList_conv(msgList *ml, const _data_msgs_achive msgs);
//int removeList_conv(msgList *list_msgs);
void print_list_conv(msgList list_msgs[], const int list_cont);
int search_listMSG(msgList list_users[], const int id_list, int num_list);
_data_msgs_achive *create_msg_to_list(const _data_msg msg_recv, int id_to_set);
int old_conversation_list(msgList list_msgs);
int print_log(msgList list_to_log);


#endif
