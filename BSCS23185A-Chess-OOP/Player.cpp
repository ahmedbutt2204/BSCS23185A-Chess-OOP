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