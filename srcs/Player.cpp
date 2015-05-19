#include "Player.hpp"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void		Player::setActive(bool active)
{
	this->_active = active;
}

bool		Player::isActive(void) const
{
	return this->_active;
}
