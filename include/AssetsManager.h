#pragma once
#include "stdafx.h"
#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetsManager
{
public:
	static AssetsManager& getInstance();
	sf::SoundBuffer loadSound(std::string file);
	bool loadMusic(std::string file, sf::Music& music);
	char* getXmlBuffer(std::string file);
	sf::Texture getTexture(std::string file);
	sf::Font getFont(std::string file);
	char* getMapBuffer(std::string file);

private:
	AssetsManager() = default;
	const std::string m_assetspath = "../assets/";
	const std::string m_musicFolder = "music/";
	const std::string m_soundFolder = "sounds/";
	const std::string m_mapsFolder = "maps/";
	const std::string m_fontsFolder = "fonts/";
	const std::string m_xmlFolder = "xmlFiles/";
	const std::string m_textureFolder = "textures/";
};
