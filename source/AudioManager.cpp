#include "stdafx.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "AudioMapLoader.h"
#include "AssetsManager.h"
#include "RandomNumber.h"
#include "RoomManager.h"

AudioManager::AudioManager():m_volume(100.0f)
{
	//Max paralell sounds
	for(int i = 0; i < 10; i++)
	{
		m_sound.push_back(sf::Sound{});
	}
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

	int i = getBufferCounter();
	
	m_sound[i].setVolume(m_volume);
	m_sound[i].setBuffer(*m_bufferSounds[name]);
	m_sound[i].play();
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
		if(RoomManager::getInstance().getLives() > 0)
			playSound("failure");
	}
	if(type==engine::EventType::ROOMUNLOCKED)
	{
		playSound("success");
	}
	if(type==engine::EventType::GAMEOVER)
	{
		int i = engine::Random::getIntBetween(0, 9);
		switch (i)
		{
		case 0:
			playSound("death1");
			break;
		case 1:
			playSound("death2");
			break;
		case 2:
			playSound("death3");
			break;
		case 3:
			playSound("death4");
			break;
		case 4:
			playSound("death5");
			break;
		case 5:
			playSound("death6");
			break;
		case 6:
			playSound("death7");
			break;
		case 7:
			playSound("death8");
			break;
		case 8:
			playSound("death9");
			break; 
		default:
			playSound("death10");
		}
	}
}

int AudioManager::getBufferCounter()
{
	if (++buffercounter >= m_sound.size())
		buffercounter = 0;
	sf::err() << buffercounter << std::endl;
	return buffercounter;
}


void AudioManager::init()
{
	loadMusicFromAudioXml();
	loadSoundsFromAudioXml();

	EventBus::getInstance().addObserver(engine::EventType::DAMAGETAKEN, this);
	EventBus::getInstance().addObserver(engine::EventType::GAMEOVER, this);
	EventBus::getInstance().addObserver(engine::EventType::ROOMUNLOCKED, this);
}
