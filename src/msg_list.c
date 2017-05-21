#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include "msg_list.h"
#include "blocked_list.h"
#include "print_xml.h"


void createList_conv(msgList *ml, const int _id_list_set){
	ml->id_list = _id_list_set;
	ml->inicio = NULL;
	
}

int isEmpty_listConv(msgList ml){
	if (ml.inicio == NULL)
		return 1;		
	else
		return 0;
}

int insertList_conv(msgList *ml, const _data_msgs_achive msgs){
	struct no_msgs *aux, *anterior, *atual;
	aux = (struct no_msgs *) malloc(sizeof (struct no_msgs));
	
	if (aux != NULL){	
		aux->_msgs = msgs;		
		aux->prox=NULL;
		anterior = NULL;
		atual = ml->inicio;
		
		while(atual != NULL){
			anterior = atual;
			atual = atual->prox;
		}
		if(anterior == NULL){
			aux->prox = ml->inicio;
			ml->inicio = aux;
		}
		else{
			anterior->prox = aux;
			aux->prox = atual;
		}
	}		
	return 1;
}

int search_listMSG(msgList list_users[], const int id_list, int num_list){
	int i;
	
	for(i=0; i<=num_list; i++){
		if(list_users[i].id_list == id_list){
			return list_users[i].id_list;
		}	
	}
	return -1;
}

/* Recebe o id da lista da conversa para saber em qual lista sera inserida e a conversa*/
int insertdata(int id_list_conv, const _data_msg msgs){
	static msgList list_msg[MAX_LIST];	
	static int cont_num_list = 0;
	_data_msgs_achive * _msg_created;	
	int list_to_insert=0;
	int old_conv_to_set;
	
	if(cont_num_list == 0){
		createList_conv(&list_msg[id_list_conv], id_list_conv);
		
		_msg_created = create_msg_to_list(msgs, 1);
		
		insertList_conv(&list_msg[id_list_conv], *_msg_created);
		cont_num_list++;		
	}else{
		
		list_to_insert = search_listMSG(list_msg, id_list_conv, cont_num_list);
				
		if(list_to_insert == -1){
			createList_conv(&list_msg[id_list_conv], id_list_conv);
			cont_num_list++;
			
			_msg_created = create_msg_to_list(msgs, 1);
						
			insertList_conv(&list_msg[id_list_conv], *_msg_created);			
			
		}else{					
			old_conv_to_set= old_conversation_list(list_msg[list_to_insert]);
			_msg_created = create_msg_to_list(msgs, ++old_conv_to_set);
						
			insertList_conv(&list_msg[list_to_insert], *_msg_created);						
		}	
		
	}
	print_list_conv(list_msg, cont_num_list);
	return 0;
}

_data_msgs_achive *create_msg_to_list(const _data_msg msg_recv, int id_to_set){
	
	_data_msgs_achive *_msgs_set_data;
	char *have_word_blocked;
	
	_msgs_set_data = (_data_msgs_achive *)malloc(sizeof(_data_msgs_achive));
	
		if(_msgs_set_data == NULL){
			perror("_msgs_set_data");
			exit(1);
		}
		
		_msgs_set_data->id_conv = id_to_set;
		_msgs_set_data->_user_to = (char *)malloc(strlen(msg_recv.MSG_TO));
		_msgs_set_data->_user_from = (char *)malloc(strlen(msg_recv.MSG_FROM));
		_msgs_set_data->_body = (char *)malloc(strlen(msg_recv.MSG_BODY));
		
		strcpy(_msgs_set_data->_user_to, msg_recv.MSG_TO);
		strcpy(_msgs_set_data->_user_from, msg_recv.MSG_FROM);
		strcpy(_msgs_set_data->_body, msg_recv.MSG_BODY);
		
		have_word_blocked = (char *)malloc(sizeof(char));
		have_word_blocked = search_for_blocked(msg_recv.MSG_BODY);
		
		if(strlen(have_word_blocked) > 0){
			_msgs_set_data->_blocked = (char *)malloc(strlen(have_word_blocked));
			strcpy(_msgs_set_data->_blocked, have_word_blocked);
		}	
		
		return _msgs_set_data;
}

void print_list_conv(msgList list_msgs[], const int list_cont){
		int i;
		
		for(i=1; i<=list_cont; i++){
			print_log(list_msgs[i]);
			
			/*struct no_msgs *aux;
			aux = list_msgs[i].inicio;
			
			printf("\n---------------- ID LIST: %i-----------------", list_msgs[i].id_list);		
			while (aux != NULL){			
				printf("\nID Conv: %i", aux->_msgs.id_conv);
				printf("\nTO: %s", aux->_msgs._user_to);
				printf("\nFROM: %s", aux->_msgs._user_from);
				printf("\nBODY: %s", aux->_msgs._body);							
				aux = aux->prox;		
			}
			printf("\n\n");*/	
		}		
}

int old_conversation_list(msgList list_msgs){
		int old_conv;
		struct no_msgs *aux;
		
		aux = list_msgs.inicio;
		
		while(aux != NULL){
			if(aux->prox == NULL)
				old_conv = aux->_msgs.id_conv;
				
			aux = aux->prox;		
		}		
		
		return old_conv;						
}


