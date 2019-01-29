#include "stdafx.h"
#include "RandomNumber.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <SFML/System/Err.hpp>


int engine::Random::getIntBetween(int min, int max)
{
	static std::random_device random;
	std::mt19937 engX(random());
	std::uniform_int_distribution<> distrX(min, max);
	auto res = distrX(engX);
#ifdef _DEBUG
	sf::err() << "Random int: " << res << std::endl;
#endif
		return res;
}

///https://stackoverflow.com/questions/686353/random-float-number-generation
float engine::Random::getDoubleBetween(double min, double max)
{
	static std::random_device random;
	std::mt19937 engX(random());
	std::uniform_real_distribution<> distrX(min, max);
	return distrX(engX);
}
