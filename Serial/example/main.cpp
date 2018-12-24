#include <iostream>
#include "Serial.h"
#include <vector>
#include <stdio.h>
//#include <string.h>

using namespace std;

const char* portName = "\\\\.\\COM5";
char* port = const_cast<char *>(portName);
#define MAX_DATA_LENGTH 255

byte incomingData[MAX_DATA_LENGTH];

//Control signals for turning on and turning off the led
//Check m5stack code
byte ledON[] = "ON";
byte ledOFF[] = "OFF";
unsigned int ledON_size = 2;
unsigned int ledOFF_size = 3;


//m5stack SerialPort object
SerialPort *m5stack;

//Blinking Delay
const unsigned int BLINKING_DELAY = 1000;

//If you want to send data then define "SEND" else comment it out
//#define SEND

void exampleReceiveData(void)
{
	int readResult = m5stack->readSerialPort(incomingData, MAX_DATA_LENGTH);
	printf("%s", incomingData);
	Sleep(10);
}

void exampleWriteData(unsigned int delayTime)
{
	m5stack->writeSerialPort(ledON,ledON_size);
	Sleep(delayTime);
	m5stack->writeSerialPort(ledOFF,ledOFF_size);
	Sleep(delayTime);
}

void autoConnect(void)
{
	//wait connection
	while (!m5stack->isConnected()) {
		Sleep(100);
		m5stack = new SerialPort(port);
	}

	//Checking if m5stack is connected or not
	if (m5stack->isConnected()) {
		std::cout << "Connection established at port " << portName << endl;
	}

#ifdef SEND
	while (m5stack->isConnected()) exampleWriteData(BLINKING_DELAY);
#else // SEND
	while (m5stack->isConnected()) exampleReceiveData();
#endif // SEND

	//if the serial connection is lost
	autoConnect();
}

int main()
{
	m5stack = new SerialPort(port);
	autoConnect();
}
