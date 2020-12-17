#include <thread>
#include <windows.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <conio.h>
#include "Transmitter.h"

using namespace std;

int main()
{
	Transmitter tr1(777);
	Transmitter tr2(999);
	Transmitter tr3(1056);

	_getch();

	tr1.stop();
	tr2.stop();
	tr3.stop();
}
