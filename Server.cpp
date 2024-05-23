#include <iostream>
#include "E101.h"
#include <string>
#define PORT 1024

void gate(){
    char address[15] = "130.195.3.53";
	char message[24] = "Please";
	connect_to_server(address,PORT);
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
	
}
