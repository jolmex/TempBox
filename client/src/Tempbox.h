/*
 * Tempbox.h
 *
 *  Created on: Dec 6, 2013
 *      Author: danil
 */

#ifndef TEMPBOX_H_
#define TEMPBOX_H_


#include <stdlib.h>


#include <unistd.h>
#include <iostream>

#include <stddef.h>
#include <stdio.h>

#define MESSAGE_SIZE 10
#define BUFF_SIZE 1024
#define CONSTANT_COMMANDS 50
#define MAX_COMMANDS 70
#define TEMP_STEP 0.0625

class Tempbox
{
	private:
	//vars
	int ledCount, detectorCount;
	long ipTempBox;
	char buff[BUFF_SIZE];

	///////////////////////////////////////////////////////////////////////////
	// functions
	///////////////////////////////////////////////////////////////////////////


	// Returns response length of TempBox. Recomended response buffer size 1024;
	int sendUdp(char* comm, char* resp, char respSize);

	long convertIp(char*);

	public:
	// vars
	class Commands
	{
	public:
		static const int SetTemp =0, GetTemp = 1, WriteNewCommand = 2, System =3;
	};

    ///////////////////////////////////////////////////////////////////////////
	// functions
	///////////////////////////////////////////////////////////////////////////

	Tempbox(int detectorCount, int ledCount, char* ipTempBox);

	// Get temp for detector number
	double getTemp(int detectorNum);

	// Get temp from both detectors (only for systems with 2 detectors)
	double* getBothTemp(void);

	// Set temp of conditioners
	void setTemp(int temp);

	// Send a command to device by num. Use Tempbox::Commands struct. Returns -1 == fail, 0 == not shure, 1 == success;
	signed int sendCommand(int command, char value);



};

#endif /* TEMPBOX_H_ */
