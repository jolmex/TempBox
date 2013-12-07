//============================================================================
// Name        : serv.cpp
// Author      : danil
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdlib.h>
#include <strstream>
#include <string.h>
#include <stddef.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int bytesRead = 0;
char buff[1024];

using namespace std;

int main() {
	printf("Hello, start server\n");

	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3424);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	struct sockaddr_in addr_resp;

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	    {
	        perror("bind err");
	        exit(2);
	    }

	char ansver[3];
	ansver[1] = 0x01;
	ansver[2] = 0x47;

	bytesRead = recvfrom(sock, buff, 1024, 0, (struct sockaddr *)&addr_resp, NULL);

	sendto(sock, "", 3, 0,(struct sockaddr *)&addr_resp, sizeof(addr_resp));


	close(sock);

	return 0;
}
