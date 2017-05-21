#include "msg.h"
#include "log.h"
#include "conv_list.h"
#include "msg_list.h"

/* Funcao que limpa os caracteres desnecessarios do email to: */
char *clean_email_to(const char *email){
	char *_aux_email_to=NULL;
	int i=0, j=0, cont=0;
	
	_aux_email_to = (char *)malloc(strlen(email));
	
	if(_aux_email_to == NULL){
		perror("email_clean");
		exit(1);
	}
	
	bzero(_aux_email_to, strlen(_aux_email_to));
	while(email[i+1] != '\0'){
		if (email[i] == ':'){
			cont++;
			i++;
		}		
		if(email[i] != ':' && cont == 2){
			_aux_email_to[j] = email[i];
			_aux_email_to[j+1] = '\0';
			j++;i++;
		}else
			i++;
	}	
	
	
	return _aux_email_to;		
}

/* Funcao que limpa os caracteres desnecessarios do email From: */
char *clean_email_from(const char *email){
	char *email_clean;
	int i=0, j=0, cont=0;
	
	email_clean = (char *)malloc(strlen(email));
	
	if(email_clean == NULL){
		perror("email_clean");
		exit(1);
	}
	
	bzero(email_clean, strlen(email_clean));
	
	while(email[i+1] != '\0'){ //adicionei +1 12/05
		if (email[i] == ':')
			cont++;
			
		if(email[i+1] == ';')
			break;
			
		if ((cont > 1) && (email[i+1] != '\0')){
			email_clean[j] = email [i+1];
			email_clean[j+1] = '\0';
			j++;
		}
		i++;		
	}
	
	
	return email_clean;		
}


/* Funcao que procura o token no buffer passado */
int search_token(const char *_msg_recv, const char *_TOKEN_MSNP21){
	int i=0, j=0, cont=0;
	char word[TAM_BUFFER];
	
	while(_msg_recv[i] != '\0'){
		if(_msg_recv[i] == _TOKEN_MSNP21[j]){
			do{
				word[cont] = _msg_recv[i];
				i++;j++;cont++;
				
				if(_msg_recv[i] != _TOKEN_MSNP21[j] && (cont < strlen(_TOKEN_MSNP21))){
					cont=0; j=0;
				}
				
			}while(_msg_recv[i] == _TOKEN_MSNP21[j] && (_TOKEN_MSNP21[j] != '\0'));			
		}
		i++;
	}
	
	if(cont == strlen(_TOKEN_MSNP21))
		return 1;
	else
		return 0;	
}



/* Funcao que transforma o buffer de matriz para uma struct contendo apenas as informacoes necessarias */

int make_buffer_to_struct(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_buffer){
	int i, line_sdg=0, line_emailto=0, line_emailfrom=0, line_body=0;
	long int *sdg, sdg0, sdg1;
	char *_email_to;
	char *_email_from;
	char *_body;	
	
	// Pegas as linhas com as informacoes necessaria ja do buffer em matriz	
		
		for(i=0; i <= line_buffer; i++){
						
			if(search_token(buffer_recv[i], TOKEN_SDG_MSNP21) == 1){
				//printf("\n\n\n%s", buffer_recv[i]);
				line_sdg = i;
			}
			
			if(search_token(buffer_recv[i], TOKEN_TO_MSNP21) == 1){
				//printf("\n[%i] %s", i, buffer_recv[i]);					
				line_emailto = i;
			}
			
			if(search_token(buffer_recv[i], TOKEN_FROM_MSNP21) == 1){
				//printf("\n[%i] %s", i, buffer_recv[i]);						
				line_emailfrom = i;
			}
			
			if(search_token(buffer_recv[i], TOKEN_PREMSG) == 1){
				//printf("\n%s", buffer_recv[i]);
				line_body = i+1;
			}
		}
		
		
		sdg = get_num_sdg_array(buffer_recv[line_sdg]);
		sdg0=sdg[0]; sdg1=sdg[1];
		
		_email_to = get_email_to_array(buffer_recv[line_emailto]);
		_email_from = get_email_from_array(buffer_recv[line_emailfrom]);
		_body = get_body_array(buffer_recv, line_body, line_buffer);
		
		//printf("\n%li %li", sdg0, sdg1);
		//printf("\n%s", _email_to);
		//printf("\n%s", _email_from);
		//printf("\n%s", _body);
		
		if(set_struct(sdg0, sdg1, _email_to, _email_from, _body) != 0){
			printf("\n Erro ao setar strutura");
			exit(1);
		}		
								
		return 0;
}

/* Funcao que transforma o buffer recebido em matriz bidimensional */

void _get_data_buffer(const char *_MSG){
	int i=0,j=0;
	char buffer_aux[TAM_BUFFER];
	char data_buffer[TAM_BUFFER][TAM_BUFFER];
	int cont_line=0;	
	
	//Transforma o buffer recebido em matriz buffer[][]			
	do{			
		if(_MSG[i] == '\n'){			
			strcpy(data_buffer[cont_line], buffer_aux);
			bzero(buffer_aux, TAM_BUFFER);
			j=0; 
			i++; 
			cont_line++;
		
		}else{
				buffer_aux[j] = _MSG[i];
				i++; 
				j++;		
		}
		
		if(_MSG[i] == '\0'){
			strcpy(data_buffer[cont_line], buffer_aux);			
		}		
		
	}while(_MSG[i] != '\0');
	
	//print_buffer_array(data_buffer, cont_line);
	
	make_buffer_to_struct(data_buffer, cont_line);
						
}

