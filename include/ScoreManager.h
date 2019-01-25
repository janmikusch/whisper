#pragma once
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <vector>

class ScoreManager
{
public:
	static ScoreManager& getInstance()
	{
		static ScoreManager m_instance;
		return m_instance;
	};
	
	void addScore(int s) { m_score += s; };
	int getScore() { return m_score; };
	void resetScore() { m_score = 0; };

private:
	ScoreManager() = default;
	int m_score = 0;
};