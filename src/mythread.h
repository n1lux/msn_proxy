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
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pthread.h>
#include "client.h"
#include "app.h"
#include "log.h"
//#include "msglist.h"
#include "msg.h"

int *client_to_proxy(void *arg);
int *proxy_to_client(void *arg);
int create_thread(_Client *conns);

#endif
