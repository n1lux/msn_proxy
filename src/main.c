/***********************************************************************
 * 						HISTORICO DE ALTERACOES
 * 
 * Obs. Antes de efetuar qualquer alteracao no codigo fazer uma copia de
 * seguranca do arquivo.
 * 
 * [ULTIMAS MODIFICACOES]
 * 01/03/2011 - Inclusao do cabecalho 
 * 15/03/2011 - Inclusao do flag MSG_NOSIGNAL para correcao da falha 
 * 				BROKENPIPE nas funcoes client_to_proxy e proxy_to_client
 * 15/05/2001 - A programa esta funcionando perfeitamente com gravacao de
 * 				logs.
 * 16/03/2011 - Funcionado conexoes e geracao de log das mensagens
 * 
 * *********************************************************************/
#include "app.h"
#include "server.h"
#include "log.h"
#include "client.h"
#include "mythread.h"

int main (void)
{
	
	int sock_server, sock_proxy, newsockfd;
	int cont_sock = 0, cont_sock_proxy = 0;
	struct sockaddr_in cli_addr;
	socklen_t clilen;	
	_Client *new_client;
	
	clilen = sizeof(cli_addr);
	
	
	/*Cria o socket local*/
	sock_server = create_local_sock();
	system("clear");
	printf("Waiting for connections....\n");
	sleep(1);
			
	while (1){    	
     	
     	if ((new_client = (_Client *)malloc(sizeof(_Client))) == NULL){
     		perror("malloc new_client");
     		exit(1);
     	}
     	
     	if ((newsockfd = accept(sock_server,(struct sockaddr *) &cli_addr, &clilen)) < 0){
			error("ERROR on accept");
			exit(1);
		}
		    	
     	new_client = create_new_client();
     	
     	new_client->fd_sock[0] = newsockfd;
		new_client->port = cli_addr.sin_port;
		new_client->ipaddress = malloc(sizeof(cli_addr.sin_addr));
		strcpy(new_client->ipaddress, inet_ntoa(cli_addr.sin_addr));
     	   	     	
     	//printf("[%s]:[%li]\n", new_client->ipaddress, new_client->port);
     	
     	if ((new_client->port > MIN_RANGE_PORT) && (new_client->port < MAX_RANGE_PORT)){	// VERIFICACAO DO RANGE DE PORTAS DO MSN CLIENTE 
     		cont_sock++;    		
     	
     		if ((sock_proxy = connect_proxy()) == -1){
     			error("ERROr on connect proxy");
     			exit(1);
     		}     		
     		cont_sock_proxy++;
     		
     		new_client->fd_sock[1] = sock_proxy;
     		//printf("[%i] -> [%i]\n", new_client->fd_sock[0], new_client->fd_sock[1]);
     		//printf("[%i] <- [%i]\n", new_client->fd_sock[0], new_client->fd_sock[1]);
     		
     		
     		create_thread(new_client);     		     		     	
     	  		
 		}else{	//FINAL DA VERIFICACAO DO RANGE DE PORTAS DO MSN CLIENTE
 			close(new_client->fd_sock[0]);
 		}
	}     
     
	return 0;
}
