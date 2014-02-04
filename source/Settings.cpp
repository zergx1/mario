
#include "header\Settings.h"


Settings::Settings(void)
{




}

void Settings::init()
{
	parse();
}

void Settings::parse()
{//"D:\Studia\mario\mario\mario\settings.txt.txt"
	std::ifstream infile("settings.ini");
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string a, b, c;
		if (!(iss >> a >> c >> b)) { break; } // error
		options[a] = b;
		//std::cout<<a<<" "<<b;
		// process pair (a,b)
	}
}

int Settings::getIntOption(std::string opt)
{
	int str = std::stoi(options[opt]);
	return str;

}

//float Settings:getFloatOption(std::string opt)
//{
//	return 
//}

Settings::~Settings(void)
{
}