/* Funcao que preenche a struct com os dados necessario retirados do buffer em matriz */

int set_struct(const long int sdg0_set, const long int sdg1_set, const char *emailto_set, const char *emailfrom_set, const char *body_set){
	_data_msg *_msg_send;
	
	_msg_send = (_data_msg *)malloc(sizeof(_data_msg));
		
	if(_msg_send == NULL){
		perror("_msg");
		exit(1);
	}
	
	bzero(_msg_send, sizeof(_msg_send));
		
	
		
	_msg_send->SDG_1 = sdg0_set;
	_msg_send->SDG_2 = sdg1_set;
		
	_msg_send->MSG_TO = (char *)malloc(strlen(emailto_set));
	
	if(_msg_send->MSG_TO == NULL){
			perror("_msg->MSG_TO");
			exit(1);
		}
		
	strcpy(_msg_send->MSG_TO, emailto_set);
	
	_msg_send->MSG_FROM = (char *)malloc(strlen(emailfrom_set));
	
	if(_msg_send->MSG_FROM == NULL){
			perror("_msg->MSG_FROM");
			exit(1);
		}
	strcpy(_msg_send->MSG_FROM, emailfrom_set);
		
	_msg_send->MSG_BODY = (char *)malloc(strlen(body_set));
	
	if(_msg_send->MSG_BODY == NULL){
			perror("_msg->MSG_BODY");
			exit(1);
		}
	
	bzero(_msg_send->MSG_BODY, strlen(body_set));
	strcpy(_msg_send->MSG_BODY, body_set);	
		
		//write_log_struct(_msg);
		//sleep(2);
		
		//printf("\n\n\n%li %li", _msg_send->SDG_1, _msg_send->SDG_2);
		//printf("\n%s", _msg_send->MSG_TO);
		//printf("\n%s", _msg_send->MSG_FROM);
		//printf("\n%s", _msg_send->MSG_BODY);
		
		insert_data_list_online(*_msg_send);
		
		return 0;
}

void print_buffer_array(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_buffer){
	int i=0;
	
	for(i=0; i<=line_buffer; i++){
		printf("\n %s", buffer_recv[i]);
	}


}

long int *get_num_sdg_array(const char *buffer_recv){
	long int *aux_sdg;
	
	aux_sdg = (long int *)malloc(2 * sizeof(long int));	
	
	sscanf(buffer_recv, "%*s %li %li", &aux_sdg[0], &aux_sdg[1]);
		
	return aux_sdg;
}

char *get_email_to_array(char *buffer_recv){
	
	char *_aux_email_to=NULL;
	
	_aux_email_to = (char *)malloc(strlen(buffer_recv));
	
	strcpy(_aux_email_to, clean_email_to(buffer_recv));
		
	return _aux_email_to;
	
}

char *get_email_from_array(char *buffer_recv){
	
	char *_aux_email_from=NULL;
	
	
	_aux_email_from = (char *)malloc(strlen(buffer_recv));
	
	strcpy(_aux_email_from, clean_email_from(buffer_recv));
		
	return _aux_email_from;
	
}

char *get_body_array(char buffer_recv[TAM_BUFFER][TAM_BUFFER], int line_body, int line_buffer_recv){
	char *_aux_body = (char *)malloc(TAM_BUFFER);
	int i;
	
	bzero(_aux_body, sizeof(TAM_BUFFER));
	
	for(i=line_body; i<= line_buffer_recv; i++){
			if(strlen(_aux_body) > (TAM_BUFFER - 2)){
				_aux_body = (char *)realloc(_aux_body, strlen(buffer_recv[i]));
				if(_aux_body == NULL){
					perror("realloc _body");
					exit(1);
				}
				
				strcat(_aux_body, buffer_recv[i]);
			}else
				strcat(_aux_body, buffer_recv[i]);
	}
	_aux_body[strlen(_aux_body)] = '\0';
	
	return _aux_body;
}

long int get_content_length(const char *buffer_recv){
	int i=0,j=0;
	char buffer_aux[TAM_BUFFER];
	char data_buffer[TAM_BUFFER][TAM_BUFFER];
	int cont_line=0;
	long int content_length;
	
	do{			
		if(buffer_recv[i] == '\n'){			
			strcpy(data_buffer[cont_line], buffer_aux);
			bzero(buffer_aux, TAM_BUFFER);
			j=0; 
			i++; 
			cont_line++;
		
		}else{
				buffer_aux[j] = buffer_recv[i];
				i++; 
				j++;		
		}
		
		if(buffer_recv[i] == '\0'){
			strcpy(data_buffer[cont_line], buffer_aux);			
		}		
		
	}while(buffer_recv[i] != '\0');
	
	for(i=0; i<= cont_line; i++){
		if(search_token(data_buffer[i], TOKEN_CONTLENGTH_MSNP21) == 1){
			sscanf(data_buffer[i], "%*s %li", &content_length);			
		}
	}
	
	return content_length;	
}
