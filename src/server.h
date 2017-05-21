/***********************************************************************
 * 						HISTORICO DE ALTERACOES
 * 
 * Obs. Antes de efetuar qualquer alteracao no codigo fazer uma copia de
 * seguranca do arquivo.
 * 
 * [ULTIMAS MODIFICACOES]
 * 21/03/2011 - Criacao do arquivo server.h para as definicoes do arquivo
 * 				server.c
 * 
 * *********************************************************************/
#ifndef SERVER_H
#define SERVER_H


#define LOCAL_PORT 5122
#define PORT_PROXY 3128
#define SERVER_PROXY_ADDR 127.0.0.1
#define NUM_BACK	100

int create_local_sock();
int connect_proxy();


#endif
