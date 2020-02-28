#include "Spiel.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <omp.h>

int main()
{
	Spiel s = Spiel(4);

	s.simulieren();

	std::cout << s;

	return 0;
}
