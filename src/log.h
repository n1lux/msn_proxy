/***********************************************************************
 * 						HISTORICO DE ALTERACOES
 * 
 * Obs. Antes de efetuar qualquer alteracao no codigo fazer uma copia de
 * seguranca do arquivo.
 * 
 * [ULTIMAS MODIFICACOES]
 * 21/03/2011 - Criacao do arquivo server.c para separacao das funcoes do 
 * 				servidor. 
 * 
 * *********************************************************************/
#ifndef LOG_H
#define LOG_H

#include "msg.h"

#define log_send "../logs/send.txt"
#define log_recv "../logs/recv.txt"
#define log_struct "../logs/struct_log.txt"
#define log_data "../logs/data_log.txt"

void error(const char *msg);
int write_log(char *msg_rcv, int desks[], int conn, int flag);
int write_log_send(char *msg_rcv);
int write_log_recv(char *msg_rcv);
int write_log_struct(_data_msg *arg);
int write_log_msg(const long int SDGS[], const char *email_to, const char *email_from, const char *body);

#endif
