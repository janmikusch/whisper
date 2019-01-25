#include "stdafx.h"
#include "FontMapLoader.h"
#include "rapidxml/rapidxml.hpp"

FontMapLoader FontMapLoader::getInstance()
{
	static FontMapLoader m_instance;
	return m_instance;
}

map<string, string> FontMapLoader::loadFontMap(char* xml)
{
	map<string, string> resMap{  };

	rapidxml::xml_document<> doc;
	doc.parse<0>(xml);

	rapidxml::xml_node<> *audionode = doc.first_node("fonts");

	rapidxml::xml_node<> *itemnode = audionode->first_node("item");

	while (itemnode)
	{
		string name = itemnode->first_attribute("name")->value();
		string file = itemnode->first_attribute("file")->value();
		resMap.insert_or_assign(name, file);
		itemnode = itemnode->next_sibling("item");
	}

	return resMap;
}