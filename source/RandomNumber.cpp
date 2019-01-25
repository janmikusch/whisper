#include "stdafx.h"
#include "RandomNumber.h"
#include <cstdlib>
#include <ctime>

///https://www.daniweb.com/programming/software-development/threads/1769/c-random-numbers#
int engine::Random::getIntBetween(int min, int max)
{
	srand((unsigned)time(0));
	int result;
	int range = (max - min) + 1;

	result = min + int(range*rand() / (RAND_MAX + 1.0));;

	return  result;
}

///https://stackoverflow.com/questions/686353/random-float-number-generation
float engine::Random::getFloatBetween(float min, float max)
{
	float result = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return result;
}
