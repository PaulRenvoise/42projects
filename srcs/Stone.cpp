#include "Stone.hpp"

Stone::Stone(void)
{
}

Stone::~Stone(void)
{
}

void			Stone::setX(int x)
{
	this->_x = x;
}

int				Stone::getX(void) const
{
	return this->_x;
}

void			Stone::setY(int y)
{
	this->_y = y;
}

int				Stone::getY(void) const
{
	return this->_y;
}

void			Stone::setPlayer(Player* player)
{
	this->_player = player;
}

Player*			Stone::getPlayer(void) const
{
	return this->_player;
}
