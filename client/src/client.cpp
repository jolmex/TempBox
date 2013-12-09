//============================================================================
// Name        : soc.cpp
// Author      : danil
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdlib.h>

#include <string.h>
#include <stddef.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdexcept>

#include "Tempbox.h"

using namespace std;

int main() {

	char ip[20]; // 20 is more than ness.;

	printf("Welcome to TempBox control system!\n Enter TempBox ip: ");
	cin>>ip;

	Tempbox* box = new Tempbox(2, 2, ip);

	try
	{
		cout<<(box->getTemp(0));
	}catch(char const*)
	{
		printf("It's a fail!!!! Oh no.... :((\n");
	}

	cout<<'\n';

	return 0;
}
