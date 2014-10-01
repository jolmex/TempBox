//============================================================================
// Name        : soc.cpp
// Author      : danil
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define IP_LOCATION "10.25.255.50"

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



void test()
{
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
}

int main(int argc, char* argv[]) {

	Tempbox* box = new Tempbox(2, 2, IP_LOCATION);

	int c = getopt(argc, argv, "t:s:h");
	switch(c)
	{
		case 't':
		{
			try
			{
				cout<<(box->getTemp(*optarg-48))<<"\n";

			}catch(char const* str)
			{
				printf(str);
				printf("It's a fail!!!! Oh no.... :((\n");
			}
			break;
		}
		case 's':
		{
			try
			{
				cout<<(box->setTemp((*optarg-48)*10+(*(optarg+1)-48)))+'\n';

			}catch(char const* str)
			{
				printf(str);
				printf("It's a fail!!!! Oh no.... :((\n");
			}
			break;
		}
		case 'h':
		{
			cout<<"TempBox control system...\n\nparameters:\n-h\tThis help\n-s {your temp}\tSet temperature (be careful, IR transmitter may not be directed correctly)\n-t {detector index 0..n}\tGet temperature from detector\n";
			break;
		}
		default:
			cout<<"Argument error\n";
			break;
	}



	return 0;
}
