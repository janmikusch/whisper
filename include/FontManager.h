#pragma once
#include "stdafx.h"
#include <string>
#include <map>
#include <SFML/Graphics/Font.hpp>

class FontManager
{
public:
	static FontManager& getInstance();
	void init();
	sf::Font& getFont(std::string name);
	sf::Font& getDefault();
	bool hasFont(std::string name);
private:
	void loadFont(std::string name, std::string file);
	std::map<std::string, sf::Font> m_fonts;
};
