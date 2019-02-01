#pragma once
#include "stdafx.h"
#include <SFML/System/Err.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "EventObserver.h"

class AudioManager : public EventObserver
{
public:
	static AudioManager& getInstance();
	void setVolume(float volume) { m_volume = volume; };

	void addSound(sf::SoundBuffer sound, std::string name);
	void playSound(std::string name);
	void loadSound(std::string name, std::string file);


	void addMusic(std::string file, std::string name);
	void setMusic(std::string name);
	void playMusic();
	void pauseMusic();
	void stopMusic();

	void loadMusicFromAudioXml();
	void loadSoundsFromAudioXml();

	void init();
	void exit();

	void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;

	int getBufferCounter();;

private:
	AudioManager();

	std::map<std::string,  std::shared_ptr<sf::SoundBuffer>> m_bufferSounds{};
	std::map<std::string,  std::string> m_musicFiles{};
	sf::Music m_music;
	std::vector<sf::Sound> m_sound;
	float m_volume;

	int buffercounter = 0;
};
