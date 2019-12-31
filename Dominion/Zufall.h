#pragma once
#include <random>

namespace z
{
	std::mt19937 engine(0);
	std::uniform_real_distribution<double> p(0, 1);
	std::discrete_distribution<unsigned int> c2({ 1, 1 });
	std::discrete_distribution<unsigned int> c3({ 3, 1, 1, 1 });
	std::discrete_distribution<unsigned int> c4({ 1, 1 });
	std::discrete_distribution<unsigned int> c5({ 1, 1, 1, 1, 1 });

	double percent() { return p(engine); }
	unsigned int cost2() { return c2(engine); }
	unsigned int cost3() { return c3(engine); }
	unsigned int cost4() { return c4(engine); }
	unsigned int cost5() { return c5(engine); }
}