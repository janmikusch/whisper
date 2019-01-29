#include "stdafx.h"
#include "RandomNumber.h"
#include <cstdlib>
#include <ctime>
#include <random>


int engine::Random::getIntBetween(int min, int max)
{
	static std::random_device random;
	std::mt19937 engX(random());
	std::uniform_int_distribution<> distrX(min, max);
	return distrX(engX);
}

///https://stackoverflow.com/questions/686353/random-float-number-generation
float engine::Random::getDoubleBetween(double min, double max)
{
	static std::random_device random;
	std::mt19937 engX(random());
	std::uniform_real_distribution<> distrX(min, max);
	return distrX(engX);
}
