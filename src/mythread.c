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

#include "mythread.h"
#include "msg.h"

int *client_to_proxy(void *arg){
	char *buffer;
    int tam;
    int fd_client = (*(_Client*)arg).fd_sock[0]; // Descritor do socket local
    int fd_proxy = (*(_Client*)arg).fd_sock[1];   // Descritor do socket remoto
	//printf("Thread number %ld\n", pthread_self());
	
	
	if((buffer = (char*)malloc(sizeof(char) * TAM_BUFFER)) == NULL){
		 error("ERROR malloc c -> p");
		 exit(1);
	}
	
	while(1){
    	memset(buffer, 0x0, sizeof(char) * TAM_BUFFER);
    	
        tam = recv(fd_client, buffer, TAM_BUFFER, 0);         
        //printf("\n> > > %s", buffer);
        //printf("[%i]", strlen(buffer));
        if(tam == 0){
			shutdown(fd_client, 0);
			shutdown(fd_proxy, 1);
			pthread_exit((void *)pthread_self());
		}else if(tam > 0){
        	//write_log(buffer, ((_Client *)arg)->fd_sock, (*(_Client*)arg).num_con, 0);        
        	
        	//write_log_send(buffer);
        	if(search_token(buffer, TOKEN_MSG_TYPE_MSNP21) == 1)
        		_get_data_buffer(buffer);
        		//printf("\n%s", buffer);
        		
        	send(fd_proxy, buffer, tam, MSG_NOSIGNAL);
        	
        }
    }
}

int *proxy_to_client(void *arg){
	char *buffer;
    size_t tam;
	int fd_client = ((_Client *)arg)->fd_sock[0]; // Descritor para o socket local
    int fd_proxy = ((_Client *)arg)->fd_sock[1];   // Descritor para o socket remoto
    
	
	
    //printf("Thread number %ld\n", pthread_self());
    
    if((buffer = (char*)malloc(sizeof(char) * TAM_BUFFER)) == NULL){
		 error("ERROR malloc p -> c");
		 exit(1);
	}
	
	      
    while(1){
		memset(buffer,0x0,sizeof(char) * TAM_BUFFER);
		
		tam = recv(fd_proxy, buffer, TAM_BUFFER, 0);
						
        //printf("\n< < < %s", buffer);
        //printf("[%i]", strlen(buffer));
        if(tam == 0){
			shutdown(fd_client, 1);
			shutdown(fd_proxy, 0);
			pthread_exit((void *)pthread_self());
		}else if(tam > 0){
        	//write_log (buffer, ((_Client *)arg)->fd_sock, (*(_Client*)arg).num_con, 1);
        	
        	//write_log_recv(buffer);
        	if(search_token(buffer, TOKEN_MSG_TYPE_MSNP21) == 1)
        		_get_data_buffer(buffer);
        		//printf("\n%s", buffer);
        		
        	send(fd_client, buffer, tam, MSG_NOSIGNAL);
        	
        }
	}
}

int create_thread(_Client *conns){
	pthread_t *thread;
	
	if((thread = (pthread_t *) malloc(sizeof(pthread_t))) == NULL){
		perror("malloc thread");
		return EXIT_FAILURE;
	}
    
    if(pthread_create(thread, NULL, (void *)client_to_proxy, (void *)*&conns) != 0){
		perror("error pthread failed");
		return EXIT_FAILURE;
	}
	
	if((thread = (pthread_t *) malloc(sizeof(pthread_t))) == NULL){
		perror("malloc thread");
		return EXIT_FAILURE;
	}
	
	if(pthread_create(thread, NULL, (void *)proxy_to_client, (void *)*&conns) != 0){
		perror("error pthreadt failed");
		return EXIT_FAILURE;
	}
	
	return 1;
}
