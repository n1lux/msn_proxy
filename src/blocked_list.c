#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocked_list.h"

void createList_blocked(listWordBlocked *lb){
	
	lb->inicio = NULL;
	
}

int isEmpty_listblocked(listWordBlocked lb){
	if (lb.inicio == NULL)
		return 1;		
	else
		return 0;
}

int insertList_blocked(listWordBlocked *lb, char *word_recv){
	struct no_word_block *aux, *anterior, *atual;
	aux = (struct no_word_block *) malloc(sizeof (struct no_word_block));
	
	if (aux != NULL){	
		aux->_word = (char *)malloc(strlen(word_recv));
		strcpy(aux->_word, word_recv);		
		aux->prox=NULL;
		anterior = NULL;
		atual = lb->inicio;
		
		while(atual != NULL){
			anterior = atual;
			atual = atual->prox;
		}
		if(anterior == NULL){
			aux->prox = lb->inicio;
			lb->inicio = aux;
		}
		else{
			anterior->prox = aux;
			aux->prox = atual;
		}
	}		
	return 1;
}

listWordBlocked *read_data_block(){
	FILE *fp_list_blocked;	
	listWordBlocked *blocked_list;
	char *aux_list_blocked;
	
	blocked_list = (listWordBlocked *)malloc(sizeof(listWordBlocked));
	
	createList_blocked(blocked_list);
	
	if((fp_list_blocked = fopen(path_to_denny, "r")) == NULL){
		perror("fp_list_blocked");
		exit(1);
	}
	
	while(!feof(fp_list_blocked)){
		aux_list_blocked = (char *)malloc(sizeof(char));
		fscanf(fp_list_blocked, "%s", aux_list_blocked);
		if(strlen(aux_list_blocked) > 0)
			insertList_blocked(blocked_list, aux_list_blocked);
	}
	fclose(fp_list_blocked);
	
	return blocked_list;	
	
}	

char *search_for_blocked(const char *string_search){
	listWordBlocked *list_blocked;
	struct no_word_block *aux_list_blocked;
	char *_words_found;
	
	_words_found = (char *)malloc(1024 * sizeof(char));
	
	list_blocked = read_data_block();
	
	aux_list_blocked = (struct no_word_block *)malloc(sizeof(struct no_word_block));
	aux_list_blocked = list_blocked->inicio;
	
	
	while(aux_list_blocked != NULL){
		
		if(search_word_blocked(string_search, aux_list_blocked->_word) == 1){
			if(strlen(_words_found) == 0){
				strcpy(_words_found, aux_list_blocked->_word);
				strcat(_words_found, "-");
			}else{
				strcat(_words_found, aux_list_blocked->_word);
				strcat(_words_found, "-");				
			}
						
		}
		
		aux_list_blocked = aux_list_blocked->prox;
	}
	
	return _words_found;
			
}

int search_word_blocked(const char *_msg_recv, const char *_word_to_search){
	int i=0, j=0, cont=0;
	char word[1024];
	
	while(_msg_recv[i] != '\0'){
		if(_msg_recv[i] == _word_to_search[j]){
			do{
				word[cont] = _msg_recv[i];
				i++;j++;cont++;
				
				if(_msg_recv[i] != _word_to_search[j] && (cont < strlen(_word_to_search))){
					cont=0; j=0;
				}
				
			}while(_msg_recv[i] == _word_to_search[j] && (_word_to_search[j] != '\0'));			
		}
		i++;
	}
	
	if(cont == strlen(_word_to_search))
		return 1;
	else
		return 0;	
}

