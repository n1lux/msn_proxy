#ifndef MYSTRING_H
#define MYSTRING_H


typedef struct{	
	char *buff;
}_myString;

int myString_init(_myString *str, const char *str_recv);
int myString_free(_myString *str);
int myString_have_content(const _myString *str);
int myString_append(_myString *str, const char *str_recv);

#endif
