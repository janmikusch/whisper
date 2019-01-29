#pragma once
#include "stdafx.h"

namespace engine
{
	class Random
	{
	public:
		static int getIntBetween(int min, int max);
		static float getDoubleBetween(double min, double max);
	};
}
