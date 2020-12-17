#include "Transmitter.h"

string Transmitter::msg_channel = "";
int Transmitter::id = 0;

string Transmitter::generateMessage()
{
	string tmp_s;
	static const char dataSource[] =
		"0123456789"
		"ABSTEFGHIJKLMNOPQRSTUVWXYZ"
		"abstefghijklmnopqrstuvwxyz"
		"!@#$%^&*()_+~";
	srand(clock() + GetCurrentThreadId());
	for (int i = 0; i < MESSAGE_LENGHT; ++i)
		tmp_s += dataSource[rand() % (sizeof(dataSource) - 1)];
	return tmp_s;
}

void Transmitter::transmitting(Transmitter* instance)
{
	while (instance->running)
	{
		Sleep(instance->transmitter_delay);
		string msg;
		msg = generateMessage();
		int attempt_counter = 0;
		while (true)
		{
			if (!attempt_counter && !Transmitter::msg_channel.compare(JAM_SIGNAL))
				break;

			Transmitter::msg_channel = msg;
			Sleep(COLISION_WINDOW);

			if (Transmitter::msg_channel == msg)
			{
				cout << "Transmit message from " << instance->name << ": " << setw(8) << msg_channel << endl;
				Transmitter::msg_channel = "";
				break;
			}
			else
			{
				Transmitter::msg_channel = JAM_SIGNAL;
				attempt_counter++;
				cout << "Collision on " << instance->name << ", attempt: " << attempt_counter << endl;
				if (attempt_counter == MAX_ATTEMPTS)
				{
					cout << "ERROR!" << endl;
					break;
				}
				int time_slot = rand() % ((int)pow(2, attempt_counter) + 1);
				Sleep(time_slot * 100);
				Transmitter::msg_channel = "";
			}
		}
	}
}

void Transmitter::stop()
{
	running = false;
	transmit_thread->join();
	cout << name << " stopped" << endl;
}