#ifndef BLOCKED_LIST__H
#define BLOCKED_LIST__H

#define path_to_denny "../conf/denny.dad"

struct no_word_block{	
	char *_word;
	struct no_word_block *prox;
};

typedef struct{
	struct no_word_block *inicio;	
}listWordBlocked;

void createList_blocked(listWordBlocked *lb);
int isEmpty_listblocked(listWordBlocked lb);
int insertList_blocked(listWordBlocked *lb, char *word_recv);
listWordBlocked *read_data_block();
char *search_for_blocked(const char *string_search);
int search_word_blocked(const char *_msg_recv, const char *_word_to_search);



#endif
