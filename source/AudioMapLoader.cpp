#include "stdafx.h"
#include "AudioMapLoader.h"
#include "rapidxml/rapidxml.hpp"

AudioMapLoader AudioMapLoader::getInstance()
{
	static AudioMapLoader m_instance;
	return m_instance;
}

map<string, string> AudioMapLoader::loadSoundMap(char* xml)
{
	map<string, string> resMap{  };

	rapidxml::xml_document<> doc;
	doc.parse<0>(xml);

	rapidxml::xml_node<> *audionode = doc.first_node("audio");

	rapidxml::xml_node<> *soundsnode = audionode->first_node("sounds");
	rapidxml::xml_node<> *sounditemsnode = soundsnode->first_node("item");

	while (sounditemsnode)
	{
		string name = sounditemsnode->first_attribute("name")->value();
		string file = sounditemsnode->first_attribute("file")->value();
		resMap.insert_or_assign(name, file);
		sounditemsnode = sounditemsnode->next_sibling("item");
	}

	return resMap;
}

map<string, string> AudioMapLoader::loadMusicMap(char* xml)
{
	map<string, string> resMap{  };

	rapidxml::xml_document<> doc;
	doc.parse<0>(xml);

	rapidxml::xml_node<> *audionode = doc.first_node("audio");

	rapidxml::xml_node<> *musicnode = audionode->first_node("music");
	rapidxml::xml_node<> *musicitemsnode = musicnode->first_node("item");

	while (musicitemsnode)
	{
		string name = musicitemsnode->first_attribute("name")->value();
		string file = musicitemsnode->first_attribute("file")->value();
		resMap.insert_or_assign(name, file);
		musicitemsnode = musicitemsnode->next_sibling("item");
	}

	return resMap;
}