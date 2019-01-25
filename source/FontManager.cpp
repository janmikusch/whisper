#include "stdafx.h"
#include "FontManager.h"
#include "FontMapLoader.h"
#include "AssetsManager.h"
#include <SFML/System/Err.hpp>

FontManager& FontManager::getInstance()
{
	static FontManager m_instance;
	return m_instance;
}

void FontManager::init()
{
	std::string filename = "fonts.xml";

	auto buffer = AssetsManager::getInstance().getXmlBuffer(filename);
	auto fontMap = FontMapLoader::getInstance().loadFontMap(buffer);
	delete buffer;

	for(auto it:fontMap)
	{
		loadFont(it.first, it.second);
	}
}

sf::Font& FontManager::getFont(std::string name)
{
	if (!hasFont(name))
	{
		sf::err() << "Font " << name << " not found" << std::endl;
		return getDefault();
	}
	return m_fonts[name];
}

void FontManager::loadFont(std::string name,std::string file)
{
	m_fonts.insert_or_assign(name, AssetsManager::getInstance().getFont(file));
}

sf::Font& FontManager::getDefault()
{
	return m_fonts["default"];
}

bool FontManager::hasFont(std::string s)
{
	return m_fonts.find(s) != m_fonts.end();
}
