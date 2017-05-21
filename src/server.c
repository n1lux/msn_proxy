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
#include "server.h"
#include "log.h"
#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Cria o socket local */
int create_local_sock(){
	struct sockaddr_in serv_addr;
	int sockfd, portno;
	int optval = 1;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = LOCAL_PORT;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)) < 0) { //SO_REUSEADDR
		fprintf(stderr, "Setsockopt failure\n");
		exit(1);
	}
     
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    	error("ERROR on binding");
     
    listen(sockfd,NUM_BACK);
	
	return (sockfd);
}

/* Conecta ao servidor de proxy */
int connect_proxy(){
	struct sockaddr_in proxy_addr;
	int sockfd_proxy, portno;
	
	sockfd_proxy = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd_proxy < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &proxy_addr, sizeof(proxy_addr));
    portno = PORT_PROXY;
    proxy_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &proxy_addr.sin_addr);
    proxy_addr.sin_port = htons(portno);
    
    if ((connect(sockfd_proxy, (const void *)&proxy_addr, sizeof(proxy_addr))) == -1){
		perror("Connect proxy");
		return -1;
	}
    
    return sockfd_proxy;
}

