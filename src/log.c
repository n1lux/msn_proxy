/***********************************************************************
 * 						HISTORICO DE ALTERACOES
 * 
 * Obs. Antes de efetuar qualquer alteracao no codigo fazer uma copia de
 * seguranca do arquivo.
 * 
 * [ULTIMAS MODIFICACOES]
 * 21/03/2011 - Criacao do arquivo log.c para separacao das funcoes de 
 * 				escrita de log do servidor. 
 * 
 * *********************************************************************/
#include "app.h"
#include "log.h"

void error(const char *msg){
    perror(msg);
    exit(1);
}

/*int write_log(char *msg_rcv, int desks[], int conn, int flag){
	FILE *fp_log;
		
	if ((fp_log = fopen(LOG, "a+")) == NULL){
		error("ERROR file log");
		return FALSE;
	}
	if (flag == 0){
		fprintf(fp_log, "\n------------------------------[ %i ]------------------------------", conn);
		fprintf(fp_log, "\n[%i] -> [%i]",desks[0], desks[1]);
		fprintf(fp_log, "\n%s", msg_rcv);
		fclose(fp_log);
		return TRUE;
	}else{
		fprintf(fp_log, "\n------------------------------[ %i ]------------------------------", conn);
		fprintf(fp_log, "\n[%i] <- [%i]", desks[1], desks[0]);
		fprintf(fp_log, "\n%s", msg_rcv);
		fclose(fp_log);
		return TRUE;
	}	
	
}*/

int write_log_send(char *msg_rcv){
	FILE *fp_log;
		
	if ((fp_log = fopen(log_send, "a+")) == NULL){
		error("ERROR file log");
		return FALSE;
	}
	
	fprintf(fp_log, "\n>>> %s", msg_rcv);
	fclose(fp_log);
	return TRUE;
}

int write_log_recv(char *msg_rcv){
	FILE *fp_log;
		
	if ((fp_log = fopen(log_recv, "a+")) == NULL){
		error("ERROR file log");
		return FALSE;
	}
	
	fputs("--------------------------------------------------------------------------------------------------------\n", fp_log);
	fprintf(fp_log, "\n%s", msg_rcv);	
	fclose(fp_log);
	return TRUE;
}

int write_log_struct(_data_msg *arg){
	FILE *fp_log;
		
	if ((fp_log = fopen(log_struct, "a+")) == NULL){
		error("ERROR file log");
		return FALSE;
	}
	
	fprintf(fp_log, "\n%li", arg->SDG_1);
	fprintf(fp_log, "\t%li", arg->SDG_2);
	fprintf(fp_log, "\n%s", arg->MSG_TO);
	fprintf(fp_log, "\n%s", arg->MSG_FROM);
	fprintf(fp_log, "\n%s", arg->MSG_BODY);
	fprintf(fp_log,"\n");
	
	fclose(fp_log);
	
	return TRUE;
}

int write_log_msg(const long int SDGS[], const char *email_to, const char *email_from, const char *body){
	FILE *fp_log_data;
		
	if ((fp_log_data = fopen(log_struct, "a+")) == NULL){
		error("ERROR file log");
		return FALSE;
	}
		
	printf("\n%li %li", SDGS[0], SDGS[1]);
	printf("\n%s", email_to);
	printf("\n%s", email_from);
	printf("\n%s", body);
	printf("\n=============================================================================");
	
	/*fprintf(fp_log_data, "\n%li %li", SDGS[0], SDGS[1]);
	fprintf(fp_log_data, "\n%s", email_to);
	fprintf(fp_log_data, "\n%s", email_from);
	fprintf(fp_log_data, "\n%s", body);
	
	fclose(fp_log_data);*/
	return TRUE;
}
