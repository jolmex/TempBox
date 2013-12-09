/*
 * Tempbox.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: danil
 */

#include "Tempbox.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


using namespace std;

Tempbox::Tempbox(int detectorCount, int ledCount, char* ipTempBoxLine)
{
	this->detectorCount = detectorCount;
	this->ledCount = ledCount;
	try
	{
		this->ipTempBox = convertIp(ipTempBoxLine);
	}catch(char* str)
	{
		printf(str);
		printf("\n");
		exit(2);
	}


}

long Tempbox::convertIp(char* addr)
{

	int j = 0;
	unsigned long result = 0;

	for(int i = 0; i<4; i++)
	{
		unsigned char part = 0;
		while((addr[j]!='.')&&(addr[j]!='\0'))
		{
			part = part*10 + (addr[j]-48);
			j++;
			if(j>15) throw "ip address line parse error";
		}
		j++;

		result = ((result<<8)|part);  //a problem is here !!!!!!!!!!!!!!!!!!1
	}

	return result;

}

int Tempbox::sendUdp(char* comm, char* resp, int respSize)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addrOut;
		addrOut.sin_family = AF_INET;
		addrOut.sin_port = htons(3424);
		addrOut.sin_addr.s_addr = htonl(ipTempBox);

	int sock_in = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(3424);
			addr.sin_addr.s_addr = htonl(INADDR_ANY);

	sendto(sock, comm, MESSAGE_SIZE, 0,(struct sockaddr *)&addrOut, sizeof(addrOut));


	if(bind(sock_in, (struct sockaddr *)&addr, sizeof(addr))<0)
	{
		close(sock);
		perror("Socket perror");
		throw; //There is thread exception error (thread object destructs before function itself)
	}

	int bytesRead = recvfrom(sock_in, resp, respSize, 0, NULL, NULL);

	close(sock);
	close(sock_in);

	return bytesRead;
}

signed int Tempbox::sendCommand(int command, char value)
{
	int respLength = 0;
	char commLine[MESSAGE_SIZE];

	switch(command)
	{
	case 0:
		commLine[0] = 0x33;  //prefix
		commLine[1] = value;
		break;
	case 1:
		commLine[0] = 0x55;
		commLine[1] = value;
		break;
	case 2:
		commLine[0] = 0x44;
		if((value>CONSTANT_COMMANDS) && (value<MAX_COMMANDS) )
			commLine[1] = value;
		else
			throw "The command index is not allowed.\n";
		break;
	case 3:
		commLine[0] = 0x22;  // To add in firmware. Commands like reset and so on
		commLine[1] = value;
		break;
	default:
		throw "Unknown command";
		break;
	}

	try
	{
		respLength = sendUdp(commLine, (char*)buff, BUFF_SIZE);
		if (respLength > 0)
			return respLength;
		else return -1;

	}catch(...)
	{
		return -1;
	}


}

void Tempbox::setTemp(int temp)
{
	temp -=15; // temp is situated form 16 to 25 deg starting from 1 pos;
	if((temp<1)||(temp>25)) throw "Temp is out of range";

	if( sendCommand(Commands::SetTemp, temp) <0)
	{
		throw "Send error in setTemp";
	}
}

double Tempbox::getTemp(int detectorNum)
{
	if((detectorNum>=detectorCount)) throw "Incorrect detector index";

	if( sendCommand(Commands::GetTemp, detectorNum) < 0)
		{
			throw "Send error in getTemp";
		}
	int itemp = (buff[1]<<8)|(buff[2]);

	return itemp * TEMP_STEP;
}

double* Tempbox::getBothTemp()
{
	double temps[2];

	if( sendCommand(Commands::GetTemp, 2) < 0) // 2 - index for both detectors (for 2 detector systems only);
		{
			throw "Send error in getTemp";
		}
	temps[0] = ((buff[1]<<8)|(buff[2])) * TEMP_STEP;
	temps[1] = ((buff[3]<<8)|(buff[4])) * TEMP_STEP;

	return temps;
}

