#include "stdafx.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "AudioMapLoader.h"
#include "AssetsManager.h"

AudioManager::AudioManager():m_volume(100.0f)
{
}

AudioManager& AudioManager::getInstance()
{
	static AudioManager m_instance;
	return m_instance;
}

void AudioManager::addSound(sf::SoundBuffer sound, std::string name)
{
	auto it = m_bufferSounds.find(name);
	if (it != m_bufferSounds.end())
	{
		sf::err() << "sound " + name + " exists";
		return;
	}

	m_bufferSounds.insert_or_assign(name, std::make_shared<sf::SoundBuffer>(sound));
}

void AudioManager::playSound(std::string name)
{
	auto it = m_bufferSounds.find(name);
	if (it == m_bufferSounds.end())
	{
		sf::err() << "sound " + name + " is missing";
		return;
	}

	
	m_sound.setVolume(m_volume);
	m_sound.setBuffer(*m_bufferSounds[name]);
	m_sound.play();
}

void AudioManager::loadSound(std::string name, std::string file)
{
	sf::SoundBuffer buffer = AssetsManager::getInstance().loadSound(file);
	addSound(buffer, name);
}

void AudioManager::addMusic(std::string name, std::string file)
{
	m_musicFiles.insert_or_assign(name, file);
}

void AudioManager::setMusic(std::string name)
{
	if(AssetsManager::getInstance().loadMusic(m_musicFiles[name], m_music))
		playMusic();
}

void AudioManager::playMusic()
{
	m_music.play();
}

void AudioManager::stopMusic()
{
	m_music.stop();
}

void AudioManager::pauseMusic()
{
	m_music.stop();
}


void AudioManager::loadMusicFromAudioXml()
{
	std::string filename = "audio.xml";

	auto buffer = AssetsManager::getInstance().getXmlBuffer(filename);
	auto newMap = AudioMapLoader::getInstance().loadMusicMap(buffer);
	delete buffer;

	m_musicFiles.swap(newMap);
}

void AudioManager::loadSoundsFromAudioXml()
{
	std::string filename = "audio.xml";

	auto buffer = AssetsManager::getInstance().getXmlBuffer(filename);
	auto newMap = AudioMapLoader::getInstance().loadSoundMap(buffer);
	delete buffer;

	std::map < std::string, std::shared_ptr<sf::SoundBuffer>> newBufferMap{};
	m_bufferSounds.swap(newBufferMap);

	for (auto it : newMap)
	{
		loadSound(it.first, it.second);
	}

}


void AudioManager::exit()
{
	stopMusic();
}

void AudioManager::onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if(type==engine::EventType::DAMAGETAKEN)
	{
		playSound("failure");
		//TODO
		// Event is triggired per frame
	}
	if(type==engine::EventType::ROOMUNLOCKED)
	{
		playSound("success");
	}
}


void AudioManager::init()
{
	loadMusicFromAudioXml();
	loadSoundsFromAudioXml();

	EventBus::getInstance().addObserver(engine::EventType::DAMAGETAKEN, this);
	EventBus::getInstance().addObserver(engine::EventType::ROOMUNLOCKED, this);
}
