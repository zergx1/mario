#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED
#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

class Settings
{
public:
	Settings(void);
	void init();
	std::map<std::string, std::string> options;
	int getIntOption(std::string opt);
	void parse();
	~Settings(void);
};

#endif