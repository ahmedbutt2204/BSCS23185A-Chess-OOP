#include "player.h"
#include<iostream>
#include<iomanip>


player::player(std::string _name, Color c, int ti)
{
	this->pname = _name;
	this->C = c;
	this->time = ti;
}

std::string player::getpnamecolr()
{
	return this->pname;
}

Color player::getcolor()
{
	return this->C;
}

void player::displaytime(int _t)
{
	if (_t == BLACK)
	{
		gotoRowCol(19, 70);
		std::cout << std::setfill('0') << std::setw(2) << int(this->time * 0.0167) % 4 << " : " << std::setfill('0') << std::setw(2) << this->time % 60;
	}

	if (_t == WHITETURN)
	{
		gotoRowCol(64, 70);
		std::cout << std::setfill('0') << std::setw(2) << int(this->time * 0.0167) % 4 << " : " << std::setfill('0') << std::setw(2) << this->time % 60;
	}
}

