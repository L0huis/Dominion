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

	double percent();
	unsigned int cost2();
	unsigned int cost3();
	unsigned int cost4();
	unsigned int cost5();
} // namespace z