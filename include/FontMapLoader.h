#pragma once

#include <string>
#include <map>

using namespace std;

class FontMapLoader
{
public:
	static FontMapLoader getInstance();
	map<string, string> loadFontMap(char *xml);
private:
	FontMapLoader() = default;
};


