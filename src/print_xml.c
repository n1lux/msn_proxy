#include "print_xml.h"

int print_log(msgList list_to_log){
	FILE *fp_list_xml;
	struct no_msgs *aux_xml;
	char *_email_name_log, *_name_arq_log;
	
	aux_xml = list_to_log.inicio;
	
	_email_name_log = (char *)malloc(1024 * sizeof(char));
	
	strcpy(_email_name_log, aux_xml->_msgs._user_from);
	strcat(_email_name_log, "_");
	strcat(_email_name_log, aux_xml->_msgs._user_to);
	strcat(_email_name_log, ".xml");
	
	_name_arq_log = (char *)malloc(1024 * sizeof(char));
	
	strcpy(_name_arq_log, path_log_xml);
	strcat(_name_arq_log, _email_name_log);
	
	_name_arq_log[strlen(_name_arq_log)] = '\0';
	
	if((fp_list_xml = fopen(_name_arq_log, "w+")) == NULL){
		perror("arq_list_log_xml");
		exit(1);
	}
	
	while(aux_xml != NULL){			
		fprintf(fp_list_xml, "\n<conversation id=%i>", aux_xml->_msgs.id_conv);
		fprintf(fp_list_xml, "\n  <to>%s</to>", aux_xml->_msgs._user_to);
		fprintf(fp_list_xml, "\n  <from>%s</from>", aux_xml->_msgs._user_from);
		fprintf(fp_list_xml, "\n  <body>%s</body>", aux_xml->_msgs._body);
		if(aux_xml->_msgs._blocked == NULL){
			aux_xml->_msgs._blocked = (char *)malloc(sizeof(char));
			strcpy(aux_xml->_msgs._blocked, "");
		}			
		fprintf(fp_list_xml, "\n  <blocked>%s</blocked>", aux_xml->_msgs._blocked);
		fputs("\n</conversation>", fp_list_xml);								
		aux_xml = aux_xml->prox;		
	}
	
	fclose(fp_list_xml);
	
	return 0;


}
