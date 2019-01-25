#include "stdafx.h"
#include "AssetsManager.h"
#include <SFML/System/Err.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <immintrin.h>

AssetsManager& AssetsManager::getInstance()
{
	static AssetsManager m_instance;
	return m_instance;
}

sf::SoundBuffer AssetsManager::loadSound(std::string file)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(m_assetspath + m_soundFolder + file))
	{
		sf::err() << "sound loading failed";
	}
	return buffer;
}

bool AssetsManager::loadMusic(std::string file, sf::Music& music)
{
	const bool success = music.openFromFile(m_assetspath + m_musicFolder + file);
	if (!success)
	{
		sf::err() << "music loading failed";
	}
	return success;
}

char* AssetsManager::getXmlBuffer(std::string file)
{
	sf::FileInputStream inputStream;
	if (!inputStream.open(m_assetspath + m_xmlFolder + file))
	{
		sf::err() << "loadMusicFromAudioXml: could not open file " << file << std::endl;
		return nullptr;
	}

	// convert FileInputStream to char* mapBuffer
	char* xmlBuffer = new char[inputStream.getSize() + 1];
	inputStream.read(xmlBuffer, inputStream.getSize());
	xmlBuffer[inputStream.getSize()] = '\0';

	return xmlBuffer;
}

sf::Texture AssetsManager::getTexture(std::string file)
{
	sf::Texture texture;
	texture.loadFromFile(m_assetspath + m_textureFolder + file);
	return texture;
}

sf::Font AssetsManager::getFont(std::string file)
{
	sf::Font font;
	font.loadFromFile(m_assetspath + m_fontsFolder + file);
	return font;
}

char* AssetsManager::getMapBuffer(std::string file)
{
	sf::FileInputStream mapStream;
	if (!mapStream.open(m_assetspath + m_mapsFolder + file))
	{
		sf::err() << "loadMap: could not open file " << file << std::endl;
		return nullptr;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	return mapBuffer;
}
