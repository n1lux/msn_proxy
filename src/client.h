#ifndef CLIENT_H
#define CLIENT_H

typedef struct{
	int fd_sock[2];
	int num_con;
	long int port;
	char *ipaddress;
}_Client;

void *create_new_client();

#endif
