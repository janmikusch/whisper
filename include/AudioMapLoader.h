#pragma once

#include <string>
#include <map>

using namespace std;

class AudioMapLoader
{
public:
	static AudioMapLoader getInstance();
	map<string, string> loadMusicMap(char *xml);
	map<string, string> loadSoundMap(char *xml);
private:
	AudioMapLoader() = default;
};


