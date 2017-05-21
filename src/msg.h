#ifndef MSG_H
#define MSG_H

#include "app.h"


#define TOKEN_SDG_MSNP21 "SDG"
#define TOKEN_TO_MSNP21 "To:"
#define TOKEN_FROM_MSNP21 "From:"
#define TOKEN_CONTLENGTH_MSNP21 "Content-Length:"
#define TOKEN_MSG_TYPE_MSNP21 "Message-Type: Text"
#define TOKEN_PREMSG "X-MMS-IM-Format:"

typedef struct {
	long int SDG_1, SDG_2, MSG_LENGTH;
	char *MSG_TO, *MSG_FROM;
	char *MSG_BODY;
}_data_msg;

char *clean_email_to(const char *email);
char *clean_email_from(const char *email);
char *get_email_to_array(char *buffer_recv);
char *get_email_from_array(char *buffer_recv);
char *get_body_array(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_body, int line_buffer_recv);
int search_token(const char *_msg_recv, const char *_TOKEN_MSNP21);
//void _get_data_buffer_send(const char *_MSG);
//void _get_data_buffer_recv(const char *_MSG);
void _get_data_buffer(const char *_MSG);
void print_buffer_array(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_buffer);
int make_buffer_to_struct(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_buffer);
long int *get_num_sdg_array(const char *buffer_recv);
int set_struct(const long int sdg0_set, const long int sdg1_set, const char *emailto_set, const char *emailfrom_set, const char *body_set);
long int get_content_length(const char *buffer_recv);

#endif
