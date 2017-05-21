#include "conv_list.h"

void createList(userList *cl){
	cl->inicio = NULL;
	
}

int isEmpty(userList cl){
	if (cl.inicio == NULL)
		return 1;		
	else
		return 0;
}

int insertList(userList *cl, const _data_users users){
	struct no_users *aux, *anterior, *atual;
	aux = (struct no_users *) malloc(sizeof (struct no_users));
	
	if (aux != NULL){	
		aux->users = users;
		
		aux->prox=NULL;
		anterior = NULL;
		atual = cl->inicio;
		
		while(atual != NULL){
			anterior = atual;
			atual = atual->prox;
		}
		if(anterior == NULL){
			aux->prox = cl->inicio;
			cl->inicio = aux;
		}
		else{
			anterior->prox = aux;
			aux->prox = atual;
		}
	}	
	return 1;
}

int search_users(userList list_users, const _data_users users){
	struct no_users *aux;
	
	aux = list_users.inicio;
		
	if(!isEmpty(list_users)){
		while(aux != NULL){
			if(((strcmp(aux->users.email_user_to, users.email_user_to) == 0)&&
				(strcmp(aux->users.email_user_from, users.email_user_from) == 0))|| 
					((strcmp(aux->users.email_user_to, users.email_user_from) == 0)&&
					(strcmp(aux->users.email_user_from, users.email_user_to) == 0))){
					//printf("\nListar: %s [%i]", aux->users.email_user_to, strlen(aux->users.email_user_to));
					//printf("\nNovo: %s [%i]", users.email_user_to, strlen(users.email_user_to));				
				return aux->users.id;			
			}					
			aux = aux->prox;		
		}
	}	
	
	return -1;
}

int insert_data_list_online(const _data_msg _msg){
	static userList list_online;	
	static int get_id_conv;
	static int list_created=0;
	static int _id_conv=0;
	_data_users *conv_created;
	
	if(list_created == 0){
		createList(&list_online);
		conv_created = create_conversation(_msg);
		if(conv_created != NULL){
			conv_created->id = ++_id_conv;
			insertList(&list_online, *conv_created);
			//printf("\n Primeira insercao!!!!!");
			//print_list(list_online);		
			list_created = 1;
			insertdata(conv_created->id, _msg);			
		}	
	}else{		
			conv_created = create_conversation(_msg);
					
			if((get_id_conv = search_users(list_online, *conv_created)) == -1){
				conv_created->id = ++_id_conv;
				insertList(&list_online, *conv_created);
				insertdata(conv_created->id, _msg);
				//printf("\n Insercao nao encontrado na lista!!!!!");
		    	//print_list(list_online);						
				//fflush(stdout);
				//printf("\n OUTRA insercao!!!!!");
				
				//printf("\t\nM TO: %s TAM: [%i]", _msg.MSG_TO, strlen(_msg.MSG_TO));
				//printf("\t\nM FROM: %s TAM [%i]", _msg.MSG_FROM, strlen(_msg.MSG_FROM));
			
				//printf("\t\nL TO: %s TAM: [%i]", users_online->email_user_to, strlen(users_online->email_user_to));
				//printf("\t\nL FROM: %s TAM [%i]", users_online->email_user_from, strlen(users_online->email_user_from));				
							
			}else{
				insertdata(get_id_conv, _msg);
				//printf("\n Vai inserir a mensagem!!!!!");
		    	//print_list(list_online);
				
			}			
			
		}	
	
	return 0;
}

_data_users *create_conversation(const _data_msg _msg_recv){
	_data_users *users_online;
	
	
	users_online = (_data_users *)malloc(sizeof(_data_users));
	
	if(users_online == NULL){
		perror("users_online");
		exit(1);
	}
	
	bzero(users_online, sizeof(users_online));
			
	users_online->email_user_to = (char *)malloc(strlen(_msg_recv.MSG_TO));
	users_online->email_user_from = (char *)malloc(strlen(_msg_recv.MSG_FROM));		
	
	strcpy(users_online->email_user_to, _msg_recv.MSG_TO);
	strcpy(users_online->email_user_from, _msg_recv.MSG_FROM);
	
	return users_online;
}

void print_list(userList list_users){
	struct no_users *aux;
	
		aux = list_users.inicio;
		system("clear");
		printf("\n--------------------[LISTA ONLINE]----------------------------");
		while (aux != NULL){			
			printf("\nID: %i", aux->users.id);
			printf("\nTO: %s", aux->users.email_user_to);
			printf("\nFROM: %s", aux->users.email_user_from);			
			aux = aux->prox;		
		}
		printf("\n--------------------[FIM DA LISTA ONLINE]----------------------");
	
}
