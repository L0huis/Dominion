#include <iostream>
#include <chrono>
#include <atomic>
#include <omp.h>

#include "Spiel.h"

int main()
{
	Spiel s = Spiel(10);
	s.simulieren();

	std::cout << s;

	return 0;
}
