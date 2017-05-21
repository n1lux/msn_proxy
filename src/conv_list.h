#ifndef CONV_LIST_H
#define CONV_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg.h"
#include "msg_list.h"



typedef struct {
	int id;
	char *email_user_to;
	char *email_user_from;
}_data_users;

struct no_users{	
	_data_users users;
	struct no_users *prox;
};

typedef struct{
	struct no_users *inicio;
	
}userList;

void createList(userList *cl);
int isEmpty(userList cl);
int insertList(userList *cl, const _data_users users);
int removeList(userList *list_users);
void print_list(userList list_users);
int search_users(userList list_users, const _data_users users);
int insert_data_list_online(const _data_msg _msg);
_data_users *create_conversation(const _data_msg _msg_recv);



#endif
