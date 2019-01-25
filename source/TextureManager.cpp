#include "stdafx.h"
#include "TextureManager.h"
#include <iostream>
#include "AssetsManager.h"

void TextureManager::addTexture(std::string s, sf::Texture texture)
{
	m_textures.insert_or_assign(s, texture);
}

sf::Texture& TextureManager::getTexture(std::string s)
{
	return m_textures[s];
}

bool TextureManager::hasTexture(std::string s)
{
	return m_textures.find(s) != m_textures.end();
}

void TextureManager::loadTexture(std::string file)
{
	if(!hasTexture(file))
	{
		sf::Texture texture = AssetsManager::getInstance().getTexture(file);
		addTexture(file, texture);
	}
}

void TextureManager::clear()
{
	m_textures.clear();
}
