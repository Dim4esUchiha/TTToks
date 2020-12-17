#pragma once

#include <thread>
#include <windows.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <conio.h>

#define JAM_SIGNAL "???"
#define MAX_ATTEMPTS 10
#define COLISION_WINDOW 40
#define MESSAGE_LENGHT 7

using namespace std;

class Transmitter
{
private:
	static string msg_channel;
	thread* transmit_thread;
	bool running;
	int transmitter_delay;
	string name;
	static int id;
	static void transmitting(Transmitter* transmitter);
	static string generateMessage();

public:
	Transmitter(int transmitter_delay) : running(true)
	{
		id++;
		this->name = "Transmitter " + to_string(id);
		this->transmitter_delay = transmitter_delay;
		transmit_thread = new thread(transmitting, this);
	}
	void stop();
};

