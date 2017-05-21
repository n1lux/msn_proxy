#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"


int myString_init(_myString *str, const char *str_recv){
	
	str->buff = (char *)malloc(strlen(str_recv) + 1);
	
	if(str->buff == NULL){
		perror("malloc str->buff");
		exit(1);
	}
	
	strncpy(str->buff, str_recv, strlen(str_recv));	
	str->buff[strlen(str->buff)] = '\0';	

	return 1;
}

int myString_free(_myString *str){
	
	free(str->buff);	
	return 1;
}

int myString_have_content(const _myString *str){
	if(str->buff == NULL)
		return 1;
	else
		return 0;
}

int myString_append(_myString *str, const char *str_recv){
	
		str->buff = (char *)realloc(str->buff, strlen(str->buff) + strlen(str_recv) +1);
		
		if(str->buff == NULL){
			perror("malloc str->buff");
			exit(1);
		}
		
		strncat(str->buff, str_recv, strlen(str_recv));
		str->buff[strlen(str->buff)] = '\0';
				
		return 1;	

}
