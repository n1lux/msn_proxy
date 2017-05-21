#include "client.h"
#include "app.h"

void *create_new_client(){
	_Client * new_client_create;
	new_client_create = (_Client *)malloc(sizeof(_Client));
	
	return new_client_create;
}

