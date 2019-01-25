#pragma once
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <vector>

class TextureManager
{
public:
	static TextureManager& getInstance()
	{
		static TextureManager m_instance;
		return m_instance;
	};
	void addTexture(std::string s, sf::Texture texture);
	sf::Texture& getTexture(std::string s);
	bool hasTexture(std::string s);
	void loadTexture(std::string file);
	void clear();

private:
	TextureManager() = default;
	std::map<std::string, sf::Texture> m_textures;
};