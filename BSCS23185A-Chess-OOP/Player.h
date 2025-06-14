#pragma once
#include<string>
#include"Utility.h"
class player
{

private:
	std::string pname;
	Color C;
	int time;

public:
	player(std::string _name, Color c, int ti);
	std::string getpnamecolr();
	Color getcolor();
	void displaytime(int _t);
	void settime(int _time);
	int gettime();

};

